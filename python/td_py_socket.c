/*
 * td_py_socket.c - the socket module of the `py` command: BSD sockets
 * (lwIP on the boards, the PC's own on Linux and Windows) with CPython's
 * names.
 *
 *   socket.getaddrinfo(host, port, af=0, type=0, proto=0, flags=0)
 *   s = socket.socket(af=AF_INET, type=SOCK_STREAM, proto=0)
 *   s.connect((host, port)), bind, listen, accept, send, sendall, recv,
 *   sendto, recvfrom, setsockopt, settimeout, setblocking, close,
 *   read/readinto/readline/write (a stream: ssl, asyncio and select use it)
 *
 * The socket under it is always non-blocking; a blocking call waits in
 * slices of 10 ms and lets the VM look for Ctrl+C between them, so a script
 * stuck in recv() or connect() can be stopped. Sockets a script leaves open
 * are closed when it ends (finaliser). Addresses are (host, port) tuples.
 * DNS lookups (getaddrinfo, connect by name) wait for the resolver.
 */
#include <errno.h>
#include <stdio.h>
#include <string.h>

#include "py/runtime.h"
#include "py/stream.h"
#include "py/mperrno.h"
#include "py/objstr.h"
#include "py/mphal.h"

#if defined(_WIN32)
#include <winsock2.h>
#include <ws2tcpip.h>
typedef SOCKET td_sock_t;
#define TD_BAD_SOCK INVALID_SOCKET
#define td_closesocket closesocket
#else
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>
typedef int td_sock_t;
#define TD_BAD_SOCK (-1)
#define td_closesocket close
#endif
#if defined(ESP_PLATFORM)
#include "esp_netif.h"
#endif

#define WAIT_SLICE_MS 10

typedef struct
{
    mp_obj_base_t base;
    td_sock_t fd;
    int af;
    int timeout_ms;   /* -1: blocking, 0: non-blocking, else the timeout */
    bool connecting;  /* a non-blocking connect() still in progress */
} td_socket_t;

static const mp_obj_type_t td_socket_type;

/* ------------------------------------------------------------ errors */

/* The last socket error as an errno value MicroPython knows. */
static int sock_errno(bool connecting)
{
#if defined(_WIN32)
    int e = WSAGetLastError();
    switch (e)
    {
    case WSAEWOULDBLOCK: return connecting ? MP_EINPROGRESS : MP_EAGAIN;
    case WSAEINPROGRESS: return MP_EINPROGRESS;
    case WSAEALREADY: return MP_EALREADY;
    case WSAECONNREFUSED: return MP_ECONNREFUSED;
    case WSAECONNRESET: return MP_ECONNRESET;
    case WSAECONNABORTED: return MP_ECONNABORTED;
    case WSAETIMEDOUT: return MP_ETIMEDOUT;
    case WSAEHOSTUNREACH: return MP_EHOSTUNREACH;
    case WSAENOTCONN: return MP_ENOTCONN;
    case WSAEADDRINUSE: return MP_EADDRINUSE;
    case WSAEISCONN: return MP_EISCONN;
    case WSAEINVAL: return MP_EINVAL;
    default: return MP_EIO;
    }
#else
    int e = errno;
    if (e == EWOULDBLOCK)
        e = connecting ? MP_EINPROGRESS : MP_EAGAIN;
    return e;
#endif
}

static NORETURN void raise_sock_error(bool connecting)
{
    mp_raise_OSError(sock_errno(connecting));
}

/* The network stack must be up before the first socket call: Winsock on
 * Windows, lwIP's thread on a board (Wi-Fi or Ethernet start it too, but a
 * script may run before either was turned on; a socket then simply has no
 * route, and the loopback 127.0.0.1 works). */
static void ensure_started(void)
{
#if defined(ESP_PLATFORM)
    static bool started;
    if (!started)
    {
        esp_err_t err = esp_netif_init();
        if (err != ESP_OK && err != ESP_ERR_INVALID_STATE)
            mp_raise_OSError(MP_EIO);
        started = true;
    }
#elif defined(_WIN32)
    static bool started;
    if (!started)
    {
        WSADATA wsa;
        if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
            mp_raise_OSError(MP_EIO);
        started = true;
    }
#endif
}

static void set_nonblocking(td_sock_t fd)
{
#if defined(_WIN32)
    u_long on = 1;
    ioctlsocket(fd, FIONBIO, &on);
#else
    int flags = fcntl(fd, F_GETFL, 0);
    fcntl(fd, F_SETFL, flags | O_NONBLOCK);
#endif
}

/* ------------------------------------------------------------ waiting */

/* Whether the socket is ready to read or write within timeout_ms (0: now). */
static bool ready(td_sock_t fd, bool for_write, int timeout_ms)
{
    fd_set set, err;
    FD_ZERO(&set);
    FD_ZERO(&err);
    FD_SET(fd, &set);
    FD_SET(fd, &err);
    struct timeval tv = {.tv_sec = timeout_ms / 1000, .tv_usec = (timeout_ms % 1000) * 1000};
    int n = select((int)fd + 1, for_write ? NULL : &set, for_write ? &set : NULL, &err, &tv);
    return n > 0;
}

/* Wait until the socket can read or write, by the socket's timeout. Raises
 * EAGAIN for a non-blocking socket, ETIMEDOUT after the timeout, and
 * KeyboardInterrupt on Ctrl+C. Returns 0, or the error code with errcode
 * non-NULL (stream calls report instead of raising). */
static int wait_ready(td_socket_t *s, bool for_write, int *errcode)
{
    if (s->timeout_ms == 0)
    {
        if (ready(s->fd, for_write, 0))
            return 0;
        if (errcode)
            return *errcode = MP_EAGAIN;
        mp_raise_OSError(MP_EAGAIN);
    }
    mp_uint_t start = mp_hal_ticks_ms();
    for (;;)
    {
        if (ready(s->fd, for_write, WAIT_SLICE_MS))
            return 0;
        mp_event_handle_nowait();   /* Ctrl+C raises KeyboardInterrupt here */
        if (s->timeout_ms > 0 && (int)(mp_hal_ticks_ms() - start) >= s->timeout_ms)
        {
            if (errcode)
                return *errcode = MP_ETIMEDOUT;
            mp_raise_OSError(MP_ETIMEDOUT);
        }
    }
}

/* After a non-blocking connect(): whether it is still in progress. lwIP
 * can report such a socket writable before the connection is up, so ask
 * for the peer instead. A failed connect ends it too (send() then reports
 * the error). */
static bool still_connecting(td_socket_t *s)
{
    if (!s->connecting)
        return false;
    struct sockaddr_storage peer;
    socklen_t len = sizeof(peer);
    int soerr = 0;
    socklen_t elen = sizeof(soerr);
    if (getpeername(s->fd, (struct sockaddr *)&peer, &len) == 0 ||
        (getsockopt(s->fd, SOL_SOCKET, SO_ERROR, (char *)&soerr, &elen) == 0 && soerr != 0))
        s->connecting = false;
    return s->connecting;
}

static td_socket_t *get_open(mp_obj_t self_in)
{
    td_socket_t *s = MP_OBJ_TO_PTR(self_in);
    if (s->fd == TD_BAD_SOCK)
        mp_raise_OSError(MP_EBADF);
    return s;
}

/* ------------------------------------------------------------ addresses */

static mp_obj_t sockaddr_to_tuple(const struct sockaddr *sa)
{
    char ip[64] = "";
    int port = 0;
    if (sa->sa_family == AF_INET)
    {
        const struct sockaddr_in *in = (const struct sockaddr_in *)sa;
        inet_ntop(AF_INET, (void *)&in->sin_addr, ip, sizeof(ip));
        port = ntohs(in->sin_port);
    }
#ifdef AF_INET6
    else if (sa->sa_family == AF_INET6)
    {
        const struct sockaddr_in6 *in6 = (const struct sockaddr_in6 *)sa;
        inet_ntop(AF_INET6, (void *)&in6->sin6_addr, ip, sizeof(ip));
        port = ntohs(in6->sin6_port);
    }
#endif
    mp_obj_t items[2] = {mp_obj_new_str(ip, strlen(ip)), MP_OBJ_NEW_SMALL_INT(port)};
    return mp_obj_new_tuple(2, items);
}

/* Look up (host, port) for a socket of family af and type. */
static struct addrinfo *resolve(const char *host, mp_obj_t port_in, int af, int type, int proto, int flags)
{
    ensure_started();
    char port[16];
    if (mp_obj_is_str(port_in))
        snprintf(port, sizeof(port), "%s", mp_obj_str_get_str(port_in));
    else
        snprintf(port, sizeof(port), "%d", (int)mp_obj_get_int(port_in));
    struct addrinfo hints = {0};
    hints.ai_family = af;
    hints.ai_socktype = type;
    hints.ai_protocol = proto;
    hints.ai_flags = flags;
    struct addrinfo *res = NULL;
    if (host && !host[0])
        host = NULL;
    int rc = getaddrinfo(host, port, &hints, &res);
    if (rc != 0 || !res)
    {
        if (res)
            freeaddrinfo(res);
        mp_raise_OSError(MP_ENOENT);   /* name not found (CPython: socket.gaierror) */
    }
    return res;
}

static struct addrinfo *resolve_tuple(td_socket_t *s, mp_obj_t addr, int type)
{
    mp_obj_t *items;
    mp_obj_get_array_fixed_n(addr, 2, &items);
    const char *host = mp_obj_is_str(items[0]) ? mp_obj_str_get_str(items[0]) : "";
    return resolve(host, items[1], s->af, type, 0, 0);
}

static int sock_type(td_socket_t *s)
{
    int type = SOCK_STREAM;
    socklen_t len = sizeof(type);
    getsockopt(s->fd, SOL_SOCKET, SO_TYPE, (char *)&type, &len);
    return type;
}

/* ------------------------------------------------------------ the object */

static mp_obj_t td_socket_make(td_sock_t fd, int af)
{
    td_socket_t *s = mp_obj_malloc_with_finaliser(td_socket_t, &td_socket_type);
    s->fd = fd;
    s->af = af;
    s->timeout_ms = -1;
    s->connecting = false;
    set_nonblocking(fd);
    return MP_OBJ_FROM_PTR(s);
}

static mp_obj_t td_socket_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *args)
{
    (void)type;
    mp_arg_check_num(n_args, n_kw, 0, 4, false);
    int af = n_args > 0 ? mp_obj_get_int(args[0]) : AF_INET;
    int st = n_args > 1 ? mp_obj_get_int(args[1]) : SOCK_STREAM;
    int proto = n_args > 2 ? mp_obj_get_int(args[2]) : 0;
    ensure_started();
    td_sock_t fd = socket(af, st, proto);
    if (fd == TD_BAD_SOCK)
        raise_sock_error(false);
    return td_socket_make(fd, af);
}

static void td_socket_print(const mp_print_t *print, mp_obj_t self_in, mp_print_kind_t kind)
{
    (void)kind;
    td_socket_t *s = MP_OBJ_TO_PTR(self_in);
    mp_printf(print, "<socket fd=%d>", (int)s->fd);
}

static mp_obj_t td_socket_close(mp_obj_t self_in)
{
    td_socket_t *s = MP_OBJ_TO_PTR(self_in);
    if (s->fd != TD_BAD_SOCK)
    {
        td_closesocket(s->fd);
        s->fd = TD_BAD_SOCK;
    }
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_1(td_socket_close_obj, td_socket_close);

static mp_obj_t td_socket_connect(mp_obj_t self_in, mp_obj_t addr)
{
    td_socket_t *s = get_open(self_in);
    struct addrinfo *ai = resolve_tuple(s, addr, sock_type(s));
    int rc = connect(s->fd, ai->ai_addr, (socklen_t)ai->ai_addrlen);
    freeaddrinfo(ai);
    if (rc == 0)
        return mp_const_none;
    int e = sock_errno(true);
    if (e == MP_EINPROGRESS && s->timeout_ms == 0)
        s->connecting = true;   /* asyncio waits for it to become writable */
    if (e != MP_EINPROGRESS || s->timeout_ms == 0)
        mp_raise_OSError(e);
    wait_ready(s, true, NULL);
    int soerr = 0;
    socklen_t len = sizeof(soerr);
    getsockopt(s->fd, SOL_SOCKET, SO_ERROR, (char *)&soerr, &len);
    if (soerr)
    {
#if defined(_WIN32)
        WSASetLastError(soerr);
        raise_sock_error(false);
#else
        mp_raise_OSError(soerr);
#endif
    }
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_2(td_socket_connect_obj, td_socket_connect);

static mp_obj_t td_socket_bind(mp_obj_t self_in, mp_obj_t addr)
{
    td_socket_t *s = get_open(self_in);
    struct addrinfo *ai = resolve_tuple(s, addr, sock_type(s));
    int rc = bind(s->fd, ai->ai_addr, (socklen_t)ai->ai_addrlen);
    freeaddrinfo(ai);
    if (rc != 0)
        raise_sock_error(false);
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_2(td_socket_bind_obj, td_socket_bind);

static mp_obj_t td_socket_listen(size_t n_args, const mp_obj_t *args)
{
    td_socket_t *s = get_open(args[0]);
    int backlog = n_args > 1 ? mp_obj_get_int(args[1]) : 2;
    if (listen(s->fd, backlog) != 0)
        raise_sock_error(false);
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(td_socket_listen_obj, 1, 2, td_socket_listen);

static mp_obj_t td_socket_accept(mp_obj_t self_in)
{
    td_socket_t *s = get_open(self_in);
    struct sockaddr_storage peer;
    for (;;)
    {
        wait_ready(s, false, NULL);
        socklen_t len = sizeof(peer);
        td_sock_t fd = accept(s->fd, (struct sockaddr *)&peer, &len);
        if (fd != TD_BAD_SOCK)
        {
            mp_obj_t items[2] = {td_socket_make(fd, s->af), sockaddr_to_tuple((struct sockaddr *)&peer)};
            return mp_obj_new_tuple(2, items);
        }
        int e = sock_errno(false);
        if (e != MP_EAGAIN || s->timeout_ms == 0)
            mp_raise_OSError(e);
    }
}
static MP_DEFINE_CONST_FUN_OBJ_1(td_socket_accept_obj, td_socket_accept);

/* One send: the bytes sent. */
static mp_uint_t send_some(td_socket_t *s, const void *buf, size_t len, int *errcode)
{
    for (;;)
    {
        if (still_connecting(s))
        {
            if (s->timeout_ms == 0)
            {
                *errcode = MP_EAGAIN;
                return MP_STREAM_ERROR;
            }
            mp_hal_delay_ms(WAIT_SLICE_MS);   /* Ctrl+C is checked there */
            continue;
        }
        if (wait_ready(s, true, errcode))
            return MP_STREAM_ERROR;
        int n = send(s->fd, buf, (int)len, 0);
        if (n >= 0)
            return (mp_uint_t)n;
        int e = sock_errno(false);
        if (e != MP_EAGAIN || s->timeout_ms == 0)
        {
            *errcode = e;
            return MP_STREAM_ERROR;
        }
    }
}

/* One receive: the bytes received, 0 at the end of the stream. */
static mp_uint_t recv_some(td_socket_t *s, void *buf, size_t len, int *errcode)
{
    for (;;)
    {
        if (wait_ready(s, false, errcode))
            return MP_STREAM_ERROR;
        int n = recv(s->fd, buf, (int)len, 0);
        if (n >= 0)
            return (mp_uint_t)n;
        int e = sock_errno(false);
        if (e == MP_ENOTCONN)
            return 0;   /* lwIP, after the peer closed: the end, as elsewhere */
        if (e != MP_EAGAIN || s->timeout_ms == 0)
        {
            *errcode = e;
            return MP_STREAM_ERROR;
        }
    }
}

static mp_obj_t td_socket_send(mp_obj_t self_in, mp_obj_t data)
{
    td_socket_t *s = get_open(self_in);
    mp_buffer_info_t b;
    mp_get_buffer_raise(data, &b, MP_BUFFER_READ);
    int err = 0;
    mp_uint_t n = send_some(s, b.buf, b.len, &err);
    if (n == MP_STREAM_ERROR)
        mp_raise_OSError(err);
    return mp_obj_new_int_from_uint(n);
}
static MP_DEFINE_CONST_FUN_OBJ_2(td_socket_send_obj, td_socket_send);

static mp_obj_t td_socket_sendall(mp_obj_t self_in, mp_obj_t data)
{
    td_socket_t *s = get_open(self_in);
    mp_buffer_info_t b;
    mp_get_buffer_raise(data, &b, MP_BUFFER_READ);
    size_t done = 0;
    while (done < b.len)
    {
        int err = 0;
        mp_uint_t n = send_some(s, (const uint8_t *)b.buf + done, b.len - done, &err);
        if (n == MP_STREAM_ERROR)
            mp_raise_OSError(err);
        done += n;
    }
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_2(td_socket_sendall_obj, td_socket_sendall);

static mp_obj_t td_socket_recv(mp_obj_t self_in, mp_obj_t len_in)
{
    td_socket_t *s = get_open(self_in);
    mp_int_t len = mp_obj_get_int(len_in);
    vstr_t v;
    vstr_init_len(&v, len);
    int err = 0;
    mp_uint_t n = recv_some(s, v.buf, len, &err);
    if (n == MP_STREAM_ERROR)
    {
        vstr_clear(&v);
        mp_raise_OSError(err);
    }
    v.len = n;
    return mp_obj_new_bytes_from_vstr(&v);
}
static MP_DEFINE_CONST_FUN_OBJ_2(td_socket_recv_obj, td_socket_recv);

static mp_obj_t td_socket_sendto(mp_obj_t self_in, mp_obj_t data, mp_obj_t addr)
{
    td_socket_t *s = get_open(self_in);
    mp_buffer_info_t b;
    mp_get_buffer_raise(data, &b, MP_BUFFER_READ);
    struct addrinfo *ai = resolve_tuple(s, addr, SOCK_DGRAM);
    wait_ready(s, true, NULL);
    int n = sendto(s->fd, b.buf, (int)b.len, 0, ai->ai_addr, (socklen_t)ai->ai_addrlen);
    freeaddrinfo(ai);
    if (n < 0)
        raise_sock_error(false);
    return MP_OBJ_NEW_SMALL_INT(n);
}
static MP_DEFINE_CONST_FUN_OBJ_3(td_socket_sendto_obj, td_socket_sendto);

static mp_obj_t td_socket_recvfrom(mp_obj_t self_in, mp_obj_t len_in)
{
    td_socket_t *s = get_open(self_in);
    mp_int_t len = mp_obj_get_int(len_in);
    vstr_t v;
    vstr_init_len(&v, len);
    struct sockaddr_storage from;
    for (;;)
    {
        wait_ready(s, false, NULL);
        socklen_t flen = sizeof(from);
        int n = recvfrom(s->fd, v.buf, (int)len, 0, (struct sockaddr *)&from, &flen);
        if (n >= 0)
        {
            v.len = n;
            mp_obj_t items[2] = {mp_obj_new_bytes_from_vstr(&v), sockaddr_to_tuple((struct sockaddr *)&from)};
            return mp_obj_new_tuple(2, items);
        }
        int e = sock_errno(false);
        if (e != MP_EAGAIN || s->timeout_ms == 0)
        {
            vstr_clear(&v);
            mp_raise_OSError(e);
        }
    }
}
static MP_DEFINE_CONST_FUN_OBJ_2(td_socket_recvfrom_obj, td_socket_recvfrom);

static mp_obj_t td_socket_setsockopt(size_t n_args, const mp_obj_t *args)
{
    (void)n_args;
    td_socket_t *s = get_open(args[0]);
    int level = mp_obj_get_int(args[1]);
    int opt = mp_obj_get_int(args[2]);
    int rc;
    if (mp_obj_is_int(args[3]))
    {
        int val = mp_obj_get_int(args[3]);
        rc = setsockopt(s->fd, level, opt, (const char *)&val, sizeof(val));
    }
    else
    {
        mp_buffer_info_t b;
        mp_get_buffer_raise(args[3], &b, MP_BUFFER_READ);
        rc = setsockopt(s->fd, level, opt, (const char *)b.buf, (socklen_t)b.len);
    }
    if (rc != 0)
        raise_sock_error(false);
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(td_socket_setsockopt_obj, 4, 4, td_socket_setsockopt);

static mp_obj_t td_socket_settimeout(mp_obj_t self_in, mp_obj_t t)
{
    td_socket_t *s = get_open(self_in);
    if (t == mp_const_none)
        s->timeout_ms = -1;
    else
    {
#if MICROPY_PY_BUILTINS_FLOAT
        mp_float_t sec = mp_obj_get_float(t);
        s->timeout_ms = sec <= 0 ? 0 : (int)(sec * 1000 + 0.5);
        if (sec > 0 && s->timeout_ms == 0)
            s->timeout_ms = 1;
#else
        mp_int_t sec = mp_obj_get_int(t);
        s->timeout_ms = sec <= 0 ? 0 : (int)sec * 1000;
#endif
    }
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_2(td_socket_settimeout_obj, td_socket_settimeout);

static mp_obj_t td_socket_setblocking(mp_obj_t self_in, mp_obj_t flag)
{
    td_socket_t *s = get_open(self_in);
    s->timeout_ms = mp_obj_is_true(flag) ? -1 : 0;
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_2(td_socket_setblocking_obj, td_socket_setblocking);

/* makefile(): the socket is already a stream. */
static mp_obj_t td_socket_makefile(size_t n_args, const mp_obj_t *args)
{
    (void)n_args;
    return args[0];
}
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(td_socket_makefile_obj, 1, 3, td_socket_makefile);

/* ------------------------------------------------------------ stream */

static mp_uint_t td_socket_read(mp_obj_t self_in, void *buf, mp_uint_t size, int *errcode)
{
    td_socket_t *s = MP_OBJ_TO_PTR(self_in);
    if (s->fd == TD_BAD_SOCK)
    {
        *errcode = MP_EBADF;
        return MP_STREAM_ERROR;
    }
    return recv_some(s, buf, size, errcode);
}

static mp_uint_t td_socket_write(mp_obj_t self_in, const void *buf, mp_uint_t size, int *errcode)
{
    td_socket_t *s = MP_OBJ_TO_PTR(self_in);
    if (s->fd == TD_BAD_SOCK)
    {
        *errcode = MP_EBADF;
        return MP_STREAM_ERROR;
    }
    return send_some(s, buf, size, errcode);
}

static mp_uint_t td_socket_ioctl(mp_obj_t self_in, mp_uint_t request, uintptr_t arg, int *errcode)
{
    td_socket_t *s = MP_OBJ_TO_PTR(self_in);
    if (request == MP_STREAM_CLOSE)
    {
        td_socket_close(self_in);
        return 0;
    }
    if (request == MP_STREAM_POLL)
    {
        if (s->fd == TD_BAD_SOCK)
            return MP_STREAM_POLL_NVAL;
        mp_uint_t ret = 0;
        if ((arg & MP_STREAM_POLL_RD) && ready(s->fd, false, 0))
            ret |= MP_STREAM_POLL_RD;
        if ((arg & MP_STREAM_POLL_WR) && !still_connecting(s) && ready(s->fd, true, 0))
            ret |= MP_STREAM_POLL_WR;
        return ret;
    }
    *errcode = MP_EINVAL;
    return MP_STREAM_ERROR;
}

static const mp_stream_p_t td_socket_stream_p = {
    .read = td_socket_read,
    .write = td_socket_write,
    .ioctl = td_socket_ioctl,
};

static const mp_rom_map_elem_t td_socket_locals_table[] = {
    {MP_ROM_QSTR(MP_QSTR___del__), MP_ROM_PTR(&td_socket_close_obj)},
    {MP_ROM_QSTR(MP_QSTR___enter__), MP_ROM_PTR(&mp_identity_obj)},
    {MP_ROM_QSTR(MP_QSTR___exit__), MP_ROM_PTR(&mp_stream___exit___obj)},
    {MP_ROM_QSTR(MP_QSTR_close), MP_ROM_PTR(&td_socket_close_obj)},
    {MP_ROM_QSTR(MP_QSTR_connect), MP_ROM_PTR(&td_socket_connect_obj)},
    {MP_ROM_QSTR(MP_QSTR_bind), MP_ROM_PTR(&td_socket_bind_obj)},
    {MP_ROM_QSTR(MP_QSTR_listen), MP_ROM_PTR(&td_socket_listen_obj)},
    {MP_ROM_QSTR(MP_QSTR_accept), MP_ROM_PTR(&td_socket_accept_obj)},
    {MP_ROM_QSTR(MP_QSTR_send), MP_ROM_PTR(&td_socket_send_obj)},
    {MP_ROM_QSTR(MP_QSTR_sendall), MP_ROM_PTR(&td_socket_sendall_obj)},
    {MP_ROM_QSTR(MP_QSTR_recv), MP_ROM_PTR(&td_socket_recv_obj)},
    {MP_ROM_QSTR(MP_QSTR_sendto), MP_ROM_PTR(&td_socket_sendto_obj)},
    {MP_ROM_QSTR(MP_QSTR_recvfrom), MP_ROM_PTR(&td_socket_recvfrom_obj)},
    {MP_ROM_QSTR(MP_QSTR_setsockopt), MP_ROM_PTR(&td_socket_setsockopt_obj)},
    {MP_ROM_QSTR(MP_QSTR_settimeout), MP_ROM_PTR(&td_socket_settimeout_obj)},
    {MP_ROM_QSTR(MP_QSTR_setblocking), MP_ROM_PTR(&td_socket_setblocking_obj)},
    {MP_ROM_QSTR(MP_QSTR_makefile), MP_ROM_PTR(&td_socket_makefile_obj)},
    {MP_ROM_QSTR(MP_QSTR_read), MP_ROM_PTR(&mp_stream_read_obj)},
    {MP_ROM_QSTR(MP_QSTR_readinto), MP_ROM_PTR(&mp_stream_readinto_obj)},
    {MP_ROM_QSTR(MP_QSTR_readline), MP_ROM_PTR(&mp_stream_unbuffered_readline_obj)},
    {MP_ROM_QSTR(MP_QSTR_write), MP_ROM_PTR(&mp_stream_write_obj)},
};
static MP_DEFINE_CONST_DICT(td_socket_locals_dict, td_socket_locals_table);

static MP_DEFINE_CONST_OBJ_TYPE(
    td_socket_type,
    MP_QSTR_socket,
    MP_TYPE_FLAG_NONE,
    make_new, td_socket_new,
    print, td_socket_print,
    protocol, &td_socket_stream_p,
    locals_dict, &td_socket_locals_dict);

/* ------------------------------------------------------------ module */

static mp_obj_t td_getaddrinfo(size_t n_args, const mp_obj_t *args)
{
    const char *host = args[0] == mp_const_none ? NULL : mp_obj_str_get_str(args[0]);
    int af = n_args > 2 ? mp_obj_get_int(args[2]) : 0;
    int type = n_args > 3 ? mp_obj_get_int(args[3]) : 0;
    int proto = n_args > 4 ? mp_obj_get_int(args[4]) : 0;
    int flags = n_args > 5 ? mp_obj_get_int(args[5]) : 0;
    struct addrinfo *res = resolve(host, args[1], af, type, proto, flags);
    mp_obj_t list = mp_obj_new_list(0, NULL);
    /* IPv4 first: socket() makes an AF_INET socket by default, and scripts
     * (umqtt, requests) connect to the first address. */
    for (int pass = 0; pass < 2; pass++)
    for (struct addrinfo *ai = res; ai; ai = ai->ai_next)
    {
        if ((ai->ai_family == AF_INET) != (pass == 0))
            continue;
        mp_obj_t items[5] = {
            MP_OBJ_NEW_SMALL_INT(ai->ai_family),
            MP_OBJ_NEW_SMALL_INT(ai->ai_socktype),
            MP_OBJ_NEW_SMALL_INT(ai->ai_protocol),
            MP_OBJ_NEW_QSTR(MP_QSTR_),
            sockaddr_to_tuple(ai->ai_addr),
        };
        mp_obj_list_append(list, mp_obj_new_tuple(5, items));
    }
    freeaddrinfo(res);
    return list;
}
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(td_getaddrinfo_obj, 2, 6, td_getaddrinfo);

static const mp_rom_map_elem_t td_socket_module_table[] = {
    {MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_socket)},
    {MP_ROM_QSTR(MP_QSTR_socket), MP_ROM_PTR(&td_socket_type)},
    {MP_ROM_QSTR(MP_QSTR_getaddrinfo), MP_ROM_PTR(&td_getaddrinfo_obj)},
    {MP_ROM_QSTR(MP_QSTR_AF_INET), MP_ROM_INT(AF_INET)},
    {MP_ROM_QSTR(MP_QSTR_AF_INET6), MP_ROM_INT(AF_INET6)},
    {MP_ROM_QSTR(MP_QSTR_SOCK_STREAM), MP_ROM_INT(SOCK_STREAM)},
    {MP_ROM_QSTR(MP_QSTR_SOCK_DGRAM), MP_ROM_INT(SOCK_DGRAM)},
    {MP_ROM_QSTR(MP_QSTR_SOCK_RAW), MP_ROM_INT(SOCK_RAW)},
    {MP_ROM_QSTR(MP_QSTR_IPPROTO_IP), MP_ROM_INT(IPPROTO_IP)},
    {MP_ROM_QSTR(MP_QSTR_IPPROTO_TCP), MP_ROM_INT(IPPROTO_TCP)},
    {MP_ROM_QSTR(MP_QSTR_IPPROTO_UDP), MP_ROM_INT(IPPROTO_UDP)},
    {MP_ROM_QSTR(MP_QSTR_SOL_SOCKET), MP_ROM_INT(SOL_SOCKET)},
    {MP_ROM_QSTR(MP_QSTR_SO_REUSEADDR), MP_ROM_INT(SO_REUSEADDR)},
    {MP_ROM_QSTR(MP_QSTR_SO_KEEPALIVE), MP_ROM_INT(SO_KEEPALIVE)},
    {MP_ROM_QSTR(MP_QSTR_SO_BROADCAST), MP_ROM_INT(SO_BROADCAST)},
    {MP_ROM_QSTR(MP_QSTR_TCP_NODELAY), MP_ROM_INT(TCP_NODELAY)},
};
static MP_DEFINE_CONST_DICT(td_socket_module_globals, td_socket_module_table);

const mp_obj_module_t td_socket_module = {
    .base = {&mp_type_module},
    .globals = (mp_obj_dict_t *)&td_socket_module_globals,
};

MP_REGISTER_MODULE(MP_QSTR_socket, td_socket_module);

#if !MICROPY_PY_SSL
/* A build without mbedTLS (a PC program built without it): the generated
 * tables still list the tls module, so it exists, empty; ssl.wrap_socket()
 * then fails with ImportError ("no TLS in this build"). */
static const mp_rom_map_elem_t td_no_tls_table[] = {
    {MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_tls)},
};
static MP_DEFINE_CONST_DICT(td_no_tls_globals, td_no_tls_table);
const mp_obj_module_t mp_module_tls = {
    .base = {&mp_type_module},
    .globals = (mp_obj_dict_t *)&td_no_tls_globals,
};
#endif

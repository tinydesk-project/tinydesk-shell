#include "tdsh_espidf_internal.h"

#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <unistd.h>

#include "esp_log.h"
#include "esp_heap_caps.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "lwip/inet.h"
#include "lwip/sockets.h"

static const char *TAG = "tdsh-ftp";

#define TDSH_FTP_LISTENER_STACK_SIZE 6144U
#define TDSH_FTP_CLIENT_STACK_SIZE   10240U
#define TDSH_FTP_TRANSFER_BUF_SIZE   4096U
#define TDSH_FTP_MAX_CLIENTS         1U
#define TDSH_FTP_DATA_TIMEOUT_SEC    20

static volatile bool s_running;
static int s_listen_fd = -1;
static TaskHandle_t s_listener_task;
static uint16_t s_port = TDSH_DEFAULT_FTP_PORT;

static portMUX_TYPE s_clients_mux = portMUX_INITIALIZER_UNLOCKED;
static int s_client_fds[TDSH_FTP_MAX_CLIENTS];
static unsigned s_client_count;

/* Minimum free stack observed since the FTP server started (bytes on ESP-IDF). */
static volatile UBaseType_t s_listener_stack_min;
static volatile UBaseType_t s_client_stack_min;

typedef struct
{
    int ctrl;
    int pasv;
    char cwd[TDSH_MAX_PATH];
    char username[TDSH_USERNAME_MAX];
    bool authed;
    char rename_from[TDSH_MAX_PATH + sizeof(TDSH_MOUNT_POINT) + 16];
} ftp_client_t;

typedef struct
{
    int fd;
} ftp_client_task_arg_t;

static int send_all(int fd, const void *data, size_t len)
{
    const char *p = (const char *)data;
    while (len > 0)
    {
        int n = send(fd, p, len, 0);
        if (n < 0)
        {
            if (errno == EINTR)
                continue;
            return -1;
        }
        if (n == 0)
            return -1;
        p += n;
        len -= (size_t)n;
    }
    return 0;
}

static void replyf(int fd, const char *fmt, ...)
{
    char buf[512];
    va_list ap;
    va_start(ap, fmt);
    int n = vsnprintf(buf, sizeof(buf), fmt, ap);
    va_end(ap);
    if (n < 0)
        return;
    size_t len = (size_t)n < sizeof(buf) ? (size_t)n : sizeof(buf) - 1U;
    (void)send_all(fd, buf, len);
}

static int recv_line(int fd, char *buf, size_t size)
{
    size_t n = 0;
    while (n + 1U < size && s_running)
    {
        char c;
        int r = recv(fd, &c, 1, 0);
        if (r == 0)
            return 0;
        if (r < 0)
        {
            if (errno == EINTR)
                continue;
            if (errno == EAGAIN || errno == EWOULDBLOCK)
                continue;
            return -1;
        }
        if (c == '\n')
            break;
        if (c != '\r')
            buf[n++] = c;
    }
    buf[n] = '\0';
    return (int)n;
}

static void ftp_fake_session(const ftp_client_t *c, tdsh_session_t *s)
{
    memset(s, 0, sizeof(*s));
    snprintf(s->username, sizeof(s->username), "%s", c->username[0] ? c->username : "root");
    if (strcmp(s->username, "root") == 0)
    {
        snprintf(s->home, sizeof(s->home), "/root");
    }
    else
    {
        snprintf(s->home, sizeof(s->home), "/home/%s", s->username);
    }
    snprintf(s->cwd, sizeof(s->cwd), "%s", c->cwd);
}

static int ftp_path(ftp_client_t *c, const char *input,
                    char *real, size_t rsize,
                    char *logical, size_t lsize)
{
    tdsh_session_t *s = calloc(1, sizeof(*s));
    if (!s)
    {
        ESP_LOGE(TAG, "unable to allocate FTP path session (%u bytes)",
                 (unsigned)sizeof(*s));
        return -1;
    }

    ftp_fake_session(c, s);
    int rc = tdsh_path_to_real(s,
                               (input && input[0]) ? input : ".",
                               real, rsize, logical, lsize);
    free(s);
    return rc;
}

static void *ftp_transfer_alloc(size_t size)
{
    void *p = NULL;
#ifdef CONFIG_SPIRAM
    p = heap_caps_malloc(size, MALLOC_CAP_SPIRAM | MALLOC_CAP_8BIT);
#endif
    if (!p)
        p = heap_caps_malloc(size, MALLOC_CAP_8BIT);
    return p;
}

static void set_socket_timeout(int fd, int optname, int seconds)
{
    struct timeval tv = {.tv_sec = seconds, .tv_usec = 0};
    (void)setsockopt(fd, SOL_SOCKET, optname, &tv, sizeof(tv));
}

static void close_pasv(ftp_client_t *c)
{
    if (c->pasv >= 0)
    {
        close(c->pasv);
        c->pasv = -1;
    }
}

static int open_passive(ftp_client_t *c, bool epsv)
{
    close_pasv(c);

    int fd = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    if (fd < 0)
        return -1;

    int yes = 1;
    (void)setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));

    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = 0;

    if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) != 0 ||
        listen(fd, 1) != 0)
    {
        close(fd);
        return -1;
    }

    socklen_t alen = sizeof(addr);
    if (getsockname(fd, (struct sockaddr *)&addr, &alen) != 0)
    {
        close(fd);
        return -1;
    }

    set_socket_timeout(fd, SO_RCVTIMEO, TDSH_FTP_DATA_TIMEOUT_SEC);
    c->pasv = fd;

    uint16_t port = ntohs(addr.sin_port);
    if (epsv)
    {
        replyf(c->ctrl, "229 Entering Extended Passive Mode (|||%u|)\r\n", port);
    }
    else
    {
        struct sockaddr_in local = {0};
        socklen_t llen = sizeof(local);
        if (getsockname(c->ctrl, (struct sockaddr *)&local, &llen) != 0)
        {
            close_pasv(c);
            return -1;
        }

        uint32_t ip = ntohl(local.sin_addr.s_addr);
        replyf(c->ctrl,
               "227 Entering Passive Mode (%u,%u,%u,%u,%u,%u)\r\n",
               (unsigned)((ip >> 24) & 0xffU),
               (unsigned)((ip >> 16) & 0xffU),
               (unsigned)((ip >> 8) & 0xffU),
               (unsigned)(ip & 0xffU),
               (unsigned)(port >> 8),
               (unsigned)(port & 0xffU));
    }

    return 0;
}

static int accept_data(ftp_client_t *c)
{
    if (c->pasv < 0)
    {
        replyf(c->ctrl, "425 Use PASV or EPSV first.\r\n");
        return -1;
    }

    struct sockaddr_in peer = {0};
    socklen_t plen = sizeof(peer);
    int d = accept(c->pasv, (struct sockaddr *)&peer, &plen);
    close_pasv(c);

    if (d < 0)
    {
        replyf(c->ctrl, "425 Cannot open data connection.\r\n");
        return -1;
    }

    set_socket_timeout(d, SO_RCVTIMEO, TDSH_FTP_DATA_TIMEOUT_SEC);
    set_socket_timeout(d, SO_SNDTIMEO, TDSH_FTP_DATA_TIMEOUT_SEC);
    return d;
}

static void list_one(int data, const char *real, const char *name)
{
    struct stat st;
    if (stat(real, &st) != 0)
        return;

    char line[512];
    int n = snprintf(line, sizeof(line),
                     "%crw-r--r-- 1 tdsh tdsh %10ld Jan 01 00:00 %s\r\n",
                     S_ISDIR(st.st_mode) ? 'd' : '-',
                     (long)st.st_size,
                     name);
    if (n > 0)
    {
        size_t len = (size_t)n < sizeof(line) ? (size_t)n : sizeof(line) - 1U;
        (void)send_all(data, line, len);
    }
}

static void do_list(ftp_client_t *c, const char *arg, bool names_only)
{
    char real[TDSH_MAX_PATH + sizeof(TDSH_MOUNT_POINT) + 32];
    char logical[TDSH_MAX_PATH];

    if (ftp_path(c, arg && arg[0] ? arg : ".",
                 real, sizeof(real), logical, sizeof(logical)) != 0)
    {
        replyf(c->ctrl, "550 Invalid path.\r\n");
        return;
    }

    struct stat st;
    if (stat(real, &st) != 0)
    {
        replyf(c->ctrl, "550 Path not found.\r\n");
        return;
    }

    replyf(c->ctrl, "150 Opening data connection.\r\n");
    int data = accept_data(c);
    if (data < 0)
        return;

    if (S_ISDIR(st.st_mode))
    {
        DIR *d = opendir(real);
        if (d)
        {
            struct dirent *e;
            while ((e = readdir(d)) != NULL)
            {
                if (!strcmp(e->d_name, ".") || !strcmp(e->d_name, ".."))
                    continue;

                if (names_only)
                {
                    replyf(data, "%s\r\n", e->d_name);
                }
                else
                {
                    char child[sizeof(real) + 64];
                    int n = snprintf(child, sizeof(child), "%s/%s", real, e->d_name);
                    if (n > 0 && n < (int)sizeof(child))
                    {
                        list_one(data, child, e->d_name);
                    }
                }
            }
            closedir(d);
        }
    }
    else
    {
        const char *name = strrchr(logical, '/');
        name = name ? name + 1 : logical;
        if (names_only)
            replyf(data, "%s\r\n", name);
        else
            list_one(data, real, name);
    }

    shutdown(data, SHUT_RDWR);
    close(data);
    replyf(c->ctrl, "226 Transfer complete.\r\n");
}

static void do_retr(ftp_client_t *c, const char *arg)
{
    char real[TDSH_MAX_PATH + sizeof(TDSH_MOUNT_POINT) + 32];
    if (!arg || !arg[0] || ftp_path(c, arg, real, sizeof(real), NULL, 0) != 0)
    {
        replyf(c->ctrl, "550 Invalid path.\r\n");
        return;
    }

    FILE *f = fopen(real, "rb");
    if (!f)
    {
        replyf(c->ctrl, "550 File unavailable.\r\n");
        return;
    }

    replyf(c->ctrl, "150 Opening binary data connection.\r\n");
    int data = accept_data(c);
    if (data < 0)
    {
        fclose(f);
        return;
    }

    char *buf = ftp_transfer_alloc(TDSH_FTP_TRANSFER_BUF_SIZE);
    if (!buf)
    {
        fclose(f);
        shutdown(data, SHUT_RDWR);
        close(data);
        replyf(c->ctrl, "451 Insufficient memory for transfer.\r\n");
        return;
    }

    bool ok = true;
    size_t n;
    while ((n = fread(buf, 1, TDSH_FTP_TRANSFER_BUF_SIZE, f)) > 0)
    {
        if (send_all(data, buf, n) != 0)
        {
            ok = false;
            break;
        }
    }
    if (ferror(f))
        ok = false;

    free(buf);
    fclose(f);
    shutdown(data, SHUT_RDWR);
    close(data);

    if (ok)
        replyf(c->ctrl, "226 Transfer complete.\r\n");
    else
        replyf(c->ctrl, "426 Data connection error; transfer aborted.\r\n");
}

static void do_stor(ftp_client_t *c, const char *arg)
{
    char real[TDSH_MAX_PATH + sizeof(TDSH_MOUNT_POINT) + 32];
    if (!arg || !arg[0] || ftp_path(c, arg, real, sizeof(real), NULL, 0) != 0)
    {
        replyf(c->ctrl, "550 Invalid path.\r\n");
        return;
    }

    FILE *f = fopen(real, "wb");
    if (!f)
    {
        replyf(c->ctrl, "550 Cannot create file.\r\n");
        return;
    }

    replyf(c->ctrl, "150 Opening binary data connection.\r\n");
    int data = accept_data(c);
    if (data < 0)
    {
        fclose(f);
        return;
    }

    char *buf = ftp_transfer_alloc(TDSH_FTP_TRANSFER_BUF_SIZE);
    if (!buf)
    {
        fclose(f);
        shutdown(data, SHUT_RDWR);
        close(data);
        replyf(c->ctrl, "451 Insufficient memory for transfer.\r\n");
        return;
    }

    bool ok = true;
    for (;;)
    {
        int n = recv(data, buf, TDSH_FTP_TRANSFER_BUF_SIZE, 0);
        if (n > 0)
        {
            if (fwrite(buf, 1, (size_t)n, f) != (size_t)n)
            {
                ok = false;
                break;
            }
            continue;
        }
        if (n == 0)
            break; /* Normal EOF from FileZilla. */

        if (errno == EINTR)
            continue;
        ok = false;
        break;
    }

    if (fflush(f) != 0)
        ok = false;

    free(buf);
    fclose(f);
    shutdown(data, SHUT_RDWR);
    close(data);

    if (ok)
        replyf(c->ctrl, "226 Transfer complete.\r\n");
    else
        replyf(c->ctrl, "426 Data connection error; transfer aborted.\r\n");
}

static void update_client_stack_min(void)
{
    UBaseType_t now = uxTaskGetStackHighWaterMark(NULL);
    taskENTER_CRITICAL(&s_clients_mux);
    if (s_client_stack_min == 0 || now < s_client_stack_min)
    {
        s_client_stack_min = now;
    }
    taskEXIT_CRITICAL(&s_clients_mux);
}

static bool register_client_fd(int fd)
{
    bool ok = false;
    taskENTER_CRITICAL(&s_clients_mux);
    if (s_client_count < TDSH_FTP_MAX_CLIENTS)
    {
        for (unsigned i = 0; i < TDSH_FTP_MAX_CLIENTS; ++i)
        {
            if (s_client_fds[i] < 0)
            {
                s_client_fds[i] = fd;
                ++s_client_count;
                ok = true;
                break;
            }
        }
    }
    taskEXIT_CRITICAL(&s_clients_mux);
    return ok;
}

static void unregister_client_fd(int fd)
{
    taskENTER_CRITICAL(&s_clients_mux);
    for (unsigned i = 0; i < TDSH_FTP_MAX_CLIENTS; ++i)
    {
        if (s_client_fds[i] == fd)
        {
            s_client_fds[i] = -1;
            if (s_client_count > 0)
                --s_client_count;
            break;
        }
    }
    taskEXIT_CRITICAL(&s_clients_mux);
}

static unsigned get_client_count(void)
{
    unsigned count;
    taskENTER_CRITICAL(&s_clients_mux);
    count = s_client_count;
    taskEXIT_CRITICAL(&s_clients_mux);
    return count;
}

static void shutdown_all_clients(void)
{
    int fds[TDSH_FTP_MAX_CLIENTS];

    taskENTER_CRITICAL(&s_clients_mux);
    for (unsigned i = 0; i < TDSH_FTP_MAX_CLIENTS; ++i)
    {
        fds[i] = s_client_fds[i];
    }
    taskEXIT_CRITICAL(&s_clients_mux);

    for (unsigned i = 0; i < TDSH_FTP_MAX_CLIENTS; ++i)
    {
        if (fds[i] >= 0)
            (void)shutdown(fds[i], SHUT_RDWR);
    }
}

static void ftp_client_session(int fd)
{
    ftp_client_t c = {.ctrl = fd, .pasv = -1};
    snprintf(c.cwd, sizeof(c.cwd), "/");

    set_socket_timeout(fd, SO_RCVTIMEO, 1);
    set_socket_timeout(fd, SO_SNDTIMEO, TDSH_FTP_DATA_TIMEOUT_SEC);

    replyf(fd, "220 TinyDesk Shell %s FTP server ready.\r\n", TDSH_VERSION);

    char line[512];
    while (s_running)
    {
        int n = recv_line(fd, line, sizeof(line));
        if (n == 0)
            break;
        if (n < 0)
            continue;

        char *arg = strchr(line, ' ');
        if (arg)
        {
            *arg++ = '\0';
            while (*arg == ' ')
                ++arg;
        }
        else
        {
            arg = (char *)"";
        }

        for (char *p = line; *p; ++p)
        {
            *p = (char)toupper((unsigned char)*p);
        }

        if (!strcmp(line, "USER"))
        {
            snprintf(c.username, sizeof(c.username), "%s", arg);
            c.authed = false;
            replyf(fd, "331 Password required for %s.\r\n", c.username);
        }
        else if (!strcmp(line, "PASS"))
        {
            if (tdsh_user_authenticate_remote(c.username, arg))
            {
                c.authed = true;
                if (!strcmp(c.username, "root"))
                {
                    snprintf(c.cwd, sizeof(c.cwd), "/root");
                }
                else
                {
                    snprintf(c.cwd, sizeof(c.cwd), "/home/%s", c.username);
                }
                replyf(fd, "230 Login successful.\r\n");
            }
            else
            {
                replyf(fd, "530 Login incorrect.\r\n");
            }
        }
        else if (!strcmp(line, "QUIT"))
        {
            replyf(fd, "221 Goodbye.\r\n");
            break;
        }
        else if (!strcmp(line, "SYST"))
        {
            replyf(fd, "215 UNIX Type: L8\r\n");
        }
        else if (!strcmp(line, "FEAT"))
        {
            replyf(fd,
                   "211-Features\r\n"
                   " UTF8\r\n"
                   " SIZE\r\n"
                   " EPSV\r\n"
                   "211 End\r\n");
        }
        else if (!strcmp(line, "OPTS"))
        {
            replyf(fd, "200 OPTS accepted.\r\n");
        }
        else if (!strcmp(line, "CLNT"))
        {
            replyf(fd, "200 Client accepted.\r\n");
        }
        else if (!strcmp(line, "NOOP"))
        {
            replyf(fd, "200 OK.\r\n");
        }
        else if (!c.authed)
        {
            replyf(fd, "530 Please login with USER and PASS.\r\n");
        }
        else if (!strcmp(line, "PWD") || !strcmp(line, "XPWD"))
        {
            replyf(fd, "257 \"%s\" is current directory.\r\n", c.cwd);
        }
        else if (!strcmp(line, "CWD"))
        {
            char real[TDSH_MAX_PATH + sizeof(TDSH_MOUNT_POINT) + 32];
            char logical[TDSH_MAX_PATH];
            struct stat st;
            if (ftp_path(&c, arg, real, sizeof(real), logical, sizeof(logical)) == 0 &&
                stat(real, &st) == 0 && S_ISDIR(st.st_mode))
            {
                snprintf(c.cwd, sizeof(c.cwd), "%s", logical);
                replyf(fd, "250 Directory changed.\r\n");
            }
            else
            {
                replyf(fd, "550 Directory unavailable.\r\n");
            }
        }
        else if (!strcmp(line, "CDUP"))
        {
            char real[TDSH_MAX_PATH + sizeof(TDSH_MOUNT_POINT) + 32];
            char logical[TDSH_MAX_PATH];
            if (ftp_path(&c, "..", real, sizeof(real), logical, sizeof(logical)) == 0)
            {
                snprintf(c.cwd, sizeof(c.cwd), "%s", logical);
                replyf(fd, "250 Directory changed.\r\n");
            }
            else
            {
                replyf(fd, "550 Failed.\r\n");
            }
        }
        else if (!strcmp(line, "TYPE"))
        {
            replyf(fd, "200 Type set.\r\n");
        }
        else if (!strcmp(line, "PASV"))
        {
            if (open_passive(&c, false) != 0)
            {
                replyf(fd, "425 Cannot enter passive mode.\r\n");
            }
        }
        else if (!strcmp(line, "EPSV"))
        {
            if (open_passive(&c, true) != 0)
            {
                replyf(fd, "425 Cannot enter passive mode.\r\n");
            }
        }
        else if (!strcmp(line, "PORT") || !strcmp(line, "EPRT"))
        {
            replyf(fd, "502 Active mode not supported; use PASV/EPSV.\r\n");
        }
        else if (!strcmp(line, "LIST"))
        {
            do_list(&c, arg, false);
        }
        else if (!strcmp(line, "NLST"))
        {
            do_list(&c, arg, true);
        }
        else if (!strcmp(line, "RETR"))
        {
            do_retr(&c, arg);
        }
        else if (!strcmp(line, "STOR"))
        {
            do_stor(&c, arg);
        }
        else if (!strcmp(line, "SIZE"))
        {
            char real[TDSH_MAX_PATH + sizeof(TDSH_MOUNT_POINT) + 32];
            struct stat st;
            if (ftp_path(&c, arg, real, sizeof(real), NULL, 0) == 0 &&
                stat(real, &st) == 0 && !S_ISDIR(st.st_mode))
            {
                replyf(fd, "213 %ld\r\n", (long)st.st_size);
            }
            else
            {
                replyf(fd, "550 File unavailable.\r\n");
            }
        }
        else if (!strcmp(line, "DELE"))
        {
            char real[TDSH_MAX_PATH + sizeof(TDSH_MOUNT_POINT) + 32];
            if (ftp_path(&c, arg, real, sizeof(real), NULL, 0) == 0 &&
                unlink(real) == 0)
            {
                replyf(fd, "250 Deleted.\r\n");
            }
            else
            {
                replyf(fd, "550 Delete failed.\r\n");
            }
        }
        else if (!strcmp(line, "MKD") || !strcmp(line, "XMKD"))
        {
            char real[TDSH_MAX_PATH + sizeof(TDSH_MOUNT_POINT) + 32];
            char logical[TDSH_MAX_PATH];
            if (ftp_path(&c, arg, real, sizeof(real), logical, sizeof(logical)) == 0 &&
                mkdir(real, 0755) == 0)
            {
                replyf(fd, "257 \"%s\" created.\r\n", logical);
            }
            else
            {
                replyf(fd, "550 Create directory failed.\r\n");
            }
        }
        else if (!strcmp(line, "RMD") || !strcmp(line, "XRMD"))
        {
            char real[TDSH_MAX_PATH + sizeof(TDSH_MOUNT_POINT) + 32];
            if (ftp_path(&c, arg, real, sizeof(real), NULL, 0) == 0 &&
                rmdir(real) == 0)
            {
                replyf(fd, "250 Removed.\r\n");
            }
            else
            {
                replyf(fd, "550 Remove failed.\r\n");
            }
        }
        else if (!strcmp(line, "RNFR"))
        {
            struct stat st;
            if (ftp_path(&c, arg, c.rename_from, sizeof(c.rename_from), NULL, 0) == 0 &&
                stat(c.rename_from, &st) == 0)
            {
                replyf(fd, "350 Ready for RNTO.\r\n");
            }
            else
            {
                c.rename_from[0] = '\0';
                replyf(fd, "550 Source unavailable.\r\n");
            }
        }
        else if (!strcmp(line, "RNTO"))
        {
            char real[TDSH_MAX_PATH + sizeof(TDSH_MOUNT_POINT) + 32];
            if (c.rename_from[0] &&
                ftp_path(&c, arg, real, sizeof(real), NULL, 0) == 0 &&
                rename(c.rename_from, real) == 0)
            {
                replyf(fd, "250 Rename successful.\r\n");
            }
            else
            {
                replyf(fd, "550 Rename failed.\r\n");
            }
            c.rename_from[0] = '\0';
        }
        else
        {
            replyf(fd, "502 Command not implemented.\r\n");
        }

        update_client_stack_min();
    }

    close_pasv(&c);
    shutdown(fd, SHUT_RDWR);
    close(fd);
}

static void ftp_client_task(void *arg)
{
    ftp_client_task_arg_t *ctx = (ftp_client_task_arg_t *)arg;
    int fd = ctx->fd;
    free(ctx);

    ftp_client_session(fd);
    update_client_stack_min();
    unregister_client_fd(fd);

    ESP_LOGI(TAG, "FTP client disconnected; active clients=%u, min free client stack=%u bytes",
             get_client_count(), (unsigned)s_client_stack_min);

    vTaskDelete(NULL);
}

static void ftp_listener_task(void *arg)
{
    (void)arg;

    int fd = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    if (fd < 0)
        goto done;

    int yes = 1;
    (void)setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));
    set_socket_timeout(fd, SO_RCVTIMEO, 1);

    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(s_port);

    if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) != 0 ||
        listen(fd, (int)TDSH_FTP_MAX_CLIENTS) != 0)
    {
        ESP_LOGE(TAG, "FTP bind/listen on port %u failed: errno=%d", s_port, errno);
        close(fd);
        goto done;
    }

    s_listen_fd = fd;
    ESP_LOGI(TAG, "FTP server listening on port %u (max clients=%u)",
             s_port, (unsigned)TDSH_FTP_MAX_CLIENTS);

    while (s_running)
    {
        struct sockaddr_in peer = {0};
        socklen_t plen = sizeof(peer);
        int c = accept(fd, (struct sockaddr *)&peer, &plen);
        if (c < 0)
        {
            if (errno == EINTR)
                continue;
            if (errno == EAGAIN || errno == EWOULDBLOCK)
            {
                UBaseType_t now = uxTaskGetStackHighWaterMark(NULL);
                if (s_listener_stack_min == 0 || now < s_listener_stack_min)
                {
                    s_listener_stack_min = now;
                }
                continue;
            }
            if (!s_running)
                break;
            continue;
        }

        if (!s_running)
        {
            close(c);
            break;
        }

        if (!register_client_fd(c))
        {
            replyf(c, "421 Too many FTP connections. Try again later.\r\n");
            shutdown(c, SHUT_RDWR);
            close(c);
            continue;
        }

        ESP_LOGI(TAG, "FTP control client connected from %s (active=%u)",
                 inet_ntoa(peer.sin_addr), get_client_count());

        ftp_client_task_arg_t *ctx = malloc(sizeof(*ctx));
        if (!ctx)
        {
            replyf(c, "421 Server out of memory.\r\n");
            unregister_client_fd(c);
            shutdown(c, SHUT_RDWR);
            close(c);
            continue;
        }
        ctx->fd = c;

        if (xTaskCreate(ftp_client_task,
                        "tdsh_ftp_c",
                        TDSH_FTP_CLIENT_STACK_SIZE,
                        ctx,
                        4,
                        NULL) != pdPASS)
        {
            free(ctx);
            replyf(c, "421 Unable to create FTP session.\r\n");
            unregister_client_fd(c);
            shutdown(c, SHUT_RDWR);
            close(c);
            continue;
        }
    }

    shutdown(fd, SHUT_RDWR);
    close(fd);

done:
    s_listen_fd = -1;
    s_listener_task = NULL;
    s_running = false;
    vTaskDelete(NULL);
}

static void reset_client_slots(void)
{
    taskENTER_CRITICAL(&s_clients_mux);
    for (unsigned i = 0; i < TDSH_FTP_MAX_CLIENTS; ++i)
    {
        s_client_fds[i] = -1;
    }
    s_client_count = 0;
    s_listener_stack_min = 0;
    s_client_stack_min = 0;
    taskEXIT_CRITICAL(&s_clients_mux);
}

static int ftp_start(uint16_t port)
{
    if (!tdsh_remote_access_ready())
    {
        printf("ftp: change the factory root password with passwd first (old password: " TDSH_FACTORY_ROOT_PASSWORD ")\n");
        return 1;
    }
    if (s_running)
    {
        printf("FTP server is already running on port %u.\n", s_port);
        return 0;
    }

    if (!tdsh_network_is_reachable())
    {
        printf("ftp: no network interface is connected.\n");
        return 1;
    }

    reset_client_slots();
    s_port = port;
    s_running = true;

    if (xTaskCreate(ftp_listener_task,
                    "tdsh_ftp",
                    TDSH_FTP_LISTENER_STACK_SIZE,
                    NULL,
                    4,
                    &s_listener_task) != pdPASS)
    {
        s_running = false;
        s_listener_task = NULL;
        printf("ftp: failed to create server task\n");
        return 1;
    }

    printf("FTP server starting on port %u. Login with a tdsh username/password.\n",
           port);
    printf("FTP supports up to %u simultaneous control connections.\n",
           (unsigned)TDSH_FTP_MAX_CLIENTS);
    return 0;
}

static void ftp_stop(void)
{
    if (!s_running)
    {
        printf("FTP server is not running.\n");
        return;
    }

    s_running = false;

    if (s_listen_fd >= 0)
    {
        (void)shutdown(s_listen_fd, SHUT_RDWR);
    }
    shutdown_all_clients();

    printf("FTP server stopping.\n");
}

/* status and control for GUI front ends. */
bool tdsh_ftp_is_running(uint16_t *port)
{
    if (port)
        *port = s_port;
    return s_running;
}

int tdsh_ftp_set_running(bool on)
{
    if (on == s_running)
        return 0;
    if (on)
        return ftp_start(s_port ? s_port : TDSH_DEFAULT_FTP_PORT);
    ftp_stop();
    return 0;
}

int tdsh_cmd_ftp(tdsh_session_t *session, int argc, char **argv)
{
    if (argc < 2)
    {
        printf("usage: ftp <start|stop|restart|status> [port]\n");
        return 2;
    }

    if (!strcmp(argv[1], "status"))
    {
        if (s_running)
        {
            printf("FTP server: running on port %u\n", s_port);
            printf("FTP active clients: %u / %u\n",
                   get_client_count(), (unsigned)TDSH_FTP_MAX_CLIENTS);
            printf("FTP listener stack: %u bytes\n",
                   (unsigned)TDSH_FTP_LISTENER_STACK_SIZE);
            printf("FTP client stack: %u bytes each\n",
                   (unsigned)TDSH_FTP_CLIENT_STACK_SIZE);
            if (s_listener_stack_min)
            {
                printf("FTP minimum free listener stack observed: %u bytes\n",
                       (unsigned)s_listener_stack_min);
            }
            if (s_client_stack_min)
            {
                printf("FTP minimum free client stack observed: %u bytes\n",
                       (unsigned)s_client_stack_min);
            }
        }
        else
        {
            printf("FTP server: stopped\n");
        }
        return 0;
    }

    if (strcmp(session->username, "root") != 0 && !tdsh_is_physical_console())
    {
        printf("ftp: permission denied: root, or any user on the local console/desktop\n");
        return 1;
    }

    uint16_t port = TDSH_DEFAULT_FTP_PORT;
    if (argc >= 3)
    {
        char *end = NULL;
        long p = strtol(argv[2], &end, 10);
        if (!end || *end || p < 1 || p > 65535)
        {
            printf("ftp: invalid port\n");
            return 2;
        }
        port = (uint16_t)p;
    }

    if (!strcmp(argv[1], "start"))
        return ftp_start(port);

    if (!strcmp(argv[1], "stop"))
    {
        ftp_stop();
        return 0;
    }

    if (!strcmp(argv[1], "restart"))
    {
        ftp_stop();

        for (int i = 0; i < 60; ++i)
        {
            if (!s_listener_task && get_client_count() == 0)
                break;
            vTaskDelay(pdMS_TO_TICKS(50));
        }

        return ftp_start(port);
    }

    printf("usage: ftp <start|stop|restart|status> [port]\n");
    return 2;
}

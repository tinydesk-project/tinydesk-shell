# websocket: a small blocking WebSocket client for TinyDesk Shell's py
# (RFC 6455; ws:// and wss://). For asyncio, use aiohttp's
# ClientSession().ws_connect() instead.
#
#   import websocket
#   ws = websocket.create_connection("wss://echo.example.org/", timeout=10)
#   ws.send("hello")          # str: a text frame, bytes: a binary frame
#   print(ws.recv())          # str or bytes; answers pings by itself
#   ws.close()
import binascii
import random
import socket
import struct

OP_CONT = 0x0
OP_TEXT = 0x1
OP_BINARY = 0x2
OP_CLOSE = 0x8
OP_PING = 0x9
OP_PONG = 0xA


def _rand(n):
    return bytes(random.getrandbits(8) for _ in range(n))


class WebSocketException(Exception):
    pass


class WebSocketConnectionClosedException(WebSocketException):
    pass


def _split_url(url):
    if url.startswith("wss://"):
        secure, rest, port = True, url[6:], 443
    elif url.startswith("ws://"):
        secure, rest, port = False, url[5:], 80
    else:
        raise ValueError("url must start with ws:// or wss://")
    host, _, path = rest.partition("/")
    if ":" in host:
        host, p = host.rsplit(":", 1)
        port = int(p)
    return secure, host, port, "/" + path


class WebSocket:
    def __init__(self, sock):
        self.sock = sock
        self.connected = True

    def _read_exact(self, n):
        buf = b""
        while len(buf) < n:
            chunk = self.sock.read(n - len(buf))
            if not chunk:
                self.connected = False
                raise WebSocketConnectionClosedException("connection closed")
            buf += chunk
        return buf

    def send_frame(self, opcode, data=b""):
        if isinstance(data, str):
            data = data.encode()
        n = len(data)
        head = bytearray([0x80 | opcode])
        if n < 126:
            head.append(0x80 | n)
        elif n < 65536:
            head.append(0x80 | 126)
            head += struct.pack("!H", n)
        else:
            head.append(0x80 | 127)
            head += struct.pack("!Q", n)
        mask = _rand(4)
        head += mask
        body = bytearray(data)
        for i in range(n):
            body[i] ^= mask[i & 3]
        self.sock.write(head + body)

    def send(self, data):
        if not self.connected:
            raise WebSocketConnectionClosedException("connection closed")
        self.send_frame(OP_TEXT if isinstance(data, str) else OP_BINARY, data)

    def send_binary(self, data):
        self.send_frame(OP_BINARY, data)

    def ping(self, data=b""):
        self.send_frame(OP_PING, data)

    def recv_frame(self):
        """One frame: (fin, opcode, payload)."""
        b0, b1 = self._read_exact(2)
        n = b1 & 0x7F
        if n == 126:
            n = struct.unpack("!H", self._read_exact(2))[0]
        elif n == 127:
            n = struct.unpack("!Q", self._read_exact(8))[0]
        mask = self._read_exact(4) if b1 & 0x80 else None
        data = self._read_exact(n) if n else b""
        if mask:
            data = bytearray(data)
            for i in range(n):
                data[i] ^= mask[i & 3]
            data = bytes(data)
        return b0 & 0x80, b0 & 0x0F, data

    def recv(self):
        """The next message: str for text, bytes for binary."""
        opcode, parts = None, []
        while True:
            fin, op, data = self.recv_frame()
            if op == OP_PING:
                self.send_frame(OP_PONG, data)
                continue
            if op == OP_PONG:
                continue
            if op == OP_CLOSE:
                if self.connected:
                    try:
                        self.send_frame(OP_CLOSE, data[:2])
                    except OSError:
                        pass
                self.connected = False
                self.sock.close()
                raise WebSocketConnectionClosedException("closed by the server")
            if op != OP_CONT:
                opcode = op
            parts.append(data)
            if fin:
                msg = b"".join(parts)
                return msg.decode() if opcode == OP_TEXT else msg

    def close(self, status=1000):
        if self.connected:
            self.connected = False
            try:
                self.send_frame(OP_CLOSE, struct.pack("!H", status))
            except OSError:
                pass
        self.sock.close()

    def settimeout(self, t):
        self.sock.settimeout(t)

    def __enter__(self):
        return self

    def __exit__(self, *args):
        self.close()


def create_connection(url, timeout=None, header=None, verify=True):
    """Connect to url (ws:// or wss://); header: extra lines, as a list or
    dict; verify=False accepts any server certificate."""
    secure, host, port, path = _split_url(url)
    ai = socket.getaddrinfo(host, port, 0, socket.SOCK_STREAM)[0]
    sock = socket.socket(ai[0], socket.SOCK_STREAM, ai[2])
    sock.settimeout(timeout)
    try:
        sock.connect(ai[-1])
        if secure:
            import tls

            # The server's certificate is checked against the trusted CAs
            # (the firmware's bundle, the PC's roots); verify=False skips it.
            ctx = tls.SSLContext(tls.PROTOCOL_TLS_CLIENT)
            if not verify:
                ctx.verify_mode = tls.CERT_NONE
            sock = ctx.wrap_socket(sock, server_hostname=host)
        key = binascii.b2a_base64(_rand(16)).strip()
        req = (
            "GET %s HTTP/1.1\r\nHost: %s\r\nUpgrade: websocket\r\n"
            "Connection: Upgrade\r\nSec-WebSocket-Key: %s\r\n"
            "Sec-WebSocket-Version: 13\r\n" % (path, host, key.decode())
        )
        if isinstance(header, dict):
            header = ["%s: %s" % kv for kv in header.items()]
        for line in header or ():
            req += line + "\r\n"
        sock.write((req + "\r\n").encode())
        status = sock.readline()
        if not status.startswith(b"HTTP/1.1 101"):
            raise WebSocketException("handshake failed: " + status.decode().strip())
        while sock.readline() not in (b"\r\n", b""):
            pass
    except:
        sock.close()
        raise
    return WebSocket(sock)

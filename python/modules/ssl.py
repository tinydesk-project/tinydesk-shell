# ssl from micropython-lib (python-stdlib/ssl 0.2.1, MIT), with one change
# for TinyDesk Shell: SSLContext(PROTOCOL_TLS_CLIENT) checks the server's
# certificate against the trusted CAs, as in CPython (the original turns
# the check off). wrap_socket() keeps MicroPython's default, CERT_NONE.
import tls

if not hasattr(tls, "SSLContext"):
    # A PC program built without mbedTLS: sockets work, TLS does not.
    raise ImportError("no TLS in this build (built without mbedTLS)")

from tls import *


class SSLContext:
    def __init__(self, *args):
        self._context = tls.SSLContext(*args)

    @property
    def verify_mode(self):
        return self._context.verify_mode

    @verify_mode.setter
    def verify_mode(self, val):
        self._context.verify_mode = val

    def load_cert_chain(self, certfile, keyfile):
        if isinstance(certfile, str):
            with open(certfile, "rb") as f:
                certfile = f.read()
        if isinstance(keyfile, str):
            with open(keyfile, "rb") as f:
                keyfile = f.read()
        self._context.load_cert_chain(certfile, keyfile)

    def load_verify_locations(self, cafile=None, cadata=None):
        if cafile:
            with open(cafile, "rb") as f:
                cadata = f.read()
        self._context.load_verify_locations(cadata)

    def wrap_socket(
        self, sock, server_side=False, do_handshake_on_connect=True, server_hostname=None
    ):
        return self._context.wrap_socket(
            sock,
            server_side=server_side,
            do_handshake_on_connect=do_handshake_on_connect,
            server_hostname=server_hostname,
        )


def wrap_socket(
    sock,
    server_side=False,
    key=None,
    cert=None,
    cert_reqs=CERT_NONE,
    cadata=None,
    server_hostname=None,
    do_handshake=True,
):
    con = SSLContext(PROTOCOL_TLS_SERVER if server_side else PROTOCOL_TLS_CLIENT)
    if cert or key:
        con.load_cert_chain(cert, key)
    if cadata:
        con.load_verify_locations(cadata=cadata)
    con.verify_mode = cert_reqs
    return con.wrap_socket(
        sock,
        server_side=server_side,
        do_handshake_on_connect=do_handshake,
        server_hostname=server_hostname,
    )

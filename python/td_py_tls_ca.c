/*
 * td_py_tls_ca.c - the certificates py's ssl/tls trusts by default, so
 * https://, wss:// and MQTT over TLS check the server without a script
 * loading CAs of its own (SSLContext.load_verify_locations() replaces them):
 *
 *   boards   ESP-IDF's certificate bundle (CONFIG_MBEDTLS_CERTIFICATE_BUNDLE)
 *   Windows  the system's trusted root certificates (the ROOT store)
 *   Linux    the system's CA file (/etc/ssl/certs/ca-certificates.crt, ...)
 *
 * The PC programs also stay with TLS 1.2, like the boards.
 *
 * extmod/modtls_mbedtls.c calls td_py_ssl_default_ca() for every new
 * SSLContext (MICROPY_PY_SSL_DEFAULT_CA in mpconfigport.h).
 */
#include "py/mpconfig.h"

#if MICROPY_PY_SSL && !defined(TD_PY_GENHDR)

#include "mbedtls/ssl.h"
#include "mbedtls/x509_crt.h"

#if defined(ESP_PLATFORM)
#include "sdkconfig.h"
#if CONFIG_MBEDTLS_CERTIFICATE_BUNDLE
#include "esp_crt_bundle.h"
#endif

void td_py_ssl_default_ca(mbedtls_ssl_config *conf)
{
#if CONFIG_MBEDTLS_CERTIFICATE_BUNDLE
    esp_crt_bundle_attach(conf);
#else
    (void)conf;
#endif
}

#else /* the PC programs */

#include <stdbool.h>
#if defined(_WIN32)
#include <windows.h>
#include <wincrypt.h>
#endif

static mbedtls_x509_crt s_roots;
static bool s_loaded, s_have;

static void load_roots(void)
{
    s_loaded = true;
    mbedtls_x509_crt_init(&s_roots);
#if defined(_WIN32)
    HCERTSTORE store = CertOpenSystemStoreA(0, "ROOT");
    if (!store)
        return;
    const CERT_CONTEXT *c = NULL;
    while ((c = CertEnumCertificatesInStore(store, c)) != NULL)
        if (c->dwCertEncodingType == X509_ASN_ENCODING &&
            mbedtls_x509_crt_parse_der(&s_roots, c->pbCertEncoded, c->cbCertEncoded) == 0)
            s_have = true;
    CertCloseStore(store, 0);
#else
    static const char *const files[] = {
        "/etc/ssl/certs/ca-certificates.crt",   /* Debian, Ubuntu, Arch */
        "/etc/pki/tls/certs/ca-bundle.crt",     /* Fedora, RHEL */
        "/etc/ssl/ca-bundle.pem",               /* openSUSE */
        "/etc/ssl/cert.pem",                    /* Alpine, macOS */
    };
    for (size_t i = 0; i < sizeof(files) / sizeof(files[0]) && !s_have; i++)
        if (mbedtls_x509_crt_parse_file(&s_roots, files[i]) >= 0 && s_roots.raw.len)
            s_have = true;   /* >= 0: some certificates may be skipped */
#endif
}

void td_py_ssl_default_ca(mbedtls_ssl_config *conf)
{
     /* TLS 1.2, as on the boards (ESP-IDF's mbedTLS configuration): the PC
     * build's TLS 1.3 handshake fails in mbedTLS ("internal error"). */
    mbedtls_ssl_conf_max_tls_version(conf, MBEDTLS_SSL_VERSION_TLS1_2);
    if (!s_loaded)
        load_roots();   /* once per program; they stay for later scripts */
    if (s_have)
        mbedtls_ssl_conf_ca_chain(conf, &s_roots, NULL);
}

#endif
#endif

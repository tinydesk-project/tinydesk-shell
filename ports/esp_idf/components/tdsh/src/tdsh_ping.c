#include "tdsh_espidf_internal.h"

#include <inttypes.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"
#include "lwip/inet.h"
#include "lwip/netdb.h"
#include "lwip/sockets.h"
#include "ping/ping_sock.h"

/*
 * ESP-IDF 5.3.1's ESP_PING_DEFAULT_CONFIG() uses ESP_TASK_PING_STACK,
 * which is only 2048 bytes (+ TASK_EXTRA_STACK_SIZE). That is marginal
 * once our callbacks perform several esp_ping_get_profile() calls and
 * format their lines. Give the dedicated ping worker enough room.
 *
 * ESP-IDF FreeRTOS task stack sizes are specified in bytes.
 */
#define TDSH_PING_TASK_STACK_SIZE 6144U

/*
 * The callbacks run in ESP-IDF's ping task, whose stdout is not the
 * session's (a TinyDesk Terminal window redirects stdout per task). They
 * queue their lines; the command's own task prints them.
 */
#define PING_LINE_MAX   112
#define PING_LINE_QUEUE 8

typedef struct
{
    SemaphoreHandle_t done;
    QueueHandle_t lines;
} ping_ctx_t;

static void queue_line(ping_ctx_t *ctx, const char *fmt, ...) __attribute__((format(printf, 2, 3)));

static void queue_line(ping_ctx_t *ctx, const char *fmt, ...)
{
    char line[PING_LINE_MAX];
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(line, sizeof(line), fmt, ap);
    va_end(ap);
    if (ctx != NULL && ctx->lines != NULL)
    {
        (void)xQueueSend(ctx->lines, line, pdMS_TO_TICKS(200));
    }
}

static void on_success(esp_ping_handle_t hdl, void *args)
{
    ping_ctx_t *ctx = (ping_ctx_t *)args;

    uint8_t ttl = 0;
    uint16_t seqno = 0;
    uint32_t elapsed = 0;
    uint32_t len = 0;
    ip_addr_t addr;
    memset(&addr, 0, sizeof(addr));

    (void)esp_ping_get_profile(hdl, ESP_PING_PROF_SEQNO,
                               &seqno, sizeof(seqno));
    (void)esp_ping_get_profile(hdl, ESP_PING_PROF_TTL,
                               &ttl, sizeof(ttl));
    (void)esp_ping_get_profile(hdl, ESP_PING_PROF_IPADDR,
                               &addr, sizeof(addr));
    (void)esp_ping_get_profile(hdl, ESP_PING_PROF_SIZE,
                               &len, sizeof(len));
    (void)esp_ping_get_profile(hdl, ESP_PING_PROF_TIMEGAP,
                               &elapsed, sizeof(elapsed));

    queue_line(ctx, "%" PRIu32 " bytes from %s icmp_seq=%" PRIu16 " ttl=%u time=%" PRIu32 " ms\n",
               len,
               ipaddr_ntoa(&addr),
               seqno,
               (unsigned)ttl,
               elapsed);
}

static void on_timeout(esp_ping_handle_t hdl, void *args)
{
    ping_ctx_t *ctx = (ping_ctx_t *)args;

    uint16_t seqno = 0;
    ip_addr_t addr;
    memset(&addr, 0, sizeof(addr));

    (void)esp_ping_get_profile(hdl, ESP_PING_PROF_SEQNO,
                               &seqno, sizeof(seqno));
    (void)esp_ping_get_profile(hdl, ESP_PING_PROF_IPADDR,
                               &addr, sizeof(addr));

    queue_line(ctx, "From %s icmp_seq=%" PRIu16 " timeout\n",
               ipaddr_ntoa(&addr), seqno);
}

static void on_end(esp_ping_handle_t hdl, void *args)
{
    ping_ctx_t *ctx = (ping_ctx_t *)args;

    uint32_t tx = 0;
    uint32_t rx = 0;
    uint32_t duration = 0;
    uint32_t loss = 0;
    ip_addr_t addr;
    memset(&addr, 0, sizeof(addr));

    (void)esp_ping_get_profile(hdl, ESP_PING_PROF_REQUEST,
                               &tx, sizeof(tx));
    (void)esp_ping_get_profile(hdl, ESP_PING_PROF_REPLY,
                               &rx, sizeof(rx));
    (void)esp_ping_get_profile(hdl, ESP_PING_PROF_DURATION,
                               &duration, sizeof(duration));
    (void)esp_ping_get_profile(hdl, ESP_PING_PROF_IPADDR,
                               &addr, sizeof(addr));

    /* Integer-only calculation: avoids floating-point work in ping task. */
    if (tx > 0)
    {
        const uint32_t lost = (tx >= rx) ? (tx - rx) : 0;
        loss = (lost * 100U) / tx;
    }

    queue_line(ctx, "--- %s ping statistics ---\n", ipaddr_ntoa(&addr));
    queue_line(ctx, "%" PRIu32 " packets transmitted, %" PRIu32 " received, %" PRIu32 "%% packet loss, time %" PRIu32 "ms\n",
               tx, rx, loss, duration);

    if (ctx != NULL && ctx->done != NULL)
    {
        xSemaphoreGive(ctx->done);
    }
}

static int resolve_target(const char *host, ip_addr_t *target)
{
    memset(target, 0, sizeof(*target));

    if (ipaddr_aton(host, target))
    {
        return 0;
    }

    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_socktype = SOCK_STREAM;

    struct addrinfo *res = NULL;
    if (getaddrinfo(host, NULL, &hints, &res) != 0 || res == NULL)
    {
        return -1;
    }

    if (res->ai_family == AF_INET)
    {
        const struct in_addr a =
            ((const struct sockaddr_in *)res->ai_addr)->sin_addr;
        inet_addr_to_ip4addr(ip_2_ip4(target), &a);
    }
    else if (res->ai_family == AF_INET6)
    {
        const struct in6_addr a6 =
            ((const struct sockaddr_in6 *)res->ai_addr)->sin6_addr;
        inet6_addr_to_ip6addr(ip_2_ip6(target), &a6);
    }
    else
    {
        freeaddrinfo(res);
        return -1;
    }

    freeaddrinfo(res);
    return 0;
}

/* Print what the ping task queued, for up to wait_ms. */
static void print_lines(ping_ctx_t *ctx, uint32_t wait_ms)
{
    char line[PING_LINE_MAX];
    while (xQueueReceive(ctx->lines, line, pdMS_TO_TICKS(wait_ms)) == pdTRUE)
    {
        fputs(line, stdout);
        fflush(stdout);
        wait_ms = 0;
    }
}

static int ping_one(const char *host, uint32_t count)
{
    ip_addr_t target;
    if (resolve_target(host, &target) != 0)
    {
        printf("ping: unknown host %s\n", host);
        return 1;
    }

    ping_ctx_t ctx = {
        .done = xSemaphoreCreateBinary(),
        .lines = xQueueCreate(PING_LINE_QUEUE, PING_LINE_MAX),
    };

    if (ctx.done == NULL || ctx.lines == NULL)
    {
        printf("ping: not enough memory\n");
        if (ctx.done != NULL)
            vSemaphoreDelete(ctx.done);
        if (ctx.lines != NULL)
            vQueueDelete(ctx.lines);
        return 1;
    }

    esp_ping_config_t cfg = ESP_PING_DEFAULT_CONFIG();
    cfg.target_addr = target;
    cfg.count = count;
    cfg.interval_ms = 1000;
    cfg.timeout_ms = 1000;
    cfg.task_stack_size = TDSH_PING_TASK_STACK_SIZE;

    esp_ping_callbacks_t cb = {
        .cb_args = &ctx,
        .on_ping_success = on_success,
        .on_ping_timeout = on_timeout,
        .on_ping_end = on_end,
    };

    esp_ping_handle_t handle = NULL;
    esp_err_t err = esp_ping_new_session(&cfg, &cb, &handle);
    if (err != ESP_OK)
    {
        printf("ping: cannot create session: %s\n", esp_err_to_name(err));
        vSemaphoreDelete(ctx.done);
        vQueueDelete(ctx.lines);
        return 1;
    }

    printf("PING %s (%s)\n", host, ipaddr_ntoa(&target));
    fflush(stdout);

    err = esp_ping_start(handle);
    if (err != ESP_OK)
    {
        printf("ping: start failed: %s\n", esp_err_to_name(err));
        (void)esp_ping_delete_session(handle);
        vSemaphoreDelete(ctx.done);
        vQueueDelete(ctx.lines);
        return 1;
    }

    /* count requests 1 s apart, 1 s timeout on the last one, plus slack. */
    const TickType_t deadline = xTaskGetTickCount() +
                                pdMS_TO_TICKS((count + 2U) * 1000U + 2000U);
    BaseType_t finished = pdFALSE;
    while (finished != pdTRUE && (int32_t)(deadline - xTaskGetTickCount()) > 0)
    {
        print_lines(&ctx, 100);
        finished = xSemaphoreTake(ctx.done, 0);
    }
    print_lines(&ctx, 0);

    if (finished != pdTRUE)
    {
        printf("ping: session timed out waiting for completion\n");
    }

    (void)esp_ping_stop(handle);
    (void)esp_ping_delete_session(handle);
    print_lines(&ctx, 0);
    vSemaphoreDelete(ctx.done);
    vQueueDelete(ctx.lines);

    return (finished == pdTRUE) ? 0 : 1;
}

int tdsh_cmd_ping(tdsh_session_t *session, int argc, char **argv)
{
    (void)session;

    /* ping [-c count] <host/address ...>: 4 requests per host by default. */
    uint32_t count = 4;
    int first = 1;
    if (argc >= 2 && strcmp(argv[1], "-c") == 0)
    {
        if (argc < 3)
        {
            printf("usage: ping [-c count] <host/address ...>\n");
            return 2;
        }
        char *end = NULL;
        const long n = strtol(argv[2], &end, 10);
        if (end == argv[2] || *end != '\0' || n < 1 || n > 100)
        {
            printf("ping: -c takes 1 to 100\n");
            return 2;
        }
        count = (uint32_t)n;
        first = 3;
    }
    if (first >= argc)
    {
        printf("usage: ping [-c count] <host/address ...>\n");
        return 2;
    }

    if (!tdsh_network_is_online())
    {
        printf("ping: no network interface is connected.\n");
        return 1;
    }

    int rc = 0;
    for (int i = first; i < argc; ++i)
    {
        if (ping_one(argv[i], count) != 0)
        {
            rc = 1;
        }
    }

    return rc;
}

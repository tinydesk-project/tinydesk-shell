#include "tdsh_espidf_internal.h"
#include "sdkconfig.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "esp_event.h"
#include "esp_log.h"
#include "esp_mac.h"
#include "esp_random.h"
#include "esp_timer.h"
#include "esp_netif.h"
#include "esp_wifi.h"
#include "esp_wifi_default.h"
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "freertos/semphr.h"
#include "freertos/task.h"
#include "nvs.h"

#define WIFI_NS              "ush_wifi"
#define WIFI_KEY             "db"
#define WIFI_DB_MAGIC        0x55535746u
#define WIFI_DB_VERSION      2u      /* v2 adds an owner per network */
#define WIFI_SAVED_MAX       12
#define WIFI_CONNECTED_BIT   BIT0
#define WIFI_FAIL_BIT        BIT1
#define WIFI_CONNECT_RETRIES 4
#define WIFI_SCAN_MAX        40

#if CONFIG_ESP_SYSTEM_EVENT_TASK_STACK_SIZE < 4096
#error "tdsh Wi-Fi requires CONFIG_ESP_SYSTEM_EVENT_TASK_STACK_SIZE >= 4096. Set it in menuconfig or use the supplied sdkconfig.defaults."
#endif

/* every saved network has an owner. "" means shared: added
 * by root or saved before owners existed. Anyone may connect to a shared
 * network, only root may change or remove it. A network added by another
 * user belongs to that user (and root may manage it too). */
typedef struct
{
    uint8_t used;
    char ssid[33];
    char password[65];
    char owner[TDSH_USERNAME_MAX];
} saved_network_t;

typedef struct
{
    uint32_t magic;
    uint16_t version;
    uint16_t count;
    saved_network_t entries[WIFI_SAVED_MAX];
} wifi_db_t;

/* Version 1 layout, read once to migrate existing networks. */
typedef struct
{
    uint8_t used;
    char ssid[33];
    char password[65];
} saved_network_v1_t;

typedef struct
{
    uint32_t magic;
    uint16_t version;
    uint16_t count;
    saved_network_v1_t entries[WIFI_SAVED_MAX];
} wifi_db_v1_t;

static const char *TAG = "tdsh-wifi";
static bool s_ready;
static bool s_wifi_driver_inited;
static bool s_wifi_started;
static bool s_wifi_event_registered;
static bool s_ip_event_registered;
static bool s_auto_reconnect;
static int s_retry;
static EventGroupHandle_t s_events;
static SemaphoreHandle_t s_init_mutex;
static portMUX_TYPE s_init_mutex_guard = portMUX_INITIALIZER_UNLOCKED;
static esp_netif_t *s_sta_netif;
static wifi_db_t s_db;
static esp_netif_t *s_ap_netif;   /* the access point's (below) */
static bool s_ap_up;

static esp_err_t wifi_db_save(void)
{
    nvs_handle_t h;
    esp_err_t err = nvs_open(WIFI_NS, NVS_READWRITE, &h);
    if (err != ESP_OK)
        return err;
    err = nvs_set_blob(h, WIFI_KEY, &s_db, sizeof(s_db));
    if (err == ESP_OK)
        err = nvs_commit(h);
    nvs_close(h);
    return err;
}

/* Convert a version 1 database: every existing network becomes shared. */
static bool wifi_db_migrate_v1(nvs_handle_t h, size_t len)
{
    if (len != sizeof(wifi_db_v1_t))
        return false;
    wifi_db_v1_t *old = calloc(1, sizeof(*old));
    if (!old)
        return false;
    size_t got = len;
    bool ok = nvs_get_blob(h, WIFI_KEY, old, &got) == ESP_OK && got == len &&
              old->magic == WIFI_DB_MAGIC && old->version == 1u;
    if (ok)
    {
        memset(&s_db, 0, sizeof(s_db));
        s_db.magic = WIFI_DB_MAGIC;
        s_db.version = WIFI_DB_VERSION;
        s_db.count = old->count;
        for (int i = 0; i < WIFI_SAVED_MAX; ++i)
        {
            s_db.entries[i].used = old->entries[i].used;
            memcpy(s_db.entries[i].ssid, old->entries[i].ssid, sizeof(s_db.entries[i].ssid));
            memcpy(s_db.entries[i].password, old->entries[i].password, sizeof(s_db.entries[i].password));
        }
        ESP_LOGI(TAG, "saved networks migrated to v2 (owners); existing ones are shared");
    }
    memset(old, 0, sizeof(*old));
    free(old);
    return ok;
}

static esp_err_t wifi_db_load(void)
{
    nvs_handle_t h;
    esp_err_t err = nvs_open(WIFI_NS, NVS_READWRITE, &h);
    if (err != ESP_OK)
        return err;
    size_t len = 0;
    err = nvs_get_blob(h, WIFI_KEY, NULL, &len);
    if (err == ESP_OK && len == sizeof(s_db))
    {
        err = nvs_get_blob(h, WIFI_KEY, &s_db, &len);
        nvs_close(h);
        if (err == ESP_OK && s_db.magic == WIFI_DB_MAGIC && s_db.version == WIFI_DB_VERSION)
            return ESP_OK;
    }
    else if (err == ESP_OK && wifi_db_migrate_v1(h, len))
    {
        nvs_close(h);
        return wifi_db_save();
    }
    else
    {
        nvs_close(h);
    }
    memset(&s_db, 0, sizeof(s_db));
    s_db.magic = WIFI_DB_MAGIC;
    s_db.version = WIFI_DB_VERSION;
    return ESP_OK;
}

/* NULL user = the system itself (boot-time autoconnect): may use all. */
static bool user_is_root(const char *user)
{
    return user == NULL || strcmp(user, "root") == 0;
}

static bool can_use(int i, const char *user)
{
    const saved_network_t *e = &s_db.entries[i];
    return e->used && (user_is_root(user) || !e->owner[0] || strcmp(e->owner, user) == 0);
}

static bool can_manage(int i, const char *user)
{
    const saved_network_t *e = &s_db.entries[i];
    return e->used && (user_is_root(user) || (e->owner[0] && strcmp(e->owner, user) == 0));
}

/* A network `user` may connect to: their own entry first, then a shared one. */
static int find_usable(const char *ssid, const char *user)
{
    int shared = -1;
    for (int i = 0; i < WIFI_SAVED_MAX; ++i)
    {
        if (!can_use(i, user) || strcmp(s_db.entries[i].ssid, ssid) != 0)
            continue;
        if (s_db.entries[i].owner[0] && !user_is_root(user))
            return i;
        if (shared < 0)
            shared = i;
    }
    return shared;
}

/* The entry for ssid that `user` may change or remove. */
static int find_managed(const char *ssid, const char *user)
{
    for (int i = 0; i < WIFI_SAVED_MAX; ++i)
        if (can_manage(i, user) && strcmp(s_db.entries[i].ssid, ssid) == 0)
            return i;
    return -1;
}

static int find_free(void)
{
    for (int i = 0; i < WIFI_SAVED_MAX; ++i)
        if (!s_db.entries[i].used)
            return i;
    return -1;
}

static void wifi_event(void *arg, esp_event_base_t base, int32_t id, void *data)
{
    (void)arg;
    if (base == IP_EVENT && id == IP_EVENT_STA_GOT_IP)
    {
        /*
         * Keep the default ESP event-loop callback deliberately tiny.
         * This function runs inside ESP-IDF's sys_evt task, whose default
         * stack in v5.3.x is only 2304 bytes. Do not printf/ESP_LOG, start
         * SNTP, allocate memory, or perform other heavyweight work here.
         *
         * The command task wakes on WIFI_CONNECTED_BIT and performs all
         * user-facing work after this callback returns.
         */
        (void)data;
        s_retry = 0;
        xEventGroupClearBits(s_events, WIFI_FAIL_BIT);
        xEventGroupSetBits(s_events, WIFI_CONNECTED_BIT);
        return;
    }

    if (base == WIFI_EVENT && id == WIFI_EVENT_STA_DISCONNECTED)
    {
        xEventGroupClearBits(s_events, WIFI_CONNECTED_BIT);
        if (s_auto_reconnect)
        {
            if (s_retry < WIFI_CONNECT_RETRIES)
            {
                ++s_retry;
                (void)esp_wifi_connect();
            }
            else
            {
                s_auto_reconnect = false;
                xEventGroupSetBits(s_events, WIFI_FAIL_BIT);
            }
        }
    }
}

static esp_err_t wifi_init_mutex_ensure(void)
{
    if (s_init_mutex)
        return ESP_OK;

    /* Allocate outside the critical section. If two callers race here,
     * install exactly one mutex and delete the unused candidate. */
    SemaphoreHandle_t candidate = xSemaphoreCreateMutex();
    if (!candidate)
        return ESP_ERR_NO_MEM;

    portENTER_CRITICAL(&s_init_mutex_guard);
    if (!s_init_mutex)
    {
        s_init_mutex = candidate;
        candidate = NULL;
    }
    portEXIT_CRITICAL(&s_init_mutex_guard);

    if (candidate)
        vSemaphoreDelete(candidate);
    return s_init_mutex ? ESP_OK : ESP_ERR_NO_MEM;
}

esp_err_t tdsh_wifi_init(void)
{
    esp_err_t err = wifi_init_mutex_ensure();
    if (err != ESP_OK)
        return err;

    if (xSemaphoreTake(s_init_mutex, portMAX_DELAY) != pdTRUE)
    {
        return ESP_ERR_TIMEOUT;
    }

    /*
     * Wi-Fi init can be requested simultaneously by the automatic network
     * manager and by a foreground command such as `wificonnect`.  Protect
     * the complete create/init/start sequence so WIFI_STA_DEF is created
     * exactly once.
     */
    if (s_ready)
    {
        xSemaphoreGive(s_init_mutex);
        return ESP_OK;
    }

    ESP_LOGI(TAG, "sys_evt stack configured to %d bytes",
             CONFIG_ESP_SYSTEM_EVENT_TASK_STACK_SIZE);

    err = esp_netif_init();
    if (err != ESP_OK && err != ESP_ERR_INVALID_STATE)
        goto out;

    err = esp_event_loop_create_default();
    if (err != ESP_OK && err != ESP_ERR_INVALID_STATE)
        goto out;

    if (!s_sta_netif)
    {
        s_sta_netif = esp_netif_create_default_wifi_sta();
        if (!s_sta_netif)
        {
            err = ESP_FAIL;
            goto out;
        }
    }

    if (!s_wifi_driver_inited)
    {
        wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
        err = esp_wifi_init(&cfg);
        if (err != ESP_OK)
            goto out;
        s_wifi_driver_inited = true;
    }

    if (!s_events)
    {
        s_events = xEventGroupCreate();
        if (!s_events)
        {
            err = ESP_ERR_NO_MEM;
            goto out;
        }
    }

    if (!s_wifi_event_registered)
    {
        err = esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID,
                                         wifi_event, NULL);
        if (err != ESP_OK)
            goto out;
        s_wifi_event_registered = true;
    }

    if (!s_ip_event_registered)
    {
        err = esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP,
                                         wifi_event, NULL);
        if (err != ESP_OK)
            goto out;
        s_ip_event_registered = true;
    }

    if (!s_wifi_started)
    {
        err = esp_wifi_set_mode(WIFI_MODE_STA);
        if (err != ESP_OK)
            goto out;

        err = esp_wifi_start();
        if (err != ESP_OK)
            goto out;
        s_wifi_started = true;
    }

    err = esp_wifi_set_ps(WIFI_PS_NONE);
    if (err != ESP_OK)
    {
        ESP_LOGW(TAG, "Failed to disable Wi-Fi power save: %s",
                 esp_err_to_name(err));
        /* Power-save configuration is not fatal to shell networking. */
        err = ESP_OK;
    }
    else
    {
        ESP_LOGI(TAG, "Wi-Fi power saving disabled for low-latency shell I/O");
    }

    err = wifi_db_load();
    if (err == ESP_OK)
        s_ready = true;

out:
    xSemaphoreGive(s_init_mutex);
    return err;
}

bool tdsh_wifi_is_connected(void)
{
    if (!s_ready || !s_events)
        return false;
    return (xEventGroupGetBits(s_events) & WIFI_CONNECTED_BIT) != 0;
}

static const char *auth_name(wifi_auth_mode_t auth)
{
    switch (auth)
    {
    case WIFI_AUTH_OPEN:
        return "OPEN";
    case WIFI_AUTH_WEP:
        return "WEP";
    case WIFI_AUTH_WPA_PSK:
        return "WPA";
    case WIFI_AUTH_WPA2_PSK:
        return "WPA2";
    case WIFI_AUTH_WPA_WPA2_PSK:
        return "WPA/WPA2";
    case WIFI_AUTH_WPA2_ENTERPRISE:
        return "WPA2-ENT";
    case WIFI_AUTH_WPA3_PSK:
        return "WPA3";
    case WIFI_AUTH_WPA2_WPA3_PSK:
        return "WPA2/WPA3";
    default:
        return "SECURED";
    }
}

static int scan_records(wifi_ap_record_t **out, uint16_t *count)
{
    esp_err_t err = tdsh_wifi_init();
    if (err != ESP_OK)
    {
        printf("Wi-Fi init failed: %s\n", esp_err_to_name(err));
        return 1;
    }
    err = esp_wifi_scan_start(NULL, true);
    if (err != ESP_OK)
    {
        printf("Wi-Fi scan failed: %s\n", esp_err_to_name(err));
        return 1;
    }
    uint16_t n = 0;
    err = esp_wifi_scan_get_ap_num(&n);
    if (err != ESP_OK)
    {
        printf("Wi-Fi scan count failed: %s\n", esp_err_to_name(err));
        return 1;
    }
    if (n > WIFI_SCAN_MAX)
        n = WIFI_SCAN_MAX;
    if (n == 0)
    {
        *out = NULL;
        *count = 0;
        return 0;
    }
    wifi_ap_record_t *records = calloc(n, sizeof(*records));
    if (!records)
        return 1;
    uint16_t got = n;
    err = esp_wifi_scan_get_ap_records(&got, records);
    if (err != ESP_OK)
    {
        free(records);
        printf("Wi-Fi scan read failed: %s\n", esp_err_to_name(err));
        return 1;
    }
    *out = records;
    *count = got;
    return 0;
}

static int connect_saved_idx_ex(int idx, bool verbose)
{
    if (idx < 0 || idx >= WIFI_SAVED_MAX || !s_db.entries[idx].used)
        return 1;
    saved_network_t *net = &s_db.entries[idx];

    wifi_config_t cfg;
    memset(&cfg, 0, sizeof(cfg));

    /*
     * ESP-IDF defines sta.ssid as uint8_t[32] and sta.password as
     * uint8_t[64].  These fields are allowed to use their full width, so
     * snprintf() is the wrong tool: GCC quite correctly warns that a
     * terminating NUL might not fit.  The structure is already zeroed, so
     * copy only the actual payload bytes and let esp_wifi_set_config() use
     * the fixed-width fields directly.
     */
    const size_t ssid_len = strnlen(net->ssid, sizeof(net->ssid));
    const size_t pass_len = strnlen(net->password, sizeof(net->password));

    if (ssid_len == 0 || ssid_len > sizeof(cfg.sta.ssid))
    {
        printf("Saved SSID has invalid length (%u).\n", (unsigned)ssid_len);
        return 1;
    }
    if (pass_len > sizeof(cfg.sta.password))
    {
        printf("Saved Wi-Fi password has invalid length (%u).\n", (unsigned)pass_len);
        return 1;
    }

    memcpy(cfg.sta.ssid, net->ssid, ssid_len);
    if (pass_len > 0)
    {
        memcpy(cfg.sta.password, net->password, pass_len);
    }

    cfg.sta.threshold.authmode = WIFI_AUTH_OPEN;

    s_auto_reconnect = false;
    (void)esp_wifi_disconnect();
    vTaskDelay(pdMS_TO_TICKS(100));
    esp_err_t err = esp_wifi_set_config(WIFI_IF_STA, &cfg);
    if (err != ESP_OK)
    {
        printf("Wi-Fi config failed: %s\n", esp_err_to_name(err));
        return 1;
    }

    xEventGroupClearBits(s_events, WIFI_CONNECTED_BIT | WIFI_FAIL_BIT);
    s_retry = 0;
    s_auto_reconnect = true;
    if (verbose)
        printf("Connecting to network: %s\n", net->ssid);
    err = esp_wifi_connect();
    if (err != ESP_OK)
    {
        s_auto_reconnect = false;
        printf("Wi-Fi connect failed: %s\n", esp_err_to_name(err));
        return 1;
    }

    EventBits_t bits = xEventGroupWaitBits(s_events, WIFI_CONNECTED_BIT | WIFI_FAIL_BIT,
                                           pdFALSE, pdFALSE, pdMS_TO_TICKS(20000));
    if (!(bits & WIFI_CONNECTED_BIT))
    {
        s_auto_reconnect = false;
        (void)esp_wifi_disconnect();
        if (verbose)
            printf("Unable to connect to %s.\n", net->ssid);
        return 1;
    }

    /*
     * We are back in the tdsh command task here, not sys_evt. It is safe
     * to query/format the IP address and start SNTP from this context.
     */
    esp_netif_ip_info_t ip_info;
    if (s_sta_netif && esp_netif_get_ip_info(s_sta_netif, &ip_info) == ESP_OK)
    {
        if (verbose)
        {
            printf("Connected to %s\n", net->ssid);
            printf("IP address: " IPSTR "\n", IP2STR(&ip_info.ip));
        }
    }

    tdsh_time_sync_start();
    return 0;
}

int tdsh_cmd_networks(tdsh_session_t *session, int argc, char **argv)
{
    (void)argc;
    (void)argv;
    esp_err_t err = wifi_db_load();
    if (err != ESP_OK)
    {
        printf("Network database error: %s\n", esp_err_to_name(err));
        return 1;
    }
    const char *user = session->username;
    int shown = 0;
    for (int i = 0; i < WIFI_SAVED_MAX; ++i)
    {
        if (!can_use(i, user))
            continue;
        const char *owner = s_db.entries[i].owner;
        printf("[%d] \"%s\"  (%s)\n", ++shown, s_db.entries[i].ssid,
               !owner[0] ? "shared" : strcmp(owner, user) == 0 ? "yours"
                                                               : owner);
    }
    if (!shown)
        printf("No saved networks. Use 'wifiadd <ssid>' to add one.\n");
    return 0;
}

/* Save (or update) `ssid` for `user`. Returns 0, -1 on error, -3 when full. */
static int save_for_user(const char *ssid, const char *password, const char *user)
{
    int idx = find_managed(ssid, user);
    if (idx < 0)
    {
        idx = find_free();
        if (idx < 0)
            return -3;
        memset(&s_db.entries[idx], 0, sizeof(s_db.entries[idx]));
        s_db.entries[idx].used = 1;
        /* root's networks are shared with everyone; other users own theirs */
        if (!user_is_root(user))
            snprintf(s_db.entries[idx].owner, sizeof(s_db.entries[idx].owner), "%s", user);
        s_db.count++;
    }
    snprintf(s_db.entries[idx].ssid, sizeof(s_db.entries[idx].ssid), "%s", ssid);
    snprintf(s_db.entries[idx].password, sizeof(s_db.entries[idx].password), "%s", password ? password : "");
    return wifi_db_save() == ESP_OK ? 0 : -1;
}

int tdsh_cmd_wifiadd(tdsh_session_t *session, int argc, char **argv)
{
    if (argc < 2 || argc > 3)
    {
        printf("usage: wifiadd <ssid> [password]\n");
        return 2;
    }
    if (strlen(argv[1]) > 32)
    {
        printf("SSID is too long.\n");
        return 1;
    }
    if (wifi_db_load() != ESP_OK)
        return 1;

    char password[65] = {0};
    if (argc == 3)
    {
        if (strlen(argv[2]) > 63)
        {
            printf("Wi-Fi password is too long.\n");
            return 1;
        }
        snprintf(password, sizeof(password), "%s", argv[2]);
    }
    else
    {
        if (!session->interactive)
        {
            printf("wifiadd needs a password argument in a background script\n");
            return 1;
        }
        int n = tdsh_console_readline("Network password (Enter for open network): ", password, sizeof(password), false);
        if (n < 0)
            return 1;
    }

    int rc = save_for_user(argv[1], password, session->username);
    memset(password, 0, sizeof(password));
    if (rc == -3)
    {
        printf("Saved network database is full.\n");
        return 1;
    }
    if (rc != 0)
    {
        printf("Failed to save network.\n");
        return 1;
    }
    printf("Network %s added successfully%s.\n", argv[1],
           user_is_root(session->username) ? " (shared with all users)" : "");
    return 0;
}

int tdsh_cmd_wifiremove(tdsh_session_t *session, int argc, char **argv)
{
    if (argc < 2)
    {
        printf("usage: wifiremove <ssid ...>\n");
        return 2;
    }
    if (wifi_db_load() != ESP_OK)
        return 1;
    int rc = 0;
    for (int a = 1; a < argc; ++a)
    {
        int idx = find_managed(argv[a], session->username);
        if (idx < 0)
        {
            if (find_usable(argv[a], session->username) >= 0)
                printf("Network '%s' is shared; only root can remove it.\n", argv[a]);
            else
                printf("Network '%s' not found in database.\n", argv[a]);
            rc = 1;
            continue;
        }
        memset(&s_db.entries[idx], 0, sizeof(s_db.entries[idx]));
        if (s_db.count)
            s_db.count--;
        printf("Network %s removed successfully.\n", argv[a]);
    }
    if (wifi_db_save() != ESP_OK)
        return 1;
    return rc;
}

int tdsh_cmd_wifiscan(tdsh_session_t *session, int argc, char **argv)
{
    (void)session;
    (void)argc;
    (void)argv;
    wifi_ap_record_t *records = NULL;
    uint16_t count = 0;
    if (scan_records(&records, &count) != 0)
        return 1;
    if (!count)
    {
        printf("No Wi-Fi networks found.\n");
        return 0;
    }
    printf("%-4s %-32s %6s %4s %s\n", "#", "SSID", "RSSI", "CH", "AUTH");
    for (uint16_t i = 0; i < count; ++i)
    {
        printf("%-4u %-32.32s %6d %4u %s\n", (unsigned)(i + 1),
               (char *)records[i].ssid, records[i].rssi, records[i].primary,
               auth_name(records[i].authmode));
    }
    free(records);
    return 0;
}

int tdsh_cmd_wificonnect(tdsh_session_t *session, int argc, char **argv)
{
    const char *user = session->username;
    esp_err_t err = tdsh_wifi_init();
    if (err != ESP_OK)
    {
        printf("Wi-Fi init failed: %s\n", esp_err_to_name(err));
        return 1;
    }
    if (wifi_db_load() != ESP_OK)
        return 1;

    if (argc == 2)
    {
        int idx = find_usable(argv[1], user);
        if (idx < 0)
        {
            printf("Network '%s' not found in database.\n", argv[1]);
            return 1;
        }
        return connect_saved_idx_ex(idx, true);
    }
    if (argc != 1)
    {
        printf("usage: wificonnect [saved_ssid]\n");
        return 2;
    }

    bool any = false;
    for (int i = 0; i < WIFI_SAVED_MAX; ++i)
        any = any || can_use(i, user);
    if (!any)
    {
        printf("No saved networks. Use 'wifiadd <ssid>' first.\n");
        return 1;
    }
    printf("Scanning for available saved networks ...\n");
    wifi_ap_record_t *records = NULL;
    uint16_t count = 0;
    if (scan_records(&records, &count) != 0)
        return 1;
    for (uint16_t i = 0; i < count; ++i)
    {
        char scanned_ssid[33];
        memcpy(scanned_ssid, records[i].ssid, sizeof(records[i].ssid));
        scanned_ssid[sizeof(scanned_ssid) - 1] = '\0';

        int idx = find_usable(scanned_ssid, user);
        if (idx >= 0)
        {
            printf("found: %s (%d dBm)\n", s_db.entries[idx].ssid, records[i].rssi);
            free(records);
            return connect_saved_idx_ex(idx, true);
        }
    }
    free(records);
    printf("No saved Wi-Fi network is currently visible.\n");
    return 1;
}

int tdsh_cmd_wifidisconnect(tdsh_session_t *session, int argc, char **argv)
{
    (void)session;
    (void)argc;
    (void)argv;
    if (!s_ready)
        return 0;
    s_auto_reconnect = false;
    s_retry = 0;
    esp_err_t err = esp_wifi_disconnect();
    if (err != ESP_OK && err != ESP_ERR_WIFI_NOT_CONNECT)
    {
        printf("Wi-Fi disconnect failed: %s\n", esp_err_to_name(err));
        return 1;
    }
    xEventGroupClearBits(s_events, WIFI_CONNECTED_BIT);
    printf("Wi-Fi disconnected.\n");
    return 0;
}


void *tdsh_wifi_netif(void)
{
    return s_sta_netif;
}

esp_err_t tdsh_wifi_stop(void)
{
    esp_err_t err = wifi_init_mutex_ensure();
    if (err != ESP_OK)
        return err;

    if (xSemaphoreTake(s_init_mutex, portMAX_DELAY) != pdTRUE)
    {
        return ESP_ERR_TIMEOUT;
    }

    if (!s_ready && !s_wifi_driver_inited && !s_sta_netif)
    {
        xSemaphoreGive(s_init_mutex);
        return ESP_OK;
    }

    s_auto_reconnect = false;
    s_retry = 0;

    if (s_wifi_started)
    {
        (void)esp_wifi_disconnect();
        err = esp_wifi_stop();
        if (err != ESP_OK && err != ESP_ERR_WIFI_NOT_STARTED)
            goto out;
        s_wifi_started = false;
    }

    if (s_wifi_event_registered)
    {
        (void)esp_event_handler_unregister(WIFI_EVENT, ESP_EVENT_ANY_ID,
                                           wifi_event);
        s_wifi_event_registered = false;
    }
    if (s_ip_event_registered)
    {
        (void)esp_event_handler_unregister(IP_EVENT, IP_EVENT_STA_GOT_IP,
                                           wifi_event);
        s_ip_event_registered = false;
    }

    if (s_wifi_driver_inited)
    {
        err = esp_wifi_deinit();
        if (err != ESP_OK)
            goto out;
        s_wifi_driver_inited = false;
    }

    if (s_sta_netif)
    {
        esp_netif_destroy_default_wifi(s_sta_netif);
        s_sta_netif = NULL;
    }
    if (s_ap_netif)
    {
        esp_netif_destroy_default_wifi(s_ap_netif);
        s_ap_netif = NULL;
    }
    s_ap_up = false;
    if (s_events)
    {
        vEventGroupDelete(s_events);
        s_events = NULL;
    }

    s_ready = false;
    err = ESP_OK;

out:
    xSemaphoreGive(s_init_mutex);
    return err;
}

esp_err_t tdsh_wifi_autoconnect(bool verbose)
{
    esp_err_t err = tdsh_wifi_init();
    if (err != ESP_OK)
        return err;
    err = wifi_db_load();
    if (err != ESP_OK)
        return err;
    if (s_db.count == 0)
        return ESP_ERR_NOT_FOUND;
    if (tdsh_wifi_is_connected())
        return ESP_OK;

    if (verbose)
        printf("Scanning for available saved networks ...\n");
    wifi_ap_record_t *records = NULL;
    uint16_t count = 0;
    if (scan_records(&records, &count) != 0)
        return ESP_FAIL;
    int best_idx = -1;
    int best_rssi = -128;
    for (uint16_t i = 0; i < count; ++i)
    {
        char scanned_ssid[33];
        memcpy(scanned_ssid, records[i].ssid, sizeof(records[i].ssid));
        scanned_ssid[sizeof(scanned_ssid) - 1] = '\0';
        int idx = find_usable(scanned_ssid, NULL);
        if (idx >= 0 && records[i].rssi > best_rssi)
        {
            best_idx = idx;
            best_rssi = records[i].rssi;
        }
    }
    free(records);
    if (best_idx < 0)
        return ESP_ERR_NOT_FOUND;
    if (verbose)
        printf("found: %s (%d dBm)\n", s_db.entries[best_idx].ssid, best_rssi);
    return connect_saved_idx_ex(best_idx, verbose) == 0 ? ESP_OK : ESP_FAIL;
}

int tdsh_wifi_get_info(tdsh_wifi_info_t *info)
{
    if (!info)
        return -EINVAL;
    memset(info, 0, sizeof(*info));
    info->initialized = s_ready;
    if (!s_ready)
        return 0;

    (void)esp_wifi_get_mac(WIFI_IF_STA, info->mac);
    info->connected = tdsh_wifi_is_connected();
    if (!info->connected)
        return 0;

    esp_netif_ip_info_t ip;
    if (s_sta_netif && esp_netif_get_ip_info(s_sta_netif, &ip) == ESP_OK)
    {
        info->ip.addr = ip.ip.addr;
        info->netmask.addr = ip.netmask.addr;
        info->gateway.addr = ip.gw.addr;
        esp_netif_dns_info_t dns;
        if (esp_netif_get_dns_info(s_sta_netif, ESP_NETIF_DNS_MAIN, &dns) == ESP_OK &&
            dns.ip.type == ESP_IPADDR_TYPE_V4)
        {
            info->dns.addr = dns.ip.u_addr.ip4.addr;
        }
    }

    wifi_ap_record_t ap;
    memset(&ap, 0, sizeof(ap));
    if (esp_wifi_sta_get_ap_info(&ap) == ESP_OK)
    {
        memcpy(info->ssid, ap.ssid, sizeof(ap.ssid));
        info->ssid[sizeof(info->ssid) - 1] = '\0';
        info->rssi = ap.rssi;
        info->channel = ap.primary;
    }
    return 0;
}

/* ------------------------------------------------------------------------
 * a structured Wi-Fi API for GUI front ends. It uses the same
 * saved-network database (with owners) and connect logic as the wifi*
 * commands, prints nothing on success and may block (call it from a worker
 * task). `user` is the acting user.
 * ---------------------------------------------------------------------- */

int tdsh_wifi_scan_list(tdsh_wifi_ap_t *out, int max, const char *user)
{
    wifi_ap_record_t *records = NULL;
    uint16_t count = 0;
    if (!out || max <= 0)
        return -1;
    if (scan_records(&records, &count) != 0)
        return -1;
    (void)wifi_db_load();
    int n = 0;
    for (uint16_t i = 0; i < count; ++i)
    {
        char ssid[33];
        memcpy(ssid, records[i].ssid, sizeof(records[i].ssid));
        ssid[sizeof(ssid) - 1] = '\0';
        if (!ssid[0])
            continue;                       /* hidden network */
        int dup = -1;
        for (int j = 0; j < n; ++j)
            if (strcmp(out[j].ssid, ssid) == 0)
                dup = j;
        if (dup >= 0)
        {                               /* keep the strongest */
            if (records[i].rssi > out[dup].rssi)
                out[dup].rssi = records[i].rssi;
            continue;
        }
        if (n >= max)
            continue;
        memcpy(out[n].ssid, ssid, sizeof(out[n].ssid));
        out[n].rssi = records[i].rssi;
        out[n].secure = records[i].authmode != WIFI_AUTH_OPEN;
        out[n].saved = find_usable(ssid, user) >= 0;
        n++;
    }
    free(records);
    return n;
}

int tdsh_wifi_save(const char *ssid, const char *password, const char *user)
{
    if (!ssid || !ssid[0] || strlen(ssid) > 32)
        return -1;
    if (password && strlen(password) > 63)
        return -1;
    if (wifi_db_load() != ESP_OK)
        return -1;
    return save_for_user(ssid, password, user) == 0 ? 0 : -1;
}

int tdsh_wifi_forget(const char *ssid, const char *user)
{
    if (wifi_db_load() != ESP_OK)
        return -1;
    int idx = find_managed(ssid, user);
    if (idx < 0)
        return find_usable(ssid, user) >= 0 ? -2 : -1;
    memset(&s_db.entries[idx], 0, sizeof(s_db.entries[idx]));
    if (s_db.count)
        s_db.count--;
    return wifi_db_save() == ESP_OK ? 0 : -1;
}

int tdsh_wifi_connect_saved(const char *ssid, const char *user)
{
    if (tdsh_wifi_init() != ESP_OK || wifi_db_load() != ESP_OK)
        return -1;
    int idx = find_usable(ssid, user);
    if (idx < 0)
        return -1;
    return connect_saved_idx_ex(idx, false) == 0 ? 0 : -1;
}

int tdsh_wifi_disconnect_now(void)
{
    if (!s_ready)
        return 0;
    s_auto_reconnect = false;
    s_retry = 0;
    esp_err_t err = esp_wifi_disconnect();
    xEventGroupClearBits(s_events, WIFI_CONNECTED_BIT);
    return (err == ESP_OK || err == ESP_ERR_WIFI_NOT_CONNECT) ? 0 : -1;
}

/* ------------------------------------------------------------------------
 * The access point (STA+AP): the board's own Wi-Fi network, for Telnet,
 * SSH and the web terminal when no other network is there. Its settings
 * (mode, name, password) are kept in NVS (WIFI_NS, "ap"); the network task
 * applies the mode every second (tdsh_wifi_ap_policy). It shares the
 * station's channel, so it moves when the station joins a network.
 * ---------------------------------------------------------------------- */

#define AP_KEY         "ap"
#define AP_IDLE_MS     60000   /* auto: back off this long after a network and no clients */
#define AP_OFFLINE_MS  20000   /* auto: up after this long without a network */
#define AP_MAX_CLIENTS 4

typedef struct
{
    uint8_t mode;   /* tdsh_wifi_ap_mode_t */
    char ssid[33];
    char password[65];
} ap_conf_t;

static ap_conf_t s_ap;
static bool s_ap_loaded;
static int64_t s_offline_since, s_idle_since;

static void ap_defaults(void)
{
    uint8_t mac[6] = {0};
    esp_read_mac(mac, ESP_MAC_WIFI_SOFTAP);
    snprintf(s_ap.ssid, sizeof(s_ap.ssid), "TinyDesk-%02X%02X", mac[4], mac[5]);
    /* A password of its own for every board (no shared default), shown by
     * `wifiap` and the Network app to those with the Network right. */
    static const char letters[] = "abcdefghjkmnpqrstuvwxyz23456789";
    for (int i = 0; i < 10; i++)
        s_ap.password[i] = letters[esp_random() % (sizeof(letters) - 1)];
    s_ap.password[10] = '\0';
    s_ap.mode = TDSH_WIFI_AP_OFF;
}

static void ap_load(void)
{
    if (s_ap_loaded)
        return;
    s_ap_loaded = true;
    nvs_handle_t h;
    size_t n = sizeof(s_ap);
    bool ok = false;
    if (nvs_open(WIFI_NS, NVS_READONLY, &h) == ESP_OK)
    {
        ok = nvs_get_blob(h, AP_KEY, &s_ap, &n) == ESP_OK && n == sizeof(s_ap) && s_ap.ssid[0];
        nvs_close(h);
    }
    if (!ok)
    {
        ap_defaults();
        nvs_handle_t w;
        if (nvs_open(WIFI_NS, NVS_READWRITE, &w) == ESP_OK)
        {
            nvs_set_blob(w, AP_KEY, &s_ap, sizeof(s_ap));
            nvs_commit(w);
            nvs_close(w);
        }
    }
    s_ap.ssid[sizeof(s_ap.ssid) - 1] = '\0';
    s_ap.password[sizeof(s_ap.password) - 1] = '\0';
}

static esp_err_t ap_start(void)
{
    esp_err_t err = tdsh_wifi_init();
    if (err != ESP_OK)
        return err;
    if (!s_ap_netif)
    {
        s_ap_netif = esp_netif_create_default_wifi_ap();
        if (!s_ap_netif)
            return ESP_FAIL;
    }
    wifi_config_t cfg = {0};
    memcpy(cfg.ap.ssid, s_ap.ssid, strlen(s_ap.ssid));
    cfg.ap.ssid_len = (uint8_t)strlen(s_ap.ssid);
    memcpy(cfg.ap.password, s_ap.password, strlen(s_ap.password));
    cfg.ap.authmode = WIFI_AUTH_WPA2_PSK;
    cfg.ap.max_connection = AP_MAX_CLIENTS;
    cfg.ap.pmf_cfg.capable = true;
    err = esp_wifi_set_mode(WIFI_MODE_APSTA);
    if (err == ESP_OK)
        err = esp_wifi_set_config(WIFI_IF_AP, &cfg);
    if (err == ESP_OK)
    {
        s_ap_up = true;
        s_idle_since = 0;
        ESP_LOGI(TAG, "access point %s is up (192.168.4.1)", s_ap.ssid);
    }
    return err;
}

static void ap_stop(void)
{
    if (!s_ap_up)
        return;
    s_ap_up = false;
    if (s_wifi_started)
        esp_wifi_set_mode(WIFI_MODE_STA);
    ESP_LOGI(TAG, "access point %s is down", s_ap.ssid);
}

bool tdsh_wifi_ap_is_up(void)
{
    return s_ap_up;
}

static int ap_clients(void)
{
    wifi_sta_list_t list;
    if (!s_ap_up || esp_wifi_ap_get_sta_list(&list) != ESP_OK)
        return 0;
    return list.num;
}

void tdsh_wifi_ap_policy(bool online, bool wifi_allowed)
{
    ap_load();
    int64_t now = esp_timer_get_time() / 1000;
    if (!wifi_allowed || !s_wifi_started)
    {
        /* LAN only, or Wi-Fi stopped (tdsh_wifi_stop): no access point. */
        if (!wifi_allowed && s_ap_up)
            ap_stop();
        if (!wifi_allowed || s_ap.mode == TDSH_WIFI_AP_OFF)
            return;
    }
    bool want = s_ap_up;
    switch (s_ap.mode)
    {
    case TDSH_WIFI_AP_ON:
        want = true;
        break;
    case TDSH_WIFI_AP_AUTO:
        if (online)
        {
            s_offline_since = 0;
            if (s_ap_up && ap_clients() == 0)
            {
                if (!s_idle_since)
                    s_idle_since = now;
                if (now - s_idle_since >= AP_IDLE_MS)
                    want = false;
            }
            else
                s_idle_since = 0;
        }
        else
        {
            if (!s_offline_since)
                s_offline_since = now;
            if (now - s_offline_since >= AP_OFFLINE_MS)
                want = true;
        }
        break;
    default:
        want = false;
        break;
    }
    if (want && !s_ap_up)
    {
        esp_err_t err = ap_start();
        if (err != ESP_OK)
            ESP_LOGW(TAG, "access point: %s", esp_err_to_name(err));
    }
    else if (!want && s_ap_up)
        ap_stop();
}

int tdsh_wifi_ap_get_config(tdsh_wifi_ap_config_t *out)
{
    if (!out)
        return -EINVAL;
    ap_load();
    memset(out, 0, sizeof(*out));
    out->mode = (tdsh_wifi_ap_mode_t)s_ap.mode;
    snprintf(out->ssid, sizeof(out->ssid), "%s", s_ap.ssid);
    snprintf(out->password, sizeof(out->password), "%s", s_ap.password);
    return 0;
}

int tdsh_wifi_ap_set_config(const tdsh_wifi_ap_config_t *conf)
{
    if (!conf || conf->mode > TDSH_WIFI_AP_AUTO)
        return -EINVAL;
    size_t sl = strlen(conf->ssid), pl = strlen(conf->password);
    if (sl < 1 || sl > 32 || pl < 8 || pl > 63)
        return -EINVAL;   /* WPA2: 8 to 63 characters */
    ap_load();
    bool changed = strcmp(s_ap.ssid, conf->ssid) || strcmp(s_ap.password, conf->password);
    s_ap.mode = (uint8_t)conf->mode;
    snprintf(s_ap.ssid, sizeof(s_ap.ssid), "%s", conf->ssid);
    snprintf(s_ap.password, sizeof(s_ap.password), "%s", conf->password);
    nvs_handle_t h;
    if (nvs_open(WIFI_NS, NVS_READWRITE, &h) != ESP_OK)
        return -EIO;
    esp_err_t err = nvs_set_blob(h, AP_KEY, &s_ap, sizeof(s_ap));
    if (err == ESP_OK)
        err = nvs_commit(h);
    nvs_close(h);
    if (changed && s_ap_up)
        ap_start();   /* the new name and password at once */
    s_offline_since = s_idle_since = 0;
    tdsh_network_kick();
    return err == ESP_OK ? 0 : -EIO;
}

int tdsh_wifi_ap_get_info(tdsh_wifi_ap_info_t *info)
{
    if (!info)
        return -EINVAL;
    ap_load();
    memset(info, 0, sizeof(*info));
    info->up = s_ap_up;
    snprintf(info->ssid, sizeof(info->ssid), "%s", s_ap.ssid);
    if (!s_ap_up)
        return 0;
    info->clients = ap_clients();
    esp_netif_ip_info_t ip;
    if (s_ap_netif && esp_netif_get_ip_info(s_ap_netif, &ip) == ESP_OK)
        info->ip.addr = ip.ip.addr;
    uint8_t primary = 0;
    wifi_second_chan_t second;
    if (esp_wifi_get_channel(&primary, &second) == ESP_OK)
        info->channel = primary;
    return 0;
}

static const char *ap_mode_name(int mode)
{
    return mode == TDSH_WIFI_AP_ON ? "on" : mode == TDSH_WIFI_AP_AUTO ? "auto"
                                                                      : "off";
}

int tdsh_cmd_wifiap(tdsh_session_t *session, int argc, char **argv)
{
    (void)session;
    tdsh_wifi_ap_config_t conf;
    tdsh_wifi_ap_get_config(&conf);
    if (argc == 1 || (argc == 2 && !strcmp(argv[1], "status")))
    {
        tdsh_wifi_ap_info_t info;
        tdsh_wifi_ap_get_info(&info);
        printf("Access point: %s (%s)\n", info.up ? "up" : "down", ap_mode_name(conf.mode));
        printf("  name:      %s\n", conf.ssid);
        printf("  password:  %s\n", conf.password);
        if (info.up)
        {
            uint8_t *a = (uint8_t *)&info.ip.addr;
            printf("  address:   %u.%u.%u.%u, channel %d, %d client%s\n", a[0], a[1], a[2], a[3], info.channel,
                   info.clients, info.clients == 1 ? "" : "s");
        }
        if (conf.mode == TDSH_WIFI_AP_AUTO)
            printf("  auto: up after %d s without a network, down %d s after one is back with no clients\n",
                   AP_OFFLINE_MS / 1000, AP_IDLE_MS / 1000);
        return 0;
    }
    if (argc == 2 && (!strcmp(argv[1], "on") || !strcmp(argv[1], "off") || !strcmp(argv[1], "auto")))
        conf.mode = !strcmp(argv[1], "on") ? TDSH_WIFI_AP_ON : !strcmp(argv[1], "auto") ? TDSH_WIFI_AP_AUTO
                                                                                        : TDSH_WIFI_AP_OFF;
    else if (argc == 3 && !strcmp(argv[1], "name"))
        snprintf(conf.ssid, sizeof(conf.ssid), "%s", argv[2]);
    else if (argc == 3 && !strcmp(argv[1], "password"))
        snprintf(conf.password, sizeof(conf.password), "%s", argv[2]);
    else
    {
        printf("usage:\n"
               "  wifiap [status]          the access point's state, name and password\n"
               "  wifiap on|off|auto       always, never, or when there is no network\n"
               "  wifiap name <ssid>       its network name (1 to 32 characters)\n"
               "  wifiap password <pw>     its WPA2 password (8 to 63 characters)\n"
               "Clients get 192.168.4.x; the board is 192.168.4.1 (Telnet, SSH).\n");
        return 2;
    }
    int rc = tdsh_wifi_ap_set_config(&conf);
    if (rc == -EINVAL)
    {
        printf("wifiap: the name must be 1 to 32 characters, the password 8 to 63\n");
        return 1;
    }
    if (rc)
    {
        printf("wifiap: could not save the settings\n");
        return 1;
    }
    printf("Access point %s: %s (it applies within a second)\n", ap_mode_name(conf.mode), conf.ssid);
    return 0;
}

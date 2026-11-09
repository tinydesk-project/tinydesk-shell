#include "tdsh_espidf_internal.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "esp_log.h"
#include "esp_netif.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "lwip/ip4_addr.h"
#include "nvs.h"

#define NET_NS            "ush_net"
#define NET_KEY_MODE      "mode"
#define NET_KEY_WIFI_AUTO "wifi_auto"
#define NET_TASK_STACK    6144
#define NET_TASK_PRIORITY 3
#define WIFI_RETRY_MS     15000

static const char *TAG = "tdsh-net";
static tdsh_network_mode_t s_mode = TDSH_NETWORK_MODE_AUTO;
static bool s_wifi_autoconnect = false;
static TaskHandle_t s_task;
static bool s_initialized;
static volatile bool s_policy_kick;

static const char *mode_name(tdsh_network_mode_t mode)
{
    switch (mode)
    {
    case TDSH_NETWORK_MODE_AUTO:
        return "auto";
    case TDSH_NETWORK_MODE_LAN:
        return "lan";
    case TDSH_NETWORK_MODE_WIFI:
        return "wifi";
    case TDSH_NETWORK_MODE_BOTH:
        return "both";
    default:
        return "unknown";
    }
}

static bool mode_from_text(const char *text, tdsh_network_mode_t *mode)
{
    if (!text || !mode)
        return false;
    if (strcmp(text, "auto") == 0)
        *mode = TDSH_NETWORK_MODE_AUTO;
    else if (strcmp(text, "lan") == 0)
        *mode = TDSH_NETWORK_MODE_LAN;
    else if (strcmp(text, "wifi") == 0)
        *mode = TDSH_NETWORK_MODE_WIFI;
    else if (strcmp(text, "both") == 0)
        *mode = TDSH_NETWORK_MODE_BOTH;
    else
        return false;
    return true;
}

static esp_err_t mode_load(void)
{
    nvs_handle_t h;
    esp_err_t err = nvs_open(NET_NS, NVS_READWRITE, &h);
    if (err != ESP_OK)
        return err;

    uint8_t value = TDSH_NETWORK_MODE_AUTO;
    err = nvs_get_u8(h, NET_KEY_MODE, &value);
    if (err == ESP_ERR_NVS_NOT_FOUND || value > TDSH_NETWORK_MODE_BOTH)
    {
        value = TDSH_NETWORK_MODE_AUTO;
        err = nvs_set_u8(h, NET_KEY_MODE, value);
        if (err != ESP_OK)
        {
            nvs_close(h);
            return err;
        }
    }
    else if (err != ESP_OK)
    {
        nvs_close(h);
        return err;
    }

    /*
     * Wi-Fi auto-connect is intentionally independent of the network mode.
     *
     * Default OFF:
     *   - Removing `wificonnect` from ~/.tdshrc.tdsh really means Wi-Fi will not
     *     connect automatically on boot.
     *   - `wifiscan`, `wificonnect`, and `wifidisconnect` remain manual and
     *     predictable even while Ethernet is online.
     *
     * Users who want automatic Wi-Fi fallback can explicitly enable it with:
     *     network autowifi on
     */
    uint8_t wifi_auto = 0;
    esp_err_t wifi_err = nvs_get_u8(h, NET_KEY_WIFI_AUTO, &wifi_auto);
    if (wifi_err == ESP_ERR_NVS_NOT_FOUND)
    {
        wifi_auto = 0;
        wifi_err = nvs_set_u8(h, NET_KEY_WIFI_AUTO, wifi_auto);
    }
    if (wifi_err != ESP_OK)
    {
        nvs_close(h);
        return wifi_err;
    }

    err = nvs_commit(h);
    nvs_close(h);
    if (err != ESP_OK)
        return err;

    s_mode = (tdsh_network_mode_t)value;
    s_wifi_autoconnect = wifi_auto != 0;
    return ESP_OK;
}

static esp_err_t mode_save(void)
{
    nvs_handle_t h;
    esp_err_t err = nvs_open(NET_NS, NVS_READWRITE, &h);
    if (err != ESP_OK)
        return err;
    err = nvs_set_u8(h, NET_KEY_MODE, (uint8_t)s_mode);
    if (err == ESP_OK)
        err = nvs_commit(h);
    nvs_close(h);
    return err;
}

static esp_err_t wifi_autoconnect_save(void)
{
    nvs_handle_t h;
    esp_err_t err = nvs_open(NET_NS, NVS_READWRITE, &h);
    if (err != ESP_OK)
        return err;

    err = nvs_set_u8(h, NET_KEY_WIFI_AUTO,
                     s_wifi_autoconnect ? 1U : 0U);
    if (err == ESP_OK)
        err = nvs_commit(h);
    nvs_close(h);
    return err;
}

tdsh_network_mode_t tdsh_network_get_mode(void)
{
    return s_mode;
}

bool tdsh_network_is_online(void)
{
    return tdsh_eth_is_connected() || tdsh_wifi_is_connected();
}

bool tdsh_network_is_reachable(void)
{
    return tdsh_network_is_online() || tdsh_wifi_ap_is_up();
}

static void select_default_route(void)
{
    esp_netif_t *eth = (esp_netif_t *)tdsh_eth_netif();
    esp_netif_t *wifi = (esp_netif_t *)tdsh_wifi_netif();
    bool eth_up = tdsh_eth_is_connected();
    bool wifi_up = tdsh_wifi_is_connected();

    if (s_mode != TDSH_NETWORK_MODE_WIFI && eth_up && eth)
    {
        (void)esp_netif_set_default_netif(eth);
    }
    else if (wifi_up && wifi)
    {
        (void)esp_netif_set_default_netif(wifi);
    }
    else if (eth_up && eth)
    {
        (void)esp_netif_set_default_netif(eth);
    }
}

static void network_task(void *arg)
{
    (void)arg;

    TickType_t last_wifi_attempt = 0;
    bool was_online = false;

    for (;;)
    {
        tdsh_eth_info_t eth_info;
        (void)tdsh_eth_get_info(&eth_info);

        /*
         * Interface policy
         * ----------------
         * AUTO:
         *   Ethernet is started automatically and preferred as the default
         *   route.  A Wi-Fi interface that was manually connected is left
         *   running side-by-side.  If "network autowifi on" is enabled,
         *   Wi-Fi is automatically connected only while Ethernet is offline.
         *
         * BOTH:
         *   Ethernet is started automatically. Wi-Fi is never stopped because
         *   Ethernet is online. Optional auto-Wi-Fi may keep both connected.
         *
         * LAN:
         *   Ethernet only; Wi-Fi is intentionally stopped.
         *
         * WIFI:
         *   Wi-Fi only; Ethernet is intentionally stopped.
         */

        if (s_mode == TDSH_NETWORK_MODE_LAN ||
            s_mode == TDSH_NETWORK_MODE_BOTH ||
            s_mode == TDSH_NETWORK_MODE_AUTO)
        {
            if (eth_info.enabled)
            {
                esp_err_t err = tdsh_eth_start();
                if (err != ESP_OK &&
                    err != ESP_ERR_INVALID_STATE &&
                    err != ESP_ERR_INVALID_ARG &&
                    err != ESP_ERR_NOT_SUPPORTED)
                {   /* the board has no Ethernet (eth.chip) */
                    ESP_LOGW(TAG, "Ethernet start: %s",
                             esp_err_to_name(err));
                }
            }
        }

        bool eth_connected = tdsh_eth_is_connected();
        bool allow_wifi = false;
        bool policy_should_autoconnect_wifi = false;

        switch (s_mode)
        {
        case TDSH_NETWORK_MODE_WIFI:
            (void)tdsh_eth_stop();
            allow_wifi = true;
            policy_should_autoconnect_wifi = s_wifi_autoconnect;
            break;

        case TDSH_NETWORK_MODE_LAN:
                /*
                 * LAN mode is the only mode that deliberately tears Wi-Fi
                 * down. Use AUTO or BOTH when both interfaces should coexist.
                 */
            if (tdsh_wifi_netif())
            {
                (void)tdsh_wifi_stop();
            }
            allow_wifi = false;
            break;

        case TDSH_NETWORK_MODE_BOTH:
                /*
                 * Never stop Wi-Fi here. Manual scans/connections/disconnects
                 * must remain usable while Ethernet is connected.
                 */
            allow_wifi = true;
            policy_should_autoconnect_wifi = s_wifi_autoconnect;
            break;

        case TDSH_NETWORK_MODE_AUTO:
        default:
                /*
                 * Ethernet remains preferred, but do NOT stop an already
                 * running Wi-Fi interface. This is the key change from the
                 * old policy.
                 *
                 * Optional automatic Wi-Fi is only a fallback while Ethernet
                 * is not online. A manually connected Wi-Fi can continue to
                 * coexist after Ethernet comes up.
                 */
            allow_wifi = true;
            policy_should_autoconnect_wifi =
                s_wifi_autoconnect && !eth_connected;
            break;
        }

        if (allow_wifi &&
            policy_should_autoconnect_wifi &&
            !tdsh_wifi_is_connected())
        {
            TickType_t now = xTaskGetTickCount();
            if (!tdsh_wifi_netif() ||
                s_policy_kick ||
                (now - last_wifi_attempt) >= pdMS_TO_TICKS(WIFI_RETRY_MS))
            {
                last_wifi_attempt = now;
                esp_err_t err = tdsh_wifi_autoconnect(false);
                if (err != ESP_OK && err != ESP_ERR_NOT_FOUND)
                {
                    ESP_LOGD(TAG, "Wi-Fi auto-connect: %s",
                             esp_err_to_name(err));
                }
            }
        }

        /*
         * Route selection affects only the default outbound route. It does
         * not stop or destroy the other interface.
         */
        select_default_route();

        bool online = tdsh_network_is_online();
        tdsh_wifi_ap_policy(online, allow_wifi);   /* the access point (wifiap) */
        if (online && !was_online)
        {
            tdsh_time_sync_start();
        }
        was_online = online;

        s_policy_kick = false;
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void tdsh_network_kick(void)
{
    s_policy_kick = true;
}

esp_err_t tdsh_network_init(void)
{
    if (s_initialized)
        return ESP_OK;
    esp_err_t err = mode_load();
    if (err != ESP_OK)
        return err;

    err = tdsh_netmount_init();
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "network-drive VFS init failed: %s", esp_err_to_name(err));
        return err;
    }

    BaseType_t ok = xTaskCreate(network_task, "tdsh_net", NET_TASK_STACK,
                                NULL, NET_TASK_PRIORITY, &s_task);
    if (ok != pdPASS)
        return ESP_ERR_NO_MEM;
    s_initialized = true;
    ESP_LOGI(TAG, "network mode=%s, Wi-Fi auto-connect=%s (Ethernet preferred in auto/both)",
             mode_name(s_mode), s_wifi_autoconnect ? "on" : "off");
    return ESP_OK;
}

static void print_ip_value(uint32_t addr)
{
    ip4_addr_t ip = {.addr = addr};
    printf("%s", addr ? ip4addr_ntoa(&ip) : "0.0.0.0");
}

static void print_eth(bool is_default)
{
    tdsh_eth_info_t i;
    (void)tdsh_eth_get_info(&i);
    printf("eth0:\n");
    printf("  status:    %s%s\n",
           i.connected ? "connected" : (i.link_up ? "link-up/no-ip" : "disconnected"),
           is_default ? " [default]" : "");
    printf("  enabled:   %s\n", i.enabled ? "yes" : "no");
    printf("  driver:    %s\n", i.initialized ? "initialized" : "not initialized");
    printf("  link:      %s\n", i.link_up ? "up" : "down");
    printf("  mode:      %s\n", i.dhcp ? "DHCP" : "static");
    if (i.initialized)
    {
        printf("  mac:       %02X:%02X:%02X:%02X:%02X:%02X\n",
               i.mac[0], i.mac[1], i.mac[2], i.mac[3], i.mac[4], i.mac[5]);
        if (i.link_up)
        {
            printf("  speed:     %d Mbps\n", i.speed_mbps);
            printf("  duplex:    %s\n", i.full_duplex ? "full" : "half");
        }
    }
    if (i.connected)
    {
        printf("  ip:        ");
        print_ip_value(i.ip.addr);
        printf("\n");
        printf("  netmask:   ");
        print_ip_value(i.netmask.addr);
        printf("\n");
        printf("  gateway:   ");
        print_ip_value(i.gateway.addr);
        printf("\n");
        printf("  dns:       ");
        print_ip_value(i.dns.addr);
        printf("\n");
    }
}

static void print_wifi(bool is_default)
{
    tdsh_wifi_info_t i;
    (void)tdsh_wifi_get_info(&i);
    printf("wlan0:\n");
    printf("  status:    %s%s\n",
           i.connected ? "connected" : (i.initialized ? "disconnected" : "stopped"),
           is_default ? " [default]" : "");
    if (!i.initialized)
        return;
    printf("  mac:       %02X:%02X:%02X:%02X:%02X:%02X\n",
           i.mac[0], i.mac[1], i.mac[2], i.mac[3], i.mac[4], i.mac[5]);
    if (i.connected)
    {
        printf("  ssid:      %s\n", i.ssid);
        printf("  rssi:      %d dBm\n", i.rssi);
        printf("  channel:   %u\n", i.channel);
        printf("  ip:        ");
        print_ip_value(i.ip.addr);
        printf("\n");
        printf("  netmask:   ");
        print_ip_value(i.netmask.addr);
        printf("\n");
        printf("  gateway:   ");
        print_ip_value(i.gateway.addr);
        printf("\n");
        printf("  dns:       ");
        print_ip_value(i.dns.addr);
        printf("\n");
    }
}

int tdsh_cmd_ifconfig(tdsh_session_t *session, int argc, char **argv)
{
    (void)session;
    if (argc != 1)
    {
        printf("usage: ifconfig\n");
        return 2;
    }
    esp_netif_t *def = esp_netif_get_default_netif();
    print_eth(def && def == (esp_netif_t *)tdsh_eth_netif());
    printf("\n");
    print_wifi(def && def == (esp_netif_t *)tdsh_wifi_netif());
    printf("\nnetwork mode: %s\n", mode_name(s_mode));
    return 0;
}

int tdsh_cmd_network(tdsh_session_t *session, int argc, char **argv)
{
    /* Device-wide settings require the delegated network permission. */
    if (argc == 3 && (strcmp(argv[1], "mode") == 0 || strcmp(argv[1], "autowifi") == 0) &&
        !tdsh_session_has_right(session, TDSH_RIGHT_NETWORK))
    {
        printf("network: permission denied: network permission required\n");
        return 1;
    }

    if (argc == 1 ||
        (argc == 2 && strcmp(argv[1], "status") == 0))
    {
        esp_netif_t *def = esp_netif_get_default_netif();
        const char *def_name = "none";

        if (def && def == (esp_netif_t *)tdsh_eth_netif())
        {
            def_name = "eth0";
        }
        else if (def && def == (esp_netif_t *)tdsh_wifi_netif())
        {
            def_name = "wlan0";
        }

        printf("Mode:             %s\n", mode_name(s_mode));
        printf("Online:           %s\n",
               tdsh_network_is_online() ? "yes" : "no");
        printf("Default:          %s\n", def_name);
        printf("Wi-Fi autoconnect:%s\n",
               s_wifi_autoconnect ? " on" : " off");

        if (s_mode == TDSH_NETWORK_MODE_AUTO)
        {
            printf("Policy:           LAN preferred; Wi-Fi may coexist. "
                   "Auto-Wi-Fi is fallback only.\n");
        }
        else if (s_mode == TDSH_NETWORK_MODE_BOTH)
        {
            printf("Policy:           LAN + Wi-Fi may coexist; LAN preferred.\n");
        }
        else if (s_mode == TDSH_NETWORK_MODE_LAN)
        {
            printf("Policy:           LAN only.\n");
        }
        else
        {
            printf("Policy:           Wi-Fi only.\n");
        }
        return 0;
    }

    if (argc == 2 && strcmp(argv[1], "mode") == 0)
    {
        printf("%s\n", mode_name(s_mode));
        return 0;
    }

    if (argc == 3 && strcmp(argv[1], "mode") == 0)
    {
        tdsh_network_mode_t mode;
        if (!mode_from_text(argv[2], &mode))
        {
            printf("usage: network mode <auto|lan|wifi|both>\n");
            return 2;
        }

        s_mode = mode;
        if (mode_save() != ESP_OK)
        {
            printf("Failed to save network mode.\n");
            return 1;
        }

        s_policy_kick = true;
        printf("Network mode set to %s.\n", mode_name(s_mode));

        if (mode == TDSH_NETWORK_MODE_BOTH ||
            mode == TDSH_NETWORK_MODE_AUTO)
        {
            printf("LAN and Wi-Fi can now remain active side-by-side.\n");
        }
        return 0;
    }

    if (argc == 2 && strcmp(argv[1], "autowifi") == 0)
    {
        printf("%s\n", s_wifi_autoconnect ? "on" : "off");
        return 0;
    }

    if (argc == 3 && strcmp(argv[1], "autowifi") == 0)
    {
        if (strcmp(argv[2], "on") == 0)
        {
            s_wifi_autoconnect = true;
        }
        else if (strcmp(argv[2], "off") == 0)
        {
            s_wifi_autoconnect = false;
        }
        else
        {
            printf("usage: network autowifi <on|off>\n");
            return 2;
        }

        if (wifi_autoconnect_save() != ESP_OK)
        {
            printf("Failed to save Wi-Fi auto-connect setting.\n");
            return 1;
        }

        s_policy_kick = true;
        printf("Wi-Fi auto-connect set to %s.\n",
               s_wifi_autoconnect ? "on" : "off");

        if (!s_wifi_autoconnect)
        {
            printf("Existing Wi-Fi connection is unchanged; "
                   "future automatic reconnects are suppressed.\n");
        }
        return 0;
    }

    printf("usage:\n");
    printf("  network [status]\n");
    printf("  network mode [auto|lan|wifi|both]\n");
    printf("  network autowifi [on|off]\n");
    return 2;
}

#include "tdsh_espidf_internal.h"
#include "tdsh_board.h"
#include "sdkconfig.h"

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "driver/spi_master.h"
#include "esp_eth.h"
#include "esp_eth_netif_glue.h"
#include "esp_eth_mac_w6100.h"
#include "esp_eth_phy_w6100.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_mac.h"
#include "esp_netif.h"
#include "lwip/inet.h"
#include "nvs.h"

#define LAN_NS          "ush_lan"
#define LAN_KEY         "cfg"
#define LAN_CFG_MAGIC   0x554C414Eu
#define LAN_CFG_VERSION 2u

#ifndef CONFIG_TDSH_W6100_SPI_HOST
#define CONFIG_TDSH_W6100_SPI_HOST 1
#endif
#ifndef CONFIG_TDSH_W6100_MISO_GPIO
#define CONFIG_TDSH_W6100_MISO_GPIO -1
#endif
#ifndef CONFIG_TDSH_W6100_MOSI_GPIO
#define CONFIG_TDSH_W6100_MOSI_GPIO -1
#endif
#ifndef CONFIG_TDSH_W6100_SCLK_GPIO
#define CONFIG_TDSH_W6100_SCLK_GPIO -1
#endif
#ifndef CONFIG_TDSH_W6100_CS_GPIO
#define CONFIG_TDSH_W6100_CS_GPIO -1
#endif
#ifndef CONFIG_TDSH_W6100_INT_GPIO
#define CONFIG_TDSH_W6100_INT_GPIO -1
#endif
#ifndef CONFIG_TDSH_W6100_RST_GPIO
#define CONFIG_TDSH_W6100_RST_GPIO -1
#endif
#ifndef CONFIG_TDSH_W6100_SPI_CLOCK_MHZ
#define CONFIG_TDSH_W6100_SPI_CLOCK_MHZ 10
#endif
#ifndef CONFIG_TDSH_W6100_POLL_MS
#define CONFIG_TDSH_W6100_POLL_MS 100
#endif

typedef struct
{
    uint32_t magic;
    uint16_t version;
    uint8_t enabled;
    uint8_t dhcp;
    int8_t spi_host;
    int8_t miso_gpio;
    int8_t mosi_gpio;
    int8_t sclk_gpio;
    int8_t cs_gpio;
    int8_t int_gpio;
    int8_t rst_gpio;
    uint8_t spi_clock_mhz;
    uint16_t poll_ms;
    char ip[16];
    char netmask[16];
    char gateway[16];
    char dns[16];
} lan_config_t;

static const char *TAG = "tdsh-eth";
static lan_config_t s_cfg;
static bool s_cfg_loaded;
static bool s_initialized;
static bool s_started;
static volatile bool s_link_up;
static volatile bool s_has_ip;
static esp_eth_handle_t s_eth_handle;
static esp_eth_netif_glue_handle_t s_glue;
static esp_netif_t *s_eth_netif;
static esp_eth_mac_t *s_mac;
static esp_eth_phy_t *s_phy;

static void cfg_apply_board(void);

static void cfg_defaults(void)
{
    memset(&s_cfg, 0, sizeof(s_cfg));
    s_cfg.magic = LAN_CFG_MAGIC;
    s_cfg.version = LAN_CFG_VERSION;
    s_cfg.enabled = 1;
    s_cfg.dhcp = 1;
    s_cfg.spi_host = CONFIG_TDSH_W6100_SPI_HOST;
    s_cfg.miso_gpio = CONFIG_TDSH_W6100_MISO_GPIO;
    s_cfg.mosi_gpio = CONFIG_TDSH_W6100_MOSI_GPIO;
    s_cfg.sclk_gpio = CONFIG_TDSH_W6100_SCLK_GPIO;
    s_cfg.cs_gpio = CONFIG_TDSH_W6100_CS_GPIO;
    s_cfg.int_gpio = CONFIG_TDSH_W6100_INT_GPIO;
    s_cfg.rst_gpio = CONFIG_TDSH_W6100_RST_GPIO;
    s_cfg.spi_clock_mhz = CONFIG_TDSH_W6100_SPI_CLOCK_MHZ;
    s_cfg.poll_ms = CONFIG_TDSH_W6100_POLL_MS;
    snprintf(s_cfg.ip, sizeof(s_cfg.ip), "192.168.1.50");
    snprintf(s_cfg.netmask, sizeof(s_cfg.netmask), "255.255.255.0");
    snprintf(s_cfg.gateway, sizeof(s_cfg.gateway), "192.168.1.1");
    snprintf(s_cfg.dns, sizeof(s_cfg.dns), "8.8.8.8");
}

static esp_err_t cfg_save(void)
{
    nvs_handle_t h;
    esp_err_t err = nvs_open(LAN_NS, NVS_READWRITE, &h);
    if (err != ESP_OK)
        return err;
    err = nvs_set_blob(h, LAN_KEY, &s_cfg, sizeof(s_cfg));
    if (err == ESP_OK)
        err = nvs_commit(h);
    nvs_close(h);
    return err;
}

static esp_err_t cfg_load(void)
{
    if (s_cfg_loaded)
        return ESP_OK;
    cfg_defaults();
    nvs_handle_t h;
    esp_err_t err = nvs_open(LAN_NS, NVS_READWRITE, &h);
    if (err != ESP_OK)
        return err;
    size_t len = sizeof(s_cfg);
    lan_config_t tmp;
    err = nvs_get_blob(h, LAN_KEY, &tmp, &len);
    nvs_close(h);
    if (err == ESP_OK && len == sizeof(tmp) && tmp.magic == LAN_CFG_MAGIC &&
        tmp.version == LAN_CFG_VERSION)
    {
        s_cfg = tmp;
    }
    else if (err == ESP_ERR_NVS_NOT_FOUND || err == ESP_OK)
    {
        err = cfg_save();
    }
    cfg_apply_board();
    s_cfg_loaded = (err == ESP_OK);
    return err;
}

/* the W6100's wiring comes from the board configuration
 * (keys eth.*; the Kconfig values are only fallbacks), not from the copy
 * saved in NVS: the board file is the one place to change pins. */
static void cfg_apply_board(void)
{
    s_cfg.spi_host = (int8_t)tdsh_board_int("eth.spi_host", CONFIG_TDSH_W6100_SPI_HOST);
    s_cfg.miso_gpio = (int8_t)tdsh_board_int("eth.miso", CONFIG_TDSH_W6100_MISO_GPIO);
    s_cfg.mosi_gpio = (int8_t)tdsh_board_int("eth.mosi", CONFIG_TDSH_W6100_MOSI_GPIO);
    s_cfg.sclk_gpio = (int8_t)tdsh_board_int("eth.sclk", CONFIG_TDSH_W6100_SCLK_GPIO);
    s_cfg.cs_gpio = (int8_t)tdsh_board_int("eth.cs", CONFIG_TDSH_W6100_CS_GPIO);
    s_cfg.int_gpio = (int8_t)tdsh_board_int("eth.int", CONFIG_TDSH_W6100_INT_GPIO);
    s_cfg.rst_gpio = (int8_t)tdsh_board_int("eth.rst", CONFIG_TDSH_W6100_RST_GPIO);
    s_cfg.spi_clock_mhz = (uint8_t)tdsh_board_int("eth.spi_mhz", CONFIG_TDSH_W6100_SPI_CLOCK_MHZ);
    s_cfg.poll_ms = (uint16_t)tdsh_board_int("eth.poll_ms", CONFIG_TDSH_W6100_POLL_MS);
}

/* The board has a W6100 (eth.chip = w6100). */
static bool board_has_eth(void)
{
    const char *chip = tdsh_board_get("eth.chip");
    return chip && strcmp(chip, "w6100") == 0;
}

static bool hw_valid(void)
{
    return s_cfg.spi_host >= 0 && s_cfg.miso_gpio >= 0 && s_cfg.mosi_gpio >= 0 &&
           s_cfg.sclk_gpio >= 0 && s_cfg.cs_gpio >= 0 && s_cfg.spi_clock_mhz > 0;
}

static bool parse_ipv4(const char *text, esp_ip4_addr_t *out)
{
    if (!text || !out)
        return false;
    ip4_addr_t ip;
    if (!ip4addr_aton(text, &ip))
        return false;
    out->addr = ip.addr;
    return true;
}

static bool mac_is_zero(const uint8_t mac[6])
{
    if (!mac)
        return true;
    return mac[0] == 0 && mac[1] == 0 && mac[2] == 0 &&
           mac[3] == 0 && mac[4] == 0 && mac[5] == 0;
}

static esp_err_t configure_eth_mac(void)
{
    if (!s_eth_handle)
        return ESP_ERR_INVALID_STATE;

    uint8_t mac[6] = {0};

    /*
     * W6100 does not provide a unique factory MAC for the ESP-IDF driver.
     * Derive the Ethernet MAC from the ESP32-C6 base eFuse MAC, then write
     * it into the Ethernet MAC driver before esp_eth_start().
     */
    esp_err_t err = esp_read_mac(mac, ESP_MAC_ETH);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "esp_read_mac(ESP_MAC_ETH) failed: %s",
                 esp_err_to_name(err));
        return err;
    }

    if (mac_is_zero(mac) || (mac[0] & 0x01))
    {
        ESP_LOGE(TAG,
                 "invalid Ethernet MAC %02X:%02X:%02X:%02X:%02X:%02X",
                 mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
        return ESP_ERR_INVALID_MAC;
    }

    err = esp_eth_ioctl(s_eth_handle, ETH_CMD_S_MAC_ADDR, mac);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "ETH_CMD_S_MAC_ADDR failed: %s",
                 esp_err_to_name(err));
        return err;
    }

    uint8_t verify[6] = {0};
    err = esp_eth_ioctl(s_eth_handle, ETH_CMD_G_MAC_ADDR, verify);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "ETH_CMD_G_MAC_ADDR failed: %s",
                 esp_err_to_name(err));
        return err;
    }

    if (mac_is_zero(verify))
    {
        ESP_LOGE(TAG, "W6100 MAC remained 00:00:00:00:00:00 after assignment");
        return ESP_FAIL;
    }

    ESP_LOGI(TAG, "W6100 MAC %02X:%02X:%02X:%02X:%02X:%02X",
             verify[0], verify[1], verify[2],
             verify[3], verify[4], verify[5]);

    return ESP_OK;
}

static esp_err_t apply_ip_config(void)
{
    if (!s_eth_netif)
        return ESP_ERR_INVALID_STATE;
    if (s_cfg.dhcp)
    {
        esp_err_t err = esp_netif_dhcpc_start(s_eth_netif);
        if (err == ESP_ERR_ESP_NETIF_DHCP_ALREADY_STARTED)
            return ESP_OK;
        return err;
    }

    esp_err_t err = esp_netif_dhcpc_stop(s_eth_netif);
    if (err != ESP_OK && err != ESP_ERR_ESP_NETIF_DHCP_ALREADY_STOPPED)
        return err;

    esp_netif_ip_info_t ip_info = {0};
    if (!parse_ipv4(s_cfg.ip, &ip_info.ip) ||
        !parse_ipv4(s_cfg.netmask, &ip_info.netmask) ||
        !parse_ipv4(s_cfg.gateway, &ip_info.gw))
    {
        return ESP_ERR_INVALID_ARG;
    }
    err = esp_netif_set_ip_info(s_eth_netif, &ip_info);
    if (err != ESP_OK)
        return err;

    esp_ip4_addr_t dns4;
    if (parse_ipv4(s_cfg.dns, &dns4))
    {
        esp_netif_dns_info_t dns = {0};
        dns.ip.type = ESP_IPADDR_TYPE_V4;
        dns.ip.u_addr.ip4.addr = dns4.addr;
        (void)esp_netif_set_dns_info(s_eth_netif, ESP_NETIF_DNS_MAIN, &dns);
    }
    return ESP_OK;
}

static void eth_event_handler(void *arg, esp_event_base_t base, int32_t id, void *data)
{
    (void)arg;

    if (base == ETH_EVENT)
    {
        if (id == ETHERNET_EVENT_CONNECTED)
        {
            s_link_up = true;
            s_has_ip = false;

            eth_speed_t speed = ETH_SPEED_10M;
            eth_duplex_t duplex = ETH_DUPLEX_HALF;
            (void)esp_eth_ioctl(s_eth_handle, ETH_CMD_G_SPEED, &speed);
            (void)esp_eth_ioctl(s_eth_handle, ETH_CMD_G_DUPLEX_MODE, &duplex);

            ESP_LOGI(TAG, "eth0 link up: %d Mbps %s duplex",
                     speed == ETH_SPEED_100M ? 100 : 10,
                     duplex == ETH_DUPLEX_FULL ? "full" : "half");
        }
        else if (id == ETHERNET_EVENT_DISCONNECTED)
        {
            s_link_up = false;
            s_has_ip = false;
            ESP_LOGW(TAG, "eth0 link down");
        }
        else if (id == ETHERNET_EVENT_START)
        {
            ESP_LOGI(TAG, "eth0 started");
        }
        else if (id == ETHERNET_EVENT_STOP)
        {
            s_link_up = false;
            s_has_ip = false;
            ESP_LOGI(TAG, "eth0 stopped");
        }
        return;
    }

    if (base == IP_EVENT && id == IP_EVENT_ETH_GOT_IP && data)
    {
        ip_event_got_ip_t *event = (ip_event_got_ip_t *)data;
        s_has_ip = true;

        ESP_LOGI(TAG,
                 "eth0 got IP: " IPSTR " netmask: " IPSTR " gateway: " IPSTR,
                 IP2STR(&event->ip_info.ip),
                 IP2STR(&event->ip_info.netmask),
                 IP2STR(&event->ip_info.gw));
    }
}

/* undo a driver setup that failed half-way (no W6100 on
 * the board: the chip does not answer, so esp_eth_driver_install() fails).
 * Without this every retry left a MAC behind, each with its own
 * "w6100_tsk" task (4 KB stack) and SPI device, until the SPI host ran out
 * of device slots. */
static void eth_setup_undo(void)
{
    if (s_eth_handle)
    {
        (void)esp_eth_driver_uninstall(s_eth_handle);
        s_eth_handle = NULL;
    }
    if (s_phy)
    {
        s_phy->del(s_phy);
        s_phy = NULL;
    }
    if (s_mac)
    {
        s_mac->del(s_mac);
        s_mac = NULL;
    }
}

esp_err_t tdsh_eth_start(void)
{
    esp_err_t err = cfg_load();
    if (err != ESP_OK)
        return err;
    if (!s_cfg.enabled)
        return ESP_ERR_INVALID_STATE;
    if (!board_has_eth())
        return ESP_ERR_NOT_SUPPORTED;   /* no W6100 on this board */
    if (!hw_valid())
    {
        ESP_LOGW(TAG, "W6100 pins are not configured; set eth.* in the board configuration (lan hw set)");
        return ESP_ERR_INVALID_ARG;
    }

    err = esp_netif_init();
    if (err != ESP_OK && err != ESP_ERR_INVALID_STATE)
        return err;
    err = esp_event_loop_create_default();
    if (err != ESP_OK && err != ESP_ERR_INVALID_STATE)
        return err;

    if (!s_initialized)
    {
        spi_bus_config_t buscfg = {
            .mosi_io_num = s_cfg.mosi_gpio,
            .miso_io_num = s_cfg.miso_gpio,
            .sclk_io_num = s_cfg.sclk_gpio,
            .quadwp_io_num = -1,
            .quadhd_io_num = -1,
            .max_transfer_sz = 0,
        };
        err = spi_bus_initialize((spi_host_device_t)s_cfg.spi_host, &buscfg, SPI_DMA_CH_AUTO);
        if (err == ESP_OK)
        {
        }
        else if (err != ESP_ERR_INVALID_STATE)
        {
            ESP_LOGE(TAG, "SPI bus init failed: %s", esp_err_to_name(err));
            return err;
        }

        spi_device_interface_config_t spi_devcfg = {
            .mode = 0,
            .clock_speed_hz = (int)s_cfg.spi_clock_mhz * 1000 * 1000,
            .queue_size = 16,
            .spics_io_num = s_cfg.cs_gpio,
        };
        eth_w6100_config_t w6100_config =
            ETH_W6100_DEFAULT_CONFIG((spi_host_device_t)s_cfg.spi_host, &spi_devcfg);
        w6100_config.base.int_gpio_num = s_cfg.int_gpio;
        if (s_cfg.int_gpio < 0)
            w6100_config.base.poll_period_ms = s_cfg.poll_ms;

        eth_mac_config_t mac_config = ETH_MAC_DEFAULT_CONFIG();
        mac_config.rx_task_stack_size = 4096;
        s_mac = esp_eth_mac_new_w6100(&w6100_config, &mac_config);
        if (!s_mac)
            return ESP_ERR_NO_MEM;

        eth_phy_config_t phy_config = ETH_PHY_DEFAULT_CONFIG();
        phy_config.reset_gpio_num = s_cfg.rst_gpio;
        s_phy = esp_eth_phy_new_w6100(&phy_config);
        if (!s_phy)
        {
            eth_setup_undo();
            return ESP_ERR_NO_MEM;
        }

        esp_eth_config_t eth_config = ETH_DEFAULT_CONFIG(s_mac, s_phy);
        err = esp_eth_driver_install(&eth_config, &s_eth_handle);
        if (err != ESP_OK)
        {
            s_eth_handle = NULL;
            eth_setup_undo();
            return err;
        }

        /*
         * Important for W6100: assign an ESP32-C6-derived Ethernet MAC
         * before the driver is started. Without this the W6100 may report
         * 00:00:00:00:00:00 and DHCP will not work correctly.
         */
        err = configure_eth_mac();
        if (err != ESP_OK)
        {
            eth_setup_undo();
            return err;
        }

        esp_netif_inherent_config_t base_cfg = ESP_NETIF_INHERENT_DEFAULT_ETH();
        base_cfg.if_key = "ETH_TDSH";
        base_cfg.if_desc = "eth0";
        base_cfg.route_prio = 150;
        esp_netif_config_t netif_cfg = {
            .base = &base_cfg,
            .stack = ESP_NETIF_NETSTACK_DEFAULT_ETH,
        };
        s_eth_netif = esp_netif_new(&netif_cfg);
        if (!s_eth_netif)
            return ESP_ERR_NO_MEM;

        s_glue = esp_eth_new_netif_glue(s_eth_handle);
        if (!s_glue)
            return ESP_ERR_NO_MEM;
        err = esp_netif_attach(s_eth_netif, s_glue);
        if (err != ESP_OK)
            return err;

        err = esp_event_handler_register(ETH_EVENT, ESP_EVENT_ANY_ID, eth_event_handler, NULL);
        if (err != ESP_OK)
            return err;
        err = esp_event_handler_register(IP_EVENT, IP_EVENT_ETH_GOT_IP, eth_event_handler, NULL);
        if (err != ESP_OK)
            return err;

        /*
         * Explicitly apply IP mode. ESP_NETIF_INHERENT_DEFAULT_ETH() already
         * supports DHCP, but doing this here makes the state deterministic
         * after mode changes and reboots.
         */
        err = apply_ip_config();
        if (err != ESP_OK &&
            err != ESP_ERR_ESP_NETIF_DHCP_ALREADY_STARTED)
        {
            ESP_LOGE(TAG, "Ethernet IP configuration failed: %s",
                     esp_err_to_name(err));
            return err;
        }

        s_initialized = true;
    }

    if (s_started)
        return ESP_OK;
    s_link_up = false;
    s_has_ip = false;
    err = esp_eth_start(s_eth_handle);
    if (err != ESP_OK)
        return err;

    s_started = true;

    if (s_cfg.dhcp)
    {
        err = esp_netif_dhcpc_start(s_eth_netif);
        if (err != ESP_OK &&
            err != ESP_ERR_ESP_NETIF_DHCP_ALREADY_STARTED)
        {
            ESP_LOGE(TAG, "DHCP client start failed: %s",
                     esp_err_to_name(err));
            return err;
        }
        ESP_LOGI(TAG, "DHCP client active on eth0");
    }

    return ESP_OK;
}

esp_err_t tdsh_eth_stop(void)
{
    if (!s_initialized || !s_started)
        return ESP_OK;
    esp_err_t err = esp_eth_stop(s_eth_handle);
    if (err == ESP_OK)
    {
        s_started = false;
        s_link_up = false;
        s_has_ip = false;
    }
    return err;
}

bool tdsh_eth_is_connected(void)
{
    return s_initialized && s_started && s_link_up && s_has_ip;
}

void *tdsh_eth_netif(void)
{
    return s_eth_netif;
}

int tdsh_eth_get_info(tdsh_eth_info_t *info)
{
    if (!info)
        return -EINVAL;
    memset(info, 0, sizeof(*info));
    (void)cfg_load();
    info->enabled = s_cfg.enabled;
    info->dhcp = s_cfg.dhcp;
    info->initialized = s_initialized;
    info->link_up = s_link_up;
    info->connected = tdsh_eth_is_connected();
    if (!s_initialized)
        return 0;

    esp_err_t mac_err =
        esp_eth_ioctl(s_eth_handle, ETH_CMD_G_MAC_ADDR, info->mac);

    /*
     * The driver should already contain the configured MAC. As a defensive
     * fallback for status output, derive it again if the read failed or
     * somehow returned all zeros.
     */
    if (mac_err != ESP_OK || mac_is_zero(info->mac))
    {
        (void)esp_read_mac(info->mac, ESP_MAC_ETH);
    }

    eth_speed_t speed;
    if (esp_eth_ioctl(s_eth_handle, ETH_CMD_G_SPEED, &speed) == ESP_OK)
    {
        info->speed_mbps = speed == ETH_SPEED_100M ? 100 : 10;
    }
    eth_duplex_t duplex;
    if (esp_eth_ioctl(s_eth_handle, ETH_CMD_G_DUPLEX_MODE, &duplex) == ESP_OK)
    {
        info->full_duplex = duplex == ETH_DUPLEX_FULL;
    }
    if (s_eth_netif)
    {
        esp_netif_ip_info_t ip;
        if (esp_netif_get_ip_info(s_eth_netif, &ip) == ESP_OK)
        {
            info->ip.addr = ip.ip.addr;
            info->netmask.addr = ip.netmask.addr;
            info->gateway.addr = ip.gw.addr;
        }
        esp_netif_dns_info_t dns;
        if (esp_netif_get_dns_info(s_eth_netif, ESP_NETIF_DNS_MAIN, &dns) == ESP_OK &&
            dns.ip.type == ESP_IPADDR_TYPE_V4)
        {
            info->dns.addr = dns.ip.u_addr.ip4.addr;
        }
    }
    return 0;
}

static void print_hw(void)
{
    printf("W6100 hardware (board configuration, keys eth.*):\n");
    printf("  chip:      %s\n", board_has_eth() ? "w6100" : "none (set eth.chip = w6100)");
    printf("  spi_host:  %d\n", s_cfg.spi_host);
    printf("  miso:      %d\n", s_cfg.miso_gpio);
    printf("  mosi:      %d\n", s_cfg.mosi_gpio);
    printf("  sclk:      %d\n", s_cfg.sclk_gpio);
    printf("  cs:        %d\n", s_cfg.cs_gpio);
    printf("  int:       %d%s\n", s_cfg.int_gpio, s_cfg.int_gpio < 0 ? " (polling)" : "");
    printf("  reset:     %d\n", s_cfg.rst_gpio);
    printf("  spi_clock: %u MHz\n", (unsigned)s_cfg.spi_clock_mhz);
    if (s_cfg.int_gpio < 0)
        printf("  poll:      %u ms\n", (unsigned)s_cfg.poll_ms);
    if (!hw_valid())
        printf("  status:    incomplete - configure MISO/MOSI/SCLK/CS\n");
}

static void print_config(void)
{
    printf("LAN configuration:\n");
    printf("  enabled:   %s\n", s_cfg.enabled ? "yes" : "no");
    printf("  mode:      %s\n", s_cfg.dhcp ? "DHCP" : "static");
    if (!s_cfg.dhcp)
    {
        printf("  ip:        %s\n", s_cfg.ip);
        printf("  netmask:   %s\n", s_cfg.netmask);
        printf("  gateway:   %s\n", s_cfg.gateway);
        printf("  dns:       %s\n", s_cfg.dns);
    }
}

static void print_status(void)
{
    tdsh_eth_info_t i;
    (void)tdsh_eth_get_info(&i);
    printf("Interface: eth0\n");
    printf("Enabled:   %s\n", i.enabled ? "yes" : "no");
    printf("Driver:    %s\n", i.initialized ? "initialized" : "not initialized");
    printf("Link:      %s\n", i.link_up ? "up" : "down");
    printf("Mode:      %s\n", i.dhcp ? "DHCP" : "static");
    if (i.initialized)
    {
        printf("MAC:       %02X:%02X:%02X:%02X:%02X:%02X\n",
               i.mac[0], i.mac[1], i.mac[2], i.mac[3], i.mac[4], i.mac[5]);
        if (i.link_up)
        {
            printf("Speed:     %d Mbps\n", i.speed_mbps);
            printf("Duplex:    %s\n", i.full_duplex ? "full" : "half");
        }
    }
    if (i.ip.addr != 0)
    {
        ip4_addr_t a;
        a.addr = i.ip.addr;
        printf("IP:        %s\n", ip4addr_ntoa(&a));
        a.addr = i.netmask.addr;
        printf("Netmask:   %s\n", ip4addr_ntoa(&a));
        a.addr = i.gateway.addr;
        printf("Gateway:   %s\n", ip4addr_ntoa(&a));
        a.addr = i.dns.addr;
        printf("DNS:       %s\n", ip4addr_ntoa(&a));
    }
    else if (i.link_up && i.dhcp)
    {
        printf("IP:        waiting for DHCP lease\n");
    }
}

int tdsh_cmd_lan(tdsh_session_t *session, int argc, char **argv)
{
    (void)session;
    esp_err_t err = cfg_load();
    if (err != ESP_OK)
    {
        printf("LAN configuration error: %s\n", esp_err_to_name(err));
        return 1;
    }

    if (argc == 1 || (argc == 2 && strcmp(argv[1], "status") == 0))
    {
        print_status();
        return 0;
    }
    if (argc == 2 && strcmp(argv[1], "config") == 0)
    {
        print_config();
        print_hw();
        return 0;
    }
    if (argc == 2 && strcmp(argv[1], "enable") == 0)
    {
        s_cfg.enabled = 1;
        if ((err = cfg_save()) != ESP_OK)
            return 1;
        err = tdsh_eth_start();
        if (err != ESP_OK)
        {
            printf("LAN enable failed: %s\n", esp_err_to_name(err));
            if (!hw_valid())
            {
                printf("Configure hardware with:\n");
                printf("  lan hw set <host> <miso> <mosi> <sclk> <cs> <int|-1> <rst|-1> <MHz>\n");
            }
            return 1;
        }
        printf("LAN enabled. Waiting for Ethernet link/DHCP.\n");
        return 0;
    }
    if (argc == 2 && strcmp(argv[1], "disable") == 0)
    {
        (void)tdsh_eth_stop();
        s_cfg.enabled = 0;
        if (cfg_save() != ESP_OK)
            return 1;
        printf("LAN disabled.\n");
        return 0;
    }
    if (argc == 2 && strcmp(argv[1], "dhcp") == 0)
    {
        s_cfg.dhcp = 1;
        if (cfg_save() != ESP_OK)
            return 1;
        s_has_ip = false;
        if (s_initialized)
        {
            (void)esp_netif_dhcpc_stop(s_eth_netif);
            err = esp_netif_dhcpc_start(s_eth_netif);
            if (err != ESP_OK && err != ESP_ERR_ESP_NETIF_DHCP_ALREADY_STARTED)
            {
                printf("DHCP start failed: %s\n", esp_err_to_name(err));
                return 1;
            }
        }
        printf("LAN IPv4 mode set to DHCP. Waiting for lease.\n");
        return 0;
    }
    if (argc == 5 && strcmp(argv[1], "static") == 0)
    {
        esp_ip4_addr_t tmp;
        if (!parse_ipv4(argv[2], &tmp) || !parse_ipv4(argv[3], &tmp) || !parse_ipv4(argv[4], &tmp))
        {
            printf("Invalid IPv4 address.\n");
            return 1;
        }
        s_cfg.dhcp = 0;
        snprintf(s_cfg.ip, sizeof(s_cfg.ip), "%s", argv[2]);
        snprintf(s_cfg.netmask, sizeof(s_cfg.netmask), "%s", argv[3]);
        snprintf(s_cfg.gateway, sizeof(s_cfg.gateway), "%s", argv[4]);
        if (cfg_save() != ESP_OK)
            return 1;
        if (s_initialized && (err = apply_ip_config()) != ESP_OK)
        {
            printf("Static IP apply failed: %s\n", esp_err_to_name(err));
            return 1;
        }
        printf("LAN static IPv4 configuration saved.\n");
        return 0;
    }
    if (argc == 3 && strcmp(argv[1], "dns") == 0)
    {
        esp_ip4_addr_t tmp;
        if (!parse_ipv4(argv[2], &tmp))
        {
            printf("Invalid DNS IPv4 address.\n");
            return 1;
        }
        snprintf(s_cfg.dns, sizeof(s_cfg.dns), "%s", argv[2]);
        if (cfg_save() != ESP_OK)
            return 1;
        if (s_initialized && !s_cfg.dhcp)
            (void)apply_ip_config();
        printf("LAN DNS saved.\n");
        return 0;
    }
    if (argc == 2 && strcmp(argv[1], "hw") == 0)
    {
        print_hw();
        return 0;
    }
    if (argc == 11 && strcmp(argv[1], "hw") == 0 && strcmp(argv[2], "set") == 0)
    {
        long v[8];
        for (int i = 0; i < 8; ++i)
        {
            char *end = NULL;
            v[i] = strtol(argv[i + 3], &end, 10);
            if (!end || *end != '\0')
            {
                printf("Invalid numeric hardware value.\n");
                return 1;
            }
        }
        if (v[0] < 0 || v[0] > 2 || v[1] < 0 || v[2] < 0 || v[3] < 0 || v[4] < 0 ||
            v[5] < -1 || v[6] < -1 || v[7] < 1 || v[7] > 40)
        {
            printf("Invalid W6100 hardware settings.\n");
            return 1;
        }
        /* saved in the board configuration file. */
        static const char *const keys[8] = {"eth.spi_host", "eth.miso", "eth.mosi", "eth.sclk",
                                            "eth.cs", "eth.int", "eth.rst", "eth.spi_mhz"};
        char num[12];
        if (tdsh_board_set("eth.chip", "w6100") != 0)
        {
            printf("Cannot write the board configuration file.\n");
            return 1;
        }
        for (int i = 0; i < 8; ++i)
        {
            snprintf(num, sizeof(num), "%ld", v[i]);
            if (tdsh_board_set(keys[i], num) != 0)
            {
                printf("Cannot write the board configuration file.\n");
                return 1;
            }
        }
        cfg_apply_board();
        print_hw();
        printf("Saved in /etc/board.conf. Restart to apply new SPI pins.\n");
        return 0;
    }
    if (argc == 3 && strcmp(argv[1], "poll") == 0)
    {
        long ms = strtol(argv[2], NULL, 10);
        if (ms < 10 || ms > 5000)
        {
            printf("Polling period must be 10..5000 ms.\n");
            return 1;
        }
        char num[12];
        snprintf(num, sizeof(num), "%ld", ms);
        if (tdsh_board_set("eth.poll_ms", num) != 0)
            return 1;
        s_cfg.poll_ms = (uint16_t)ms;
        printf("W6100 polling period saved in /etc/board.conf; restart to apply.\n");
        return 0;
    }

    printf("usage:\n");
    printf("  lan status|config|enable|disable|dhcp\n");
    printf("  lan static <ip> <netmask> <gateway>\n");
    printf("  lan dns <server>\n");
    printf("  lan hw\n");
    printf("  lan hw set <host> <miso> <mosi> <sclk> <cs> <int|-1> <rst|-1> <MHz>\n");
    printf("  lan poll <milliseconds>\n");
    return 2;
}

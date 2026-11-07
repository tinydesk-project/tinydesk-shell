#include "tdsh_espidf_internal.h"
#include "tdsh_board.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "driver/gpio.h"
#include "esp_chip_info.h"
#include "esp_heap_caps.h"
#include "esp_system.h"

static int usage(const char *name)
{
    const tdsh_command_t *cmd = tdsh_command_find(name);
    if (cmd)
        printf("usage: %s\n", cmd->usage);
    return 2;
}

static int cmd_idfinfo(tdsh_session_t *session, int argc, char **argv)
{
    (void)session;
    (void)argv;
    if (argc != 1)
        return usage("idfinfo");
    esp_chip_info_t info;
    esp_chip_info(&info);
    printf("ESP-IDF:  %s\n", esp_get_idf_version());
    printf("cores:    %d\n", info.cores);
    printf("revision: %d\n", info.revision);
    printf("features: WiFi%s%s\n",
           (info.features & CHIP_FEATURE_BT) ? ", BT" : "",
           (info.features & CHIP_FEATURE_BLE) ? ", BLE" : "");
    return 0;
}

static int cmd_reboot(tdsh_session_t *session, int argc, char **argv)
{
    (void)session;
    (void)argv;
    if (argc != 1)
        return usage("reboot");
    printf("Rebooting...\n");
    fflush(stdout);
    tdsh_sleep_ms(100);
    esp_restart();
    return 0;
}

static int cmd_heap(tdsh_session_t *session, int argc, char **argv)
{
    (void)session;
    (void)argv;
    if (argc != 1)
        return usage("heap");
    size_t free_b = heap_caps_get_free_size(MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
    size_t largest = heap_caps_get_largest_free_block(MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
    size_t min_free = heap_caps_get_minimum_free_size(MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
    printf("Internal RAM: free=%u, largest=%u, minimum-free=%u bytes\n",
           (unsigned)free_b, (unsigned)largest, (unsigned)min_free);
    tdsh_memory_stats_t st;
    tdsh_memory_get_stats(&st);
    printf("Shell tracked: live=%u blocks / %u bytes, peak=%u bytes\n",
           (unsigned)st.live_blocks, (unsigned)st.live_bytes, (unsigned)st.peak_bytes);
    return 0;
}

static int parse_gpio(const char *text, gpio_num_t *gpio)
{
    char *end = NULL;
    long pin = strtol(text, &end, 10);
    if (!end || *end || pin < 0 || pin >= GPIO_NUM_MAX || !GPIO_IS_VALID_GPIO(pin))
        return -EINVAL;
    *gpio = (gpio_num_t)pin;
    return 0;
}

static int cmd_gpio(tdsh_session_t *session, int argc, char **argv)
{
    (void)session;
    if (argc < 3)
        return usage("gpio");
    gpio_num_t pin;
    if (parse_gpio(argv[2], &pin) != 0)
    {
        printf("gpio: invalid GPIO number: %s\n", argv[2]);
        return 1;
    }
    if (strcmp(argv[1], "init") == 0)
    {
        if (argc != 4)
            return usage("gpio");
        gpio_config_t cfg = {0};
        cfg.pin_bit_mask = 1ULL << pin;
        cfg.pull_down_en = GPIO_PULLDOWN_DISABLE;
        cfg.pull_up_en = GPIO_PULLUP_DISABLE;
        cfg.intr_type = GPIO_INTR_DISABLE;
        if (strcmp(argv[3], "out") == 0)
        {
            if (!GPIO_IS_VALID_OUTPUT_GPIO(pin))
                return 1;
            cfg.mode = GPIO_MODE_OUTPUT;
        }
        else if (strcmp(argv[3], "in") == 0)
            cfg.mode = GPIO_MODE_INPUT;
        else
            return usage("gpio");
        esp_err_t err = gpio_config(&cfg);
        if (err != ESP_OK)
        {
            printf("gpio: %s\n", esp_err_to_name(err));
            return 1;
        }
        return 0;
    }
    if (strcmp(argv[1], "set") == 0)
    {
        if (argc != 4 || !GPIO_IS_VALID_OUTPUT_GPIO(pin))
            return usage("gpio");
        int level;
        if (!strcmp(argv[3], "1") || !strcmp(argv[3], "high"))
            level = 1;
        else if (!strcmp(argv[3], "0") || !strcmp(argv[3], "low"))
            level = 0;
        else
            return usage("gpio");
        return gpio_set_level(pin, level) == ESP_OK ? 0 : 1;
    }
    if (strcmp(argv[1], "get") == 0)
    {
        if (argc != 3)
            return usage("gpio");
        printf("%d\n", gpio_get_level(pin));
        return 0;
    }
    return usage("gpio");
}

/* board: show and edit the board configuration (tdsh_board.h). */
static const char *origin_name(tdsh_board_origin_t o)
{
    return o == TDSH_BOARD_FILE ? "file" : o == TDSH_BOARD_BUILTIN ? "built-in"
                                                                   : "-";
}

static void board_usage(void)
{
    printf("usage:\n"
           "  board [show]            every setting and where it comes from\n"
           "  board get <key>\n"
           "  board set <key> <value> (root) write it to /etc/board.conf\n"
           "  board unset <key>       (root) remove it from /etc/board.conf\n"
           "  board init              (root) start /etc/board.conf from the built-in settings\n"
           "  board save              (root) copy the built-in settings into /etc/board.conf,\n"
           "                          so firmware without them (an official update) keeps them\n"
           "Settings are read at start-up: restart after a change.\n");
}

static int cmd_board(tdsh_session_t *session, int argc, char **argv)
{
    const char *op = argc > 1 ? argv[1] : "show";
    bool root = strcmp(session->username, "root") == 0;
    if (!strcmp(op, "show") && argc <= 2)
    {
        int n = tdsh_board_count();
        printf("Board configuration: %d setting%s (device file /etc/board.conf)\n", n, n == 1 ? "" : "s");
        for (int i = 0; i < n; i++)
        {
            const char *k, *v;
            tdsh_board_origin_t o;
            if (tdsh_board_at(i, &k, &v, &o))
                printf("  %-22s = %-16s (%s)\n", k, v, origin_name(o));
        }
        if (!n)
            printf("  (nothing configured: see `board set` and board.example.conf)\n");
        int unsaved = tdsh_board_unsaved();
        if (unsaved)
            printf("%d built-in setting%s: firmware built without %s (an official update) would\n"
                   "lose %s. `board save` copies %s into /etc/board.conf.\n",
                   unsaved, unsaved == 1 ? "" : "s", unsaved == 1 ? "it" : "them",
                   unsaved == 1 ? "it" : "them", unsaved == 1 ? "it" : "them");
        return 0;
    }
    if (!strcmp(op, "get") && argc == 3)
    {
        const char *v = tdsh_board_get(argv[2]);
        if (!v)
        {
            printf("%s is not set\n", argv[2]);
            return 1;
        }
        printf("%s = %s (%s)\n", argv[2], v, origin_name(tdsh_board_origin(argv[2])));
        return 0;
    }
    if ((!strcmp(op, "set") && argc == 4) || (!strcmp(op, "unset") && argc == 3) ||
        (!strcmp(op, "init") && argc == 2) || (!strcmp(op, "save") && argc == 2))
    {
        if (!root)
        {
            printf("board: permission denied: root required\n");
            return 1;
        }
        if (!strcmp(op, "save"))
        {
            int saved = tdsh_board_save_builtin();
            if (saved < 0)
            {
                printf("board: cannot write /etc/board.conf: %s\n", strerror(-saved));
                return 1;
            }
            if (saved == 0)
                printf("Nothing to save: no setting comes only from the firmware.\n");
            else
                printf("Saved %d built-in setting%s in /etc/board.conf.\n", saved, saved == 1 ? "" : "s");
            return 0;
        }
        if (!strcmp(op, "init"))
        {
            FILE *f = fopen(tdsh_board_file(), "r");
            if (f)
            {
                fclose(f);
                printf("board: /etc/board.conf already exists (edit it with nano)\n");
                return 1;
            }
            f = fopen(tdsh_board_file(), "w");
            if (!f)
            {
                printf("board: cannot write /etc/board.conf\n");
                return 1;
            }
            const char *b = tdsh_board_builtin();
            fputs("# Board configuration: this file overrides the settings built into\n"
                  "# the firmware. Restart after a change. Keys: see board.example.conf\n\n",
                  f);
            if (b)
                fputs(b, f);
            fclose(f);
            printf("Wrote /etc/board.conf. Edit it (nano /etc/board.conf), then restart.\n");
            return 0;
        }
        int rc = tdsh_board_set(argv[2], !strcmp(op, "set") ? argv[3] : NULL);
        if (rc != 0)
        {
            printf("board: %s\n", rc == -EINVAL ? "keys are a-z 0-9 . _ - and values one line without #" : strerror(-rc));
            return 1;
        }
        printf("Saved in /etc/board.conf. Restart to apply.\n");
        return 0;
    }
    board_usage();
    return 2;
}

static const tdsh_command_t s_base_commands[] = {
    {"board", "board [show|get|set|unset|init|save] ...", "Show or change the board configuration (pins)", cmd_board, 0},
    {"users", "users", "List users", tdsh_cmd_users, 0},
    {"useradd", "useradd <username> [admin|user]", "Create an account", tdsh_cmd_useradd, TDSH_CMD_ADMIN_ONLY | TDSH_CMD_INTERACTIVE},
    {"userdel", "userdel <username> [-f]", "Delete a user", tdsh_cmd_userdel, TDSH_CMD_ADMIN_ONLY | TDSH_CMD_INTERACTIVE},
    {"login", "login <username>", "Login as another user", tdsh_cmd_login, TDSH_CMD_INTERACTIVE},
    {"logout", "logout", "Logout current session", tdsh_cmd_logout, TDSH_CMD_INTERACTIVE},
    {"userrole", "userrole <username> [admin|user]", "Show or set account role", tdsh_cmd_userrole, 0},
    {"userrights", "userrights <username> [+right|-right ...]", "Show or share account permissions", tdsh_cmd_userrights, 0},
    {"bootuser", "bootuser [username]", "Show/set physical-console boot user", tdsh_cmd_bootuser, 0},
    {"rootrecover", "rootrecover", "Reset root password from physical USB console", tdsh_cmd_rootrecover, TDSH_CMD_INTERACTIVE},
    {"tz", "tz [[+|-]HH:MM]", "Show/set user timezone offset", tdsh_cmd_tz, 0},
    {"date", "date", "Show date/time using user timezone", tdsh_cmd_date, 0},
    {"cal", "cal", "Print current month calendar", tdsh_cmd_cal, 0},
    {"passwd", "passwd", "Change current user's password", tdsh_cmd_passwd, TDSH_CMD_INTERACTIVE},
    {"idfinfo", "idfinfo", "Show ESP-IDF/chip information", cmd_idfinfo, 0},
    {"heap", "heap", "Show ESP-IDF heap and shell tracked allocations", cmd_heap, 0},
    {"reboot", "reboot", "Restart the MCU", cmd_reboot, TDSH_CMD_RIGHT(TDSH_RIGHT_SYSTEM)},
};

static const tdsh_command_t s_network_commands[] = {
    {"networks", "networks", "List saved Wi-Fi networks", tdsh_cmd_networks, 0},
    {"wifiscan", "wifiscan", "Scan and list available Wi-Fi networks", tdsh_cmd_wifiscan, 0},
    {"wificonnect", "wificonnect [saved_ssid]", "Connect to a saved network", tdsh_cmd_wificonnect, TDSH_CMD_RIGHT(TDSH_RIGHT_NETWORK)},
    {"wifidisconnect", "wifidisconnect", "Disconnect station Wi-Fi", tdsh_cmd_wifidisconnect, TDSH_CMD_RIGHT(TDSH_RIGHT_NETWORK)},
    {"wifiadd", "wifiadd <ssid> [password]", "Save a Wi-Fi network in NVS", tdsh_cmd_wifiadd, TDSH_CMD_RIGHT(TDSH_RIGHT_NETWORK)},
    {"wifiremove", "wifiremove <ssid ...>", "Remove saved Wi-Fi networks", tdsh_cmd_wifiremove, TDSH_CMD_RIGHT(TDSH_RIGHT_NETWORK)},
    {"lan", "lan <status|config|enable|disable|dhcp|static|dns|hw|poll> ...", "Configure W6100 Ethernet", tdsh_cmd_lan, TDSH_CMD_RIGHT(TDSH_RIGHT_NETWORK)},
    {"network", "network [status] | network mode [auto|lan|wifi|both] | network autowifi [on|off]", "Configure network policy", tdsh_cmd_network, TDSH_CMD_RIGHT(TDSH_RIGHT_NETWORK)},
    {"netmount", "netmount <list|add|connect|disconnect|status|remove> ...", "Map SMB2/SMB3 shares", tdsh_cmd_netmount, 0},
    {"ifconfig", "ifconfig", "Show network interfaces and default route", tdsh_cmd_ifconfig, 0},
    {"ping", "ping [-c count] <host/address ...>", "Send ICMP echo requests", tdsh_cmd_ping, 0},
};

static const tdsh_command_t s_remote_server_commands[] = {
    /* not root-only any more. The commands themselves allow
     * root anywhere and any user on the local console (Terminal / desktop). */
    {"ftp", "ftp <start|stop|restart|status> [port]", "Control FTP server", tdsh_cmd_ftp, TDSH_CMD_RIGHT(TDSH_RIGHT_NETWORK)},
    {"ssh", "ssh <start|stop|restart|status> [port] | ssh hostkey [new]", "Control SSH/SFTP server", tdsh_cmd_ssh, TDSH_CMD_RIGHT(TDSH_RIGHT_NETWORK)},
};

static const tdsh_command_t s_editor_commands[] = {
    {"write", "write <file> [text ...]", "Line editor or direct file writer", tdsh_cmd_write, TDSH_CMD_INTERACTIVE},
    {"nano", "nano <file>", "Full-screen VT100 nano-style editor", tdsh_cmd_nano, TDSH_CMD_INTERACTIVE},
};

static const tdsh_command_t s_hardware_commands[] = {
    {"gpio", "gpio <init|get|set> ...", "Configure and control GPIO", cmd_gpio, TDSH_CMD_RIGHT(TDSH_RIGHT_HARDWARE)},
    {"hwtest", "hwtest <status|sd|uart|rs485|all> [count]", "Board SD/UART/RS485 hardware tests", tdsh_cmd_hwtest, TDSH_CMD_RIGHT(TDSH_RIGHT_HARDWARE)},
    {"sd", "sd [status] | sd mount | sd umount | sd format --yes", "SD card at /sd (FAT)", tdsh_cmd_sd, TDSH_CMD_ROOT_ONLY},
};

#define REG_GROUP(group)                                                              \
    do                                                                                \
    {                                                                                 \
        int rc = tdsh_register_commands((group), sizeof(group) / sizeof((group)[0])); \
        if (rc != 0)                                                                  \
            return rc;                                                                \
    } while (0)

int tdsh_espidf_register_commands(const tdsh_espidf_config_t *config)
{
    if (!config)
        return -EINVAL;
    REG_GROUP(s_base_commands);
    if (config->register_network_commands)
        REG_GROUP(s_network_commands);
    if (config->register_remote_server_commands)
        REG_GROUP(s_remote_server_commands);
    if (config->register_editor_commands)
        REG_GROUP(s_editor_commands);
    if (config->register_hardware_commands)
        REG_GROUP(s_hardware_commands);
    return 0;
}

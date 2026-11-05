#ifndef TDSH_ESP_IDF_H
#define TDSH_ESP_IDF_H

#include "tdsh.h"
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

#define TDSH_SHELL_TASK_STACK 24576
#define TDSH_DEFAULT_FTP_PORT 21
#define TDSH_DEFAULT_SSH_PORT 22

typedef struct
{
    const char *hostname;
    const char *default_user;
    size_t history_length;
    bool format_fs_if_mount_failed;
    bool register_core_builtins;
    bool register_network_commands;
    bool register_remote_server_commands;
    bool register_editor_commands;
    bool register_hardware_commands;
    bool init_network_manager;
    /* The board configuration built into the firmware ("key = value"
     * text, see tdsh_board.h); NULL for none. /fs/etc/board.conf on the
     * device overrides it. */
    const char *board_config;
} tdsh_espidf_config_t;

#define TDSH_ESP_IDF_CONFIG_DEFAULT()            \
    {                                            \
        .hostname = "esp32",                     \
        .default_user = "root",                  \
        .history_length = 50,                    \
        .format_fs_if_mount_failed = true,       \
        .register_core_builtins = true,          \
        .register_network_commands = true,       \
        .register_remote_server_commands = true, \
        .register_editor_commands = true,        \
        .register_hardware_commands = true,      \
        .init_network_manager = true,            \
        .board_config = NULL,                    \
    }

/* New SDK-facing API. */
esp_err_t tdsh_espidf_init(const tdsh_espidf_config_t *config);
esp_err_t tdsh_espidf_start(void);

/* instead of tdsh_espidf_start(), run the local console
 * loop in the calling task using that task's current stdin/stdout (set them
 * to your own streams first, e.g. with funopen()). Never returns. The task is
 * used for startup and login. Physical recovery also requires local transport
 * trust; shared remote transports must call tdsh_console_mark_remote(). */
void tdsh_espidf_run_console(void);

/* switch the console session to another (existing) user the
 * next time it waits for input (wake it by sending Ctrl+C), and read the
 * console's current user (changes with login / logout too). */
void tdsh_espidf_console_set_user(const char *username);
const char *tdsh_espidf_console_user(void);

/* The local console's width in columns, for the line editor: a function
 * that returns it (<= 0 if unknown), or NULL. Front ends that know their
 * terminal's size (TinyDesk's Terminal window) set it; without it the
 * editor asks a serial terminal (ESC[6n) and falls back to 80 columns.
 * SSH sessions use the width from the client's pty request. */
void tdsh_espidf_set_console_columns(int (*columns)(void));
void tdsh_espidf_set_console_flush(void (*flush)(void));
const tdsh_platform_api_t *tdsh_espidf_platform(void);
int tdsh_espidf_register_commands(const tdsh_espidf_config_t *config);

/* Short names for the configuration type, init and start. */
typedef tdsh_espidf_config_t tdsh_config_t;
#define TDSH_CONFIG_DEFAULT() TDSH_ESP_IDF_CONFIG_DEFAULT()
esp_err_t tdsh_init(const tdsh_config_t *config);
esp_err_t tdsh_start(void);

/* Interactive physical-console helpers. */
int tdsh_console_readline(const char *prompt, char *buf, size_t capacity, bool echo_input);
int tdsh_interactive_readline(tdsh_session_t *session, const char *prompt, char *buf, size_t capacity);
bool tdsh_is_local_console_task(void);
/* Task identity is not proof of physical access on a multiplexed desktop. */
bool tdsh_is_physical_console(void);
bool tdsh_console_begin_recovery(void);
void tdsh_console_end_recovery(void);
/* Call BEFORE accepting remote desktop input. False while recovery is active.
 * Successful takeover revokes physical trust until reboot, even after logout. */
bool tdsh_console_mark_remote(void);
int tdsh_session_set_user(tdsh_session_t *session, const char *username);
int tdsh_session_set_user_generation(tdsh_session_t *session,const char *username,uint32_t generation);
int tdsh_run_user_startup(tdsh_session_t *session);

/* ESP-IDF filesystem mount. Path normalization/resolution itself is core. */
esp_err_t tdsh_fs_init(bool format_if_mount_failed);
void tdsh_fs_print_info(void);

/* Users / authentication. */
esp_err_t tdsh_users_init(void);
bool tdsh_user_exists(const char *username);
bool tdsh_user_authenticate(const char *username, const char *password);
uint32_t tdsh_user_login(const char *username,const char *password);
typedef struct { char name[TDSH_USERNAME_MAX];tdsh_role_t role;uint32_t rights; } tdsh_user_info_t;
int tdsh_user_list(int index,tdsh_user_info_t *out);
tdsh_role_t tdsh_user_role(const char *username);
uint32_t tdsh_user_rights(const char *username);
uint32_t tdsh_user_generation(const char *username);
int tdsh_user_create(const char *actor,const char *name,const char *password,tdsh_role_t role,uint32_t rights);
int tdsh_user_access_set(const char *actor,const char *name,tdsh_role_t role,uint32_t rights);
int tdsh_user_password_set(const char *actor,const char *name,const char *old_password,const char *new_password);
/* Password hints: shown at sign-in to anyone at the device. Set by the
 * account itself or whoever may manage it; "" removes it. */
#define TDSH_HINT_MAX 64
int tdsh_user_hint_get(const char *name,char *out,size_t size);
int tdsh_user_hint_set(const char *actor,const char *name,const char *hint);
bool tdsh_hint_reveals(const char *hint,const char *password);
bool tdsh_remembered_user(char *out,size_t size);
uint32_t tdsh_remembered_login(char *out,size_t size);
bool tdsh_user_remember_allowed(const char *username);
int tdsh_boot_login_require_password(void);
int tdsh_cmd_userrole(tdsh_session_t *session,int argc,char **argv);
int tdsh_cmd_userrights(tdsh_session_t *session,int argc,char **argv);
bool tdsh_remote_access_ready(void);
bool tdsh_user_authenticate_remote(const char *username, const char *password);
int tdsh_cmd_users(tdsh_session_t *session, int argc, char **argv);
int tdsh_cmd_useradd(tdsh_session_t *session, int argc, char **argv);
int tdsh_cmd_userdel(tdsh_session_t *session, int argc, char **argv);
int tdsh_cmd_login(tdsh_session_t *session, int argc, char **argv);
int tdsh_cmd_logout(tdsh_session_t *session, int argc, char **argv);
int tdsh_cmd_passwd(tdsh_session_t *session, int argc, char **argv);
int tdsh_cmd_bootuser(tdsh_session_t *session, int argc, char **argv);
int tdsh_cmd_rootrecover(tdsh_session_t *session, int argc, char **argv);
int tdsh_boot_user_get(char *out, size_t out_size);
int tdsh_boot_user_set(const char *username);
int tdsh_boot_user_default(const char *username);

/* Wi-Fi / Ethernet / network. */
typedef enum
{
    TDSH_NETWORK_MODE_AUTO = 0,
    TDSH_NETWORK_MODE_LAN,
    TDSH_NETWORK_MODE_WIFI,
    TDSH_NETWORK_MODE_BOTH,
} tdsh_network_mode_t;

typedef struct
{
    bool initialized;
    bool connected;
    uint8_t mac[6];
    char ssid[33];
    int rssi;
    unsigned channel;
    struct
    {
        uint32_t addr;
    } ip, netmask, gateway, dns;
} tdsh_wifi_info_t;

typedef struct
{
    bool enabled;
    bool initialized;
    bool link_up;
    bool connected;
    bool dhcp;
    uint8_t mac[6];
    int speed_mbps;
    bool full_duplex;
    struct
    {
        uint32_t addr;
    } ip, netmask, gateway, dns;
} tdsh_eth_info_t;

esp_err_t tdsh_network_init(void);
bool tdsh_network_is_online(void);
tdsh_network_mode_t tdsh_network_get_mode(void);
int tdsh_cmd_network(tdsh_session_t *session, int argc, char **argv);
int tdsh_cmd_ifconfig(tdsh_session_t *session, int argc, char **argv);

esp_err_t tdsh_wifi_init(void);
esp_err_t tdsh_wifi_stop(void);
esp_err_t tdsh_wifi_autoconnect(bool verbose);
bool tdsh_wifi_is_connected(void);
void *tdsh_wifi_netif(void);
int tdsh_wifi_get_info(tdsh_wifi_info_t *info);
int tdsh_cmd_networks(tdsh_session_t *session, int argc, char **argv);
int tdsh_cmd_wifiscan(tdsh_session_t *session, int argc, char **argv);
int tdsh_cmd_wificonnect(tdsh_session_t *session, int argc, char **argv);
int tdsh_cmd_wifidisconnect(tdsh_session_t *session, int argc, char **argv);
int tdsh_cmd_wifiadd(tdsh_session_t *session, int argc, char **argv);
int tdsh_cmd_wifiremove(tdsh_session_t *session, int argc, char **argv);

/* structured Wi-Fi API (may block; use a worker task). */
typedef struct
{
    char ssid[33];
    int rssi;
    bool secure;
    bool saved;
} tdsh_wifi_ap_t;
/* Saved networks belong to the user who added them; networks added by root
 * (or saved before owners existed) are shared: every user may connect to
 * them, only root may change or remove them. `user` is the acting user. */
int tdsh_wifi_scan_list(tdsh_wifi_ap_t *out, int max, const char *user); /* count or -1 */
int tdsh_wifi_save(const char *ssid, const char *password, const char *user);
int tdsh_wifi_forget(const char *ssid, const char *user);  /* -2: not allowed */
int tdsh_wifi_connect_saved(const char *ssid, const char *user); /* 0 = connected */
int tdsh_wifi_disconnect_now(void);

esp_err_t tdsh_eth_start(void);
esp_err_t tdsh_eth_stop(void);
bool tdsh_eth_is_connected(void);
void *tdsh_eth_netif(void);
int tdsh_eth_get_info(tdsh_eth_info_t *info);
int tdsh_cmd_lan(tdsh_session_t *session, int argc, char **argv);

/* The password root has on a fresh device. It is public (the docs give it):
 * remote logins refuse it, and passwd says it while root still has it. */
#define TDSH_FACTORY_ROOT_PASSWORD "TinyDesk"

/* SMB2/3 mapped network drives. */
esp_err_t tdsh_netmount_init(void);
int tdsh_cmd_netmount(tdsh_session_t *session, int argc, char **argv);
bool tdsh_netmount_translate_logical(const char *logical, char *real_out, size_t real_out_size);
void tdsh_netmount_remove_owner(const char *owner);

/* The SD card as /sd (FAT over SPI; pins from the board configuration).
 * tdsh_sdcard_init() mounts it at boot when the board key sd.automount is 1.
 * tdsh_sdcard_card() is the sdmmc_card_t (sdmmc_cmd.h), NULL while not mounted. */
esp_err_t tdsh_sdcard_init(void);
esp_err_t tdsh_sdcard_mount(void);
esp_err_t tdsh_sdcard_unmount(void);
bool tdsh_sdcard_configured(void);
bool tdsh_sdcard_mounted(void);
void *tdsh_sdcard_card(void);
bool tdsh_sdcard_translate_logical(const char *logical, char *real_out, size_t real_out_size);
int tdsh_cmd_sd(tdsh_session_t *session, int argc, char **argv);

/* Time / ping / network servers / editors / hardware test. */
void tdsh_time_sync_start(void);
/* automatic (SNTP) time can be switched off; the choice is
 * kept in NVS (namespace "ush_time", key "auto", default on). While it is
 * off tdsh_time_sync_start() does nothing and SNTP is stopped.
 * tdsh_time_sync_now() syncs once even when it is off (blocks up to ~6 s;
 * returns 0 when the clock is valid afterwards). */
bool tdsh_time_auto(void);
int tdsh_time_set_auto(bool on);
int tdsh_time_sync_now(void);
int tdsh_cmd_tz(tdsh_session_t *session, int argc, char **argv);
int tdsh_cmd_date(tdsh_session_t *session, int argc, char **argv);
int tdsh_cmd_cal(tdsh_session_t *session, int argc, char **argv);
int tdsh_cmd_ping(tdsh_session_t *session, int argc, char **argv);
int tdsh_cmd_ftp(tdsh_session_t *session, int argc, char **argv);
int tdsh_cmd_ssh(tdsh_session_t *session, int argc, char **argv);
int tdsh_cmd_write(tdsh_session_t *session, int argc, char **argv);
int tdsh_cmd_nano(tdsh_session_t *session, int argc, char **argv);
int tdsh_cmd_hwtest(tdsh_session_t *session, int argc, char **argv);

/* server status / control for GUI front ends (the caller is
 * responsible for deciding who may do this). */
bool tdsh_ssh_is_running(uint16_t *port, int *clients);
int tdsh_ssh_set_running(bool on);
/* The SSH client's terminal width from its pty request, 0 if none. */
int tdsh_ssh_terminal_columns(void);
bool tdsh_ftp_is_running(uint16_t *port);
int tdsh_ftp_set_running(bool on);

#ifdef __cplusplus
}
#endif

#endif /* TDSH_ESP_IDF_H */

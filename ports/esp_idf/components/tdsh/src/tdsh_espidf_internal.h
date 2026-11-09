/*
 * tdsh_espidf_internal.h - what the ESP-IDF port's own sources share and
 * applications do not call: the built-in commands' handlers (registered by
 * tdsh_espidf_init), the start/stop routines it runs, and helpers between
 * the console, SSH and the file layers. Not part of the stable API: may
 * change in any release.
 */
#ifndef TDSH_ESPIDF_INTERNAL_H
#define TDSH_ESPIDF_INTERNAL_H

#include "tdsh_espidf.h"

#ifdef __cplusplus
extern "C" {
#endif

int tdsh_espidf_register_commands(const tdsh_espidf_config_t *config);
int tdsh_interactive_readline(tdsh_session_t *session, const char *prompt, char *buf, size_t capacity);
esp_err_t tdsh_fs_init(bool format_if_mount_failed);
void tdsh_fs_print_info(void);
int tdsh_cmd_userrole(tdsh_session_t *session, int argc, char **argv);
int tdsh_cmd_userrights(tdsh_session_t *session, int argc, char **argv);
int tdsh_cmd_users(tdsh_session_t *session, int argc, char **argv);
int tdsh_cmd_useradd(tdsh_session_t *session, int argc, char **argv);
int tdsh_cmd_userdel(tdsh_session_t *session, int argc, char **argv);
int tdsh_cmd_login(tdsh_session_t *session, int argc, char **argv);
int tdsh_cmd_logout(tdsh_session_t *session, int argc, char **argv);
int tdsh_cmd_passwd(tdsh_session_t *session, int argc, char **argv);
int tdsh_cmd_bootuser(tdsh_session_t *session, int argc, char **argv);
int tdsh_cmd_rootrecover(tdsh_session_t *session, int argc, char **argv);
esp_err_t tdsh_network_init(void);
int tdsh_cmd_network(tdsh_session_t *session, int argc, char **argv);
int tdsh_cmd_ifconfig(tdsh_session_t *session, int argc, char **argv);
esp_err_t tdsh_wifi_init(void);
esp_err_t tdsh_wifi_stop(void);
esp_err_t tdsh_wifi_autoconnect(bool verbose);
void *tdsh_wifi_netif(void);
int tdsh_cmd_networks(tdsh_session_t *session, int argc, char **argv);
int tdsh_cmd_wifiscan(tdsh_session_t *session, int argc, char **argv);
int tdsh_cmd_wificonnect(tdsh_session_t *session, int argc, char **argv);
int tdsh_cmd_wifidisconnect(tdsh_session_t *session, int argc, char **argv);
int tdsh_cmd_wifiap(tdsh_session_t *session, int argc, char **argv);
/* The access point's mode applied, every second by the network task. */
void tdsh_wifi_ap_policy(bool online, bool wifi_allowed);
/* Make the network task apply its policy at once. */
void tdsh_network_kick(void);
/* Clients can reach the board: a network, or its access point. Servers
 * (SSH, FTP) need this; time sync and the like need tdsh_network_is_online. */
bool tdsh_network_is_reachable(void);
bool tdsh_wifi_ap_is_up(void);
int tdsh_cmd_wifiadd(tdsh_session_t *session, int argc, char **argv);
int tdsh_cmd_wifiremove(tdsh_session_t *session, int argc, char **argv);
esp_err_t tdsh_eth_start(void);
esp_err_t tdsh_eth_stop(void);
void *tdsh_eth_netif(void);
int tdsh_cmd_lan(tdsh_session_t *session, int argc, char **argv);
esp_err_t tdsh_netmount_init(void);
int tdsh_cmd_netmount(tdsh_session_t *session, int argc, char **argv);
bool tdsh_netmount_translate_logical(const char *logical, char *real_out, size_t real_out_size);
/* Mounts the SD card at boot when the board key sd.automount is 1. */
esp_err_t tdsh_sdcard_init(void);
bool tdsh_sdcard_translate_logical(const char *logical, char *real_out, size_t real_out_size);
int tdsh_cmd_sd(tdsh_session_t *session, int argc, char **argv);
/* Starts SNTP unless automatic time is off (tdsh_time_auto()). */
void tdsh_time_sync_start(void);
int tdsh_cmd_tz(tdsh_session_t *session, int argc, char **argv);
int tdsh_cmd_date(tdsh_session_t *session, int argc, char **argv);
int tdsh_cmd_cal(tdsh_session_t *session, int argc, char **argv);
int tdsh_cmd_ping(tdsh_session_t *session, int argc, char **argv);
int tdsh_cmd_ftp(tdsh_session_t *session, int argc, char **argv);
int tdsh_cmd_ssh(tdsh_session_t *session, int argc, char **argv);
int tdsh_cmd_write(tdsh_session_t *session, int argc, char **argv);
int tdsh_cmd_nano(tdsh_session_t *session, int argc, char **argv);
int tdsh_cmd_hwtest(tdsh_session_t *session, int argc, char **argv);
/* The SSH client's terminal width from its pty request, 0 if none. */
int tdsh_ssh_terminal_columns(void);
/* Ctrl+C typed in the SSH session of the calling task (false in any other
 * task); input before it is dropped, input after it stays. */
bool tdsh_ssh_break_requested(void);

#ifdef __cplusplus
}
#endif

#endif /* TDSH_ESPIDF_INTERNAL_H */

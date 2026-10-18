# SDK API and commands

This inventory is generated from the delivered headers and command descriptors.

## include/tdsh.h

```c
int tdsh_core_init(const tdsh_core_config_t *config);
void tdsh_core_reset(void);
const tdsh_core_config_t *tdsh_core_config(void);
const char *tdsh_platform_name(void);
int tdsh_session_init(tdsh_session_t *session,
                        const char *username,
                        bool interactive);
int tdsh_session_clone(tdsh_session_t *dst,
                         const tdsh_session_t *src,
                         bool interactive);
int tdsh_register_command(const tdsh_command_t *command);
int tdsh_register_commands(const tdsh_command_t *commands, size_t count);
const tdsh_command_t *tdsh_commands_get(size_t *count);
const tdsh_command_t *tdsh_command_find(const char *name);
int tdsh_execute_argv(tdsh_session_t *session, int argc, char **argv);
int tdsh_execute_line(tdsh_session_t *session, const char *line);
int tdsh_register_core_builtins(void);
const char *tdsh_var_get(tdsh_session_t *session, const char *name);
int tdsh_var_set(tdsh_session_t *session, const char *name, const char *value);
int tdsh_var_unset(tdsh_session_t *session, const char *name);
int tdsh_path_normalize(tdsh_session_t *session,
                          const char *input,
                          char *logical_out,
                          size_t logical_out_size);
int tdsh_path_to_real(tdsh_session_t *session,
                        const char *input,
                        char *real_out,
                        size_t real_out_size,
                        char *logical_out,
                        size_t logical_out_size);
int tdsh_parse_words(tdsh_session_t *session,
                       const char *input,
                       char *storage,
                       size_t storage_size,
                       char **argv,
                       int *argc_out);
int tdsh_eval_int_expr(tdsh_session_t *session,
                         const char *expr,
                         int64_t *value_out);
int tdsh_run_script(tdsh_session_t *session,
                      const char *path,
                      bool background);
int tdsh_run_script_in_session(tdsh_session_t *session,
                                 const char *path);
bool tdsh_script_special_var(tdsh_session_t *session,
                               const char *name,
                               char *out,
                               size_t out_size);
bool tdsh_script_try_function(tdsh_session_t *session,
                                int argc,
                                char **argv,
                                int *status_out);
uint64_t tdsh_monotonic_ms(void);
void tdsh_sleep_ms(uint32_t ms);
void tdsh_yield(void);
int tdsh_random_bytes(void *buffer, size_t length);
void *tdsh_malloc(size_t size);
void *tdsh_calloc(size_t count, size_t size);
void *tdsh_realloc(void *ptr, size_t size);
void tdsh_free(void *ptr);
char *tdsh_strdup(const char *text);
void tdsh_memory_get_stats(tdsh_memory_stats_t *stats);
```

## include/tdsh_platform.h

```c
#define TDSH_MEM_8        (1u << 0)
#define TDSH_MEM_16       (1u << 1)
#define TDSH_MEM_32       (1u << 2)
#define TDSH_MEM_READONLY (1u << 3)

typedef struct
{
    const char *name;
    uintptr_t start;
    size_t size;
    uint32_t flags;
} tdsh_mem_region_t;

/* tdsh_platform_api_t: name, context, monotonic_ms, sleep_ms, yield,
 * random_bytes, malloc_fn, calloc_fn, realloc_fn, free_fn, worker_run and
 * the optional memory regions for peek and poke: */
const tdsh_mem_region_t *(*mem_regions)(void *context, size_t *count);
```

## include/tdsh_terminal.h

```c
typedef struct
{
    void *context;
    int (*read_byte)(void *context, uint8_t *byte_out);
    int (*write_bytes)(void *context, const void *data, size_t length);
    int (*columns)(void *context);                 /* optional: width, <= 0 unknown */
    int (*read_byte_timeout)(void *context, uint8_t *byte_out,
                             unsigned timeout_ms);  /* optional: 0, -ETIMEDOUT, or cannot wait */
} tdsh_terminal_io_t;

int tdsh_terminal_readline(tdsh_session_t *session,
                             const tdsh_terminal_io_t *io,
                             const char *prompt,
                             char *buffer,
                             size_t capacity);
```

## ports/esp_idf/components/tdsh/include/tdsh_espidf.h

```c
esp_err_t tdsh_espidf_init(const tdsh_espidf_config_t *config);
esp_err_t tdsh_espidf_start(void);
const tdsh_platform_api_t *tdsh_espidf_platform(void);
int tdsh_espidf_register_commands(const tdsh_espidf_config_t *config);
esp_err_t tdsh_init(const tdsh_config_t *config);
esp_err_t tdsh_start(void);
int tdsh_console_readline(const char *prompt, char *buf, size_t capacity, bool echo_input);
int tdsh_interactive_readline(tdsh_session_t *session, const char *prompt, char *buf, size_t capacity);
bool tdsh_is_local_console_task(void);
void tdsh_espidf_set_console_columns(int (*columns)(void));
int tdsh_ssh_terminal_columns(void);
int tdsh_session_set_user(tdsh_session_t *session, const char *username);
int tdsh_run_user_startup(tdsh_session_t *session);
esp_err_t tdsh_fs_init(bool format_if_mount_failed);
void tdsh_fs_print_info(void);
esp_err_t tdsh_users_init(void);
bool tdsh_user_exists(const char *username);
bool tdsh_user_authenticate(const char *username, const char *password);
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
esp_err_t tdsh_eth_start(void);
esp_err_t tdsh_eth_stop(void);
bool tdsh_eth_is_connected(void);
void *tdsh_eth_netif(void);
int tdsh_eth_get_info(tdsh_eth_info_t *info);
int tdsh_cmd_lan(tdsh_session_t *session, int argc, char **argv);
esp_err_t tdsh_netmount_init(void);
int tdsh_cmd_netmount(tdsh_session_t *session, int argc, char **argv);
bool tdsh_netmount_translate_logical(const char *logical, char *real_out, size_t real_out_size);
void tdsh_netmount_remove_owner(const char *owner);
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
int tdsh_cmd_sd(tdsh_session_t *session, int argc, char **argv);
```

## Registered commands

| Command | Usage | Description |
| --- | --- | --- |
| help | help [command] | Show commands or command help |
| sleep | sleep <seconds> | Sleep for a floating-point number of seconds |
| pwd | pwd | Print current working directory |
| cd | cd [directory] | Change directory |
| cp | cp <source ...> <destination> | Copy files or directory trees |
| head | head <file ...> [-l lines] | Print first lines of files |
| cat | cat <file ...> | Print entire files |
| touch | touch <file ...> | Create files if they do not exist |
| mv | mv <source ...> <destination> | Move or rename files/directories |
| rm | rm [-r] [-y] <path ...> | Remove files or directory trees |
| mkdir | mkdir [-p] <directory ...> | Create directories |
| clear | clear | Clear the terminal |
| ls | ls [-a] [-l] [path ...] | List directory contents |
| echo | echo [text ...] | Print text (generic shell redirection is supported) |
| test | test EXPRESSION | Evaluate file, string or integer conditions |
| [ | [ EXPRESSION ] | Bracket form of test |
| tdsh | tdsh run <file.ush\|directory> [--bg] | Run native .ush shell scripts |
| whoami | whoami | Print current user |
| platform | platform | Show active TinyDesk Shell platform port |
| free | free | Show TinyDesk Shell core allocation statistics |
| uptime | uptime | Show monotonic platform uptime |
| set | set | Show shell variables |
| unset | unset <name ...> | Remove shell variables |
| version | version | Show TinyDesk Shell version |
| peek | peek -l \| peek [-w 8\|16\|32] <address> [count] | Read memory the port allows (root; only on ports with `mem_regions`: the ESP32 and ESP32-C6 firmware) |
| poke | poke [-w 8\|16\|32] <address> <value> | Write memory the port allows (root; only on ports with `mem_regions`; on the ESP32 and ESP32-C6 the GPIO output registers) |
| users | users | List TinyDesk Shell users |
| useradd | useradd <username> | Create a user |
| userdel | userdel <username> [-f] | Delete a user |
| login | login <username> | Login as another user |
| logout | logout | Logout current session |
| bootuser | bootuser [username] | Show/set physical-console boot user |
| rootrecover | rootrecover | Reset root password from physical USB console |
| tz | tz [[+\|-]HH:MM] | Show/set user timezone offset |
| date | date | Show date/time using user timezone |
| cal | cal | Print current month calendar |
| passwd | passwd | Change current user's password |
| idfinfo | idfinfo | Show ESP-IDF/chip information |
| heap | heap | Show ESP-IDF heap and TinyDesk Shell tracked allocations |
| reboot | reboot | Restart the MCU |
| networks | networks | List saved Wi-Fi networks |
| wifiscan | wifiscan | Scan and list available Wi-Fi networks |
| wificonnect | wificonnect [saved_ssid] | Connect to a saved network |
| wifidisconnect | wifidisconnect | Disconnect station Wi-Fi |
| wifiadd | wifiadd <ssid> [password] | Save a Wi-Fi network in NVS |
| wifiremove | wifiremove <ssid ...> | Remove saved Wi-Fi networks |
| lan | lan <status\|config\|enable\|disable\|dhcp\|static\|dns\|hw\|poll> ... | Configure W6100 Ethernet |
| network | network [status] \| network mode [auto\|lan\|wifi\|both] \| network autowifi [on\|off] | Configure network policy (changing it: root) |
| netmount | netmount <list\|add\|connect\|disconnect\|status\|remove> ... | Map SMB2/SMB3 shares |
| ifconfig | ifconfig | Show network interfaces and default route |
| ping | ping [-c count] <host/address ...> | Send ICMP echo requests (4 per host unless -c) |
| ftp | ftp <start\|stop\|restart\|status> [port] | Control FTP server |
| ssh | ssh <start\|stop\|restart\|status> [port] | Control SSH/SFTP server |
| write | write <file> [text ...] | Line editor or direct file writer |
| nano | nano <file> | Full-screen VT100 nano-style editor |
| gpio | gpio <init\|get\|set> ... | Configure and control GPIO |
| hwtest | hwtest <status\|sd\|uart\|rs485\|all> [count] | Board SD/UART/RS485 hardware tests |
| sd | sd [status] \| sd mount \| sd umount \| sd format --yes | SD card at /sd (FAT) |

`board` is the reference application command. All optional ESP command groups
are enabled by the standalone application configuration.

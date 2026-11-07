#include "tdsh_espidf.h"
#include "tdsh_terminal.h"
#include "tdsh_board.h"
#include "tdsh_console_access.h"

#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <unistd.h>

#include "esp_log.h"
#include "sdkconfig.h"
#include "driver/usb_serial_jtag.h"
#include "driver/usb_serial_jtag_vfs.h"
#include "driver/uart.h"
#include "driver/uart_vfs.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define C_RESET "\033[0m"
#define C_GREEN "\033[1;32m"
#define C_BLUE  "\033[1;34m"

static const char *TAG = "tdsh";
static tdsh_espidf_config_t s_config;
static tdsh_session_t s_session;
/* UI and console tasks exchange a published identity, never a half-written
 * session. No provider/NVS calls occur while this short spinlock is held. */
static portMUX_TYPE s_user_mux = portMUX_INITIALIZER_UNLOCKED;
static char s_published_user[TDSH_USERNAME_MAX];
static uint32_t s_published_generation;
static bool s_user_switching = true;
static bool s_initialized;
static bool s_started;
static TaskHandle_t s_local_shell_task = NULL;
static tdsh_console_access_t s_console_access = TDSH_ACCESS_LOCAL;

/*
 * Wi-Fi scan/connect/SNTP calls are intentionally executed in the shell task.
 * 12 KiB was sufficient for normal shell commands, but ESP-IDF Wi-Fi plus
 * SNTP can transiently use substantially more stack.  A shell stack overflow
 * corrupts the adjacent FreeRTOS heap and is later reported by TLSF when SSH
 * performs its first heap walk/allocation.  Keep a generous internal-RAM
 * stack for the physical USB Serial/JTAG shell.
 */
#define TDSH_LOCAL_SHELL_STACK_BYTES TDSH_SHELL_TASK_STACK

/*
 * The ESP32-C6 local shell uses the built-in USB Serial/JTAG controller as
 * the primary ESP-IDF console. The default USB console VFS has non-blocking
 * reads, which is unsuitable for an interactive shell because fgetc(stdin)
 * can otherwise return EOF whenever the RX FIFO is temporarily empty.
 *
 * Install the interrupt-driven USB Serial/JTAG driver and tell the VFS to use
 * it. With the driver-backed VFS, stdin reads block until data is available,
 * while stdout/stderr continue to use the normal ESP-IDF console streams.
 *
 * No UART peripheral, UART pins, baud rate, or UART driver is used by the
 * local shell.
 */

static bool s_local_swallow_lf_after_cr = false;
static bool s_remote_swallow_lf_after_cr = false;
static int tdsh_task_read_char(unsigned char *out);
/* Keys the local console read while checking for Ctrl+C during a command
 * (tdsh_break_requested); they come first in tdsh_task_read_char. */
static uint8_t s_ahead[64];
static size_t s_ahead_len;

static esp_err_t tdsh_console_transport_init(void)
{
#if CONFIG_ESP_CONSOLE_USB_SERIAL_JTAG
    usb_serial_jtag_driver_config_t usb_cfg = USB_SERIAL_JTAG_DRIVER_CONFIG_DEFAULT();
    usb_cfg.rx_buffer_size = 1024;
    usb_cfg.tx_buffer_size = 1024;

    esp_err_t err = usb_serial_jtag_driver_install(&usb_cfg);
    if (err != ESP_OK && err != ESP_ERR_INVALID_STATE)
    {
        ESP_LOGE(TAG, "usb_serial_jtag_driver_install failed: %s", esp_err_to_name(err));
        return err;
    }

    /* Switch stdin/stdout/stderr from the simple polling VFS to the
     * interrupt-driven USB Serial/JTAG driver. Reads then block as required
     * by the interactive shell. */
    usb_serial_jtag_vfs_use_driver();

    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    ESP_LOGI(TAG, "USB Serial/JTAG console enabled (blocking driver-backed stdin)");
    return ESP_OK;
#elif CONFIG_ESP_CONSOLE_UART
    /* A UART console (chips without USB Serial/JTAG, e.g. the classic ESP32,
     * usually through the board's USB-UART chip). Same idea: an interrupt-
     * driven driver behind stdin so that reads block. */
    const uart_port_t port = (uart_port_t)CONFIG_ESP_CONSOLE_UART_NUM;
    esp_err_t err = uart_driver_install(port, 1024, 1024, 0, NULL, 0);
    if (err != ESP_OK && err != ESP_ERR_INVALID_STATE)
    {
        ESP_LOGE(TAG, "uart_driver_install failed: %s", esp_err_to_name(err));
        return err;
    }
    uart_vfs_dev_use_driver(port);

    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    ESP_LOGI(TAG, "UART%d console enabled (blocking driver-backed stdin)", (int)port);
    return ESP_OK;
#else
    ESP_LOGE(TAG, "tdsh needs a console: CONFIG_ESP_CONSOLE_USB_SERIAL_JTAG or CONFIG_ESP_CONSOLE_UART");
    return ESP_ERR_NOT_SUPPORTED;
#endif
}

static void print_banner(void)
{
    /* Clearing the screen is harmless, but no cursor-position query is sent. */
    printf("\033[2J\033[H");
    printf("==========================================\r\n");
    printf("          WELCOME TO TINYDESK SHELL       \r\n");
    printf("              Version %-18s\r\n", TDSH_VERSION);
    printf("               ESP-IDF port                \r\n");
    printf("==========================================\r\n\r\n");
    printf("Type 'help' to list commands.\r\n\r\n");
    fflush(stdout);
}

static void build_prompt(tdsh_session_t *session, char *out, size_t out_size)
{
    char display_path[TDSH_MAX_PATH];
    if (strcmp(session->cwd, session->home) == 0)
    {
        snprintf(display_path, sizeof(display_path), "~");
    }
    else if (strncmp(session->cwd, session->home, strlen(session->home)) == 0 &&
             session->cwd[strlen(session->home)] == '/')
    {
        snprintf(display_path, sizeof(display_path), "~%s", session->cwd + strlen(session->home));
    }
    else
    {
        snprintf(display_path, sizeof(display_path), "%s", session->cwd);
    }

    const char marker = strcmp(session->username, "root") == 0 ? '#' : '$';
    snprintf(out, out_size, C_GREEN "%s@%s" C_RESET ":" C_BLUE "%s" C_RESET "%c ",
             session->username, session->hostname, display_path, marker);
}

static bool *transport_swallow_flag(void)
{
    return tdsh_is_local_console_task() ? &s_local_swallow_lf_after_cr
                                        : &s_remote_swallow_lf_after_cr;
}

/* CR LF and CR count as one Enter: true if `byte` is the LF to drop. Keeps
 * the state shared with password/login input on the same transport. */
static bool swallow_lf(uint8_t byte)
{
    bool *swallow = transport_swallow_flag();
    if (*swallow)
    {
        *swallow = false;
        if (byte == '\n')
            return true;
    }
    if (byte == '\r')
        *swallow = true;
    return false;
}

static int terminal_read_byte(void *context, uint8_t *out)
{
    (void)context;
    for (;;)
    {
        if (tdsh_task_read_char(out) != 0)
            return -EIO;
        if (!swallow_lf(*out))
            return 0;
    }
}

static int (*s_console_columns)(void);

void tdsh_espidf_set_console_columns(int (*columns)(void))
{
    s_console_columns = columns;
}

static int terminal_columns(void *context)
{
    (void)context;
    if (!tdsh_is_local_console_task())
        return tdsh_ssh_terminal_columns();
    return s_console_columns ? s_console_columns() : 0;
}

/* A byte from the local serial console within timeout_ms, so the line
 * editor can ask the terminal for its width. SSH and a front end's own
 * stream (fileno() < 0) cannot wait and say so. */
static int terminal_read_byte_timeout(void *context, uint8_t *out, unsigned timeout_ms)
{
    (void)context;
    if (!tdsh_is_local_console_task() || fileno(stdin) < 0)
        return -ENOTSUP;
    for (;;)
    {
        if (s_ahead_len)
        {
            (void)tdsh_task_read_char(out);
            if (!swallow_lf(*out))
                return 0;
            continue;
        }
#if CONFIG_ESP_CONSOLE_USB_SERIAL_JTAG
        /* The USB Serial/JTAG VFS has no select(); stdin is unbuffered and
         * reads from the same driver, so read the driver with a timeout. */
        if (usb_serial_jtag_read_bytes(out, 1, pdMS_TO_TICKS(timeout_ms)) <= 0)
            return -ETIMEDOUT;
#else
        int fd = fileno(stdin);
        fd_set readable;
        FD_ZERO(&readable);
        FD_SET(fd, &readable);
        struct timeval tv = {
            .tv_sec = (time_t)(timeout_ms / 1000U),
            .tv_usec = (suseconds_t)((timeout_ms % 1000U) * 1000U),
        };
        int n = select(fd + 1, &readable, NULL, NULL, &tv);
        if (n == 0)
            return -ETIMEDOUT;
        if (n < 0)
            return -ENOTSUP;
        if (tdsh_task_read_char(out) != 0)
            return -EIO;
#endif
        if (!swallow_lf(*out))
            return 0;
    }
}

static int terminal_write_bytes(void *context, const void *data, size_t length)
{
    (void)context;
    if (fwrite(data, 1, length, stdout) != length)
        return -EIO;
    return fflush(stdout) == 0 ? 0 : -EIO;
}

int tdsh_interactive_readline(tdsh_session_t *session, const char *prompt,
                              char *buf, size_t capacity)
{
    const tdsh_terminal_io_t io = {
        .context = NULL,
        .read_byte = terminal_read_byte,
        .write_bytes = terminal_write_bytes,
        .columns = terminal_columns,
        .read_byte_timeout = terminal_read_byte_timeout,
    };
    return tdsh_terminal_readline(session, &io, prompt, buf, capacity);
}

bool tdsh_is_local_console_task(void)
{
    return s_local_shell_task != NULL && xTaskGetCurrentTaskHandle() == s_local_shell_task;
}

bool tdsh_is_physical_console(void)
{
    return tdsh_is_local_console_task() && tdsh_access_is_physical(&s_console_access);
}

bool tdsh_console_begin_recovery(void)
{
    return tdsh_is_local_console_task() && tdsh_access_begin_recovery(&s_console_access);
}

void tdsh_console_end_recovery(void)
{
    tdsh_access_end_recovery(&s_console_access);
}

bool tdsh_console_mark_remote(void)
{
    return tdsh_access_mark_remote(&s_console_access);
}

/* One key waiting on the local serial console, without blocking: 1 read, 0
 * none. Only for the console's own driver (not a front end's stream). */
static int local_poll_byte(uint8_t *out)
{
#if CONFIG_ESP_CONSOLE_USB_SERIAL_JTAG
    return usb_serial_jtag_read_bytes(out, 1, 0) > 0 ? 1 : 0;
#else
    int fd = fileno(stdin);
    fd_set readable;
    FD_ZERO(&readable);
    FD_SET(fd, &readable);
    struct timeval tv = {0};
    if (select(fd + 1, &readable, NULL, NULL, &tv) <= 0)
        return 0;
    int c = fgetc(stdin);
    if (c == EOF)
    {
        clearerr(stdin);
        return 0;
    }
    *out = (uint8_t)c;
    return 1;
#endif
}

bool tdsh_break_requested(void)
{
    if (!tdsh_is_local_console_task())
        return tdsh_ssh_break_requested();
    if (fileno(stdin) < 0)
        return false;   /* a front end's stream: it checks for itself */
    bool brk = false;
    uint8_t b;
    while (local_poll_byte(&b))
    {
        if (b == 0x03)
        {
            brk = true;
            s_ahead_len = 0;   /* like a terminal: drop the keys typed before it */
        }
        else if (s_ahead_len < sizeof(s_ahead))
        {
            s_ahead[s_ahead_len++] = b;
        }
    }
    return brk;
}

int tdsh_getchar(void)
{
    unsigned char c;
    return tdsh_task_read_char(&c) == 0 ? c : EOF;
}

static int tdsh_task_read_char(unsigned char *out)
{
    if (!out)
        return -1;
    if (s_ahead_len && tdsh_is_local_console_task())
    {
        *out = s_ahead[0];
        memmove(s_ahead, s_ahead + 1, --s_ahead_len);
        return 0;
    }

    /* stdin is transport-local: USB Serial/JTAG for the local shell and the
     * encrypted stream for SSH sessions. The local USB VFS was switched to
     * its blocking driver in tdsh_console_transport_init(). */
    int c = fgetc(stdin);
    if (c == EOF)
    {
        clearerr(stdin);
        return -1;
    }
    *out = (unsigned char)c;
    return 0;
}

int tdsh_console_readline(const char *prompt, char *buf, size_t capacity, bool echo_input)
{
    bool *swallow_lf_after_cr = transport_swallow_flag();
    size_t len = 0;
    int esc_state = 0;

    if (!buf || capacity < 2)
        return -1;
    buf[0] = '\0';
    if (prompt)
    {
        printf("%s", prompt);
        fflush(stdout);
    }

    for (;;)
    {
        unsigned char ch = 0;
        if (tdsh_task_read_char(&ch) != 0)
        {
            buf[0] = '\0';
            return -1;
        }

        if (*swallow_lf_after_cr)
        {
            *swallow_lf_after_cr = false;
            if (ch == '\n')
                continue;
        }

        if (esc_state == 1)
        {
            if (ch == '[')
                esc_state = 2;
            else
                esc_state = 0;
            continue;
        }
        if (esc_state == 2)
        {
            if (ch >= 0x40 && ch <= 0x7E)
                esc_state = 0;
            continue;
        }
        if (ch == 0x1B)
        {
            esc_state = 1;
            continue;
        }

        if (ch == '\r' || ch == '\n')
        {
            if (ch == '\r')
                *swallow_lf_after_cr = true;
            buf[len] = '\0';
            printf("\r\n");
            fflush(stdout);
            return (int)len;
        }

        if (ch == 0x03)
        { /* Ctrl+C */
            buf[0] = '\0';
            printf("^C\r\n");
            fflush(stdout);
            return 0;
        }

        if (ch == 0x08 || ch == 0x7F)
        {
            if (len > 0)
            {
                --len;
                buf[len] = '\0';
                if (echo_input)
                {
                    printf("\b \b");
                    fflush(stdout);
                }
            }
            continue;
        }

        if (ch < 0x20)
            continue;
        if (len + 1 >= capacity)
        {
            putchar('\a');
            fflush(stdout);
            continue;
        }

        buf[len++] = (char)ch;
        buf[len] = '\0';
        if (echo_input)
        {
            putchar((char)ch);
            fflush(stdout);
        }
    }
}

static void (*s_console_flush)(void);
void tdsh_espidf_set_console_flush(void (*flush)(void))
{
    s_console_flush = flush;
}
int tdsh_session_set_user_generation(tdsh_session_t *session, const char *username, uint32_t generation)
{
    if (!session || !username || username[0] == '\0')
        return -EINVAL;
    if (strlen(username) >= sizeof(session->username))
        return -ENAMETOOLONG;
    uint32_t current = tdsh_user_generation(username);
    if (!current || (generation && generation != current))
        return -EACCES;
    if (session == &s_session)
    {
        taskENTER_CRITICAL(&s_user_mux);
        s_user_switching = true;
        taskEXIT_CRITICAL(&s_user_mux);
        session->logout_requested = true;
        if (s_console_flush)
            s_console_flush();
    }

    snprintf(session->username, sizeof(session->username), "%s", username);
    session->user_generation = generation ? generation : current;
    memset(session->vars, 0, sizeof(session->vars));
    if (strcmp(username, "root") == 0)
    {
        snprintf(session->home, sizeof(session->home), "/root");
    }
    else
    {
        snprintf(session->home, sizeof(session->home), "/home/%s", username);
    }
    snprintf(session->cwd, sizeof(session->cwd), "%s", session->home);

    char real_home[TDSH_MAX_PATH + sizeof(TDSH_MOUNT_POINT) + 8];
    snprintf(real_home, sizeof(real_home), "%s%s", TDSH_MOUNT_POINT, session->home);
    if (mkdir(real_home, 0755) != 0 && errno != EEXIST)
    {
        return -errno;
    }

    session->logout_requested = false;
    if (session == &s_session)
    {
        taskENTER_CRITICAL(&s_user_mux);
        memcpy(s_published_user, session->username, sizeof(s_published_user));
        s_published_generation = session->user_generation;
        s_user_switching = false;
        taskEXIT_CRITICAL(&s_user_mux);
    }
    return 0;
}
int tdsh_session_set_user(tdsh_session_t *session, const char *username)
{
    return tdsh_session_set_user_generation(session, username, 0);
}


int tdsh_run_user_startup(tdsh_session_t *session)
{
    if (!session || !session->interactive || !tdsh_is_local_console_task())
        return 0;

    char real[TDSH_MAX_REAL_PATH];
    if (tdsh_path_to_real(session, "~/" TDSH_STARTUP_FILE, real, sizeof(real), NULL, 0) != 0)
    {
        return 1;
    }
    struct stat st;
    if (stat(real, &st) != 0)
    {
        FILE *f = fopen(real, "w");
        if (!f)
            return 1;
        fprintf(f, "#!/bin/tdsh\n");
        fprintf(f, "# TinyDesk Shell per-user startup script (uScript %s)\n", USCRIPT_VERSION);
        fprintf(f, "# Runs when the local shell starts (the console, or the desktop's Terminal).\n");
        fclose(f);
        return 0;
    }
    if (!S_ISREG(st.st_mode))
        return 1;
    return tdsh_run_script_in_session(session, "~/" TDSH_STARTUP_FILE);
}

/* the host (the desktop) may switch the console's user,
 * e.g. when someone logs in to the desktop over Telnet. The switch happens
 * when the console next waits for input; the host wakes it with Ctrl+C. */
static char s_switch_user[TDSH_USERNAME_MAX];
static bool s_switch_pending;

void tdsh_espidf_console_set_user(const char *username)
{
    char target[TDSH_USERNAME_MAX] = {0};
    snprintf(target, sizeof(target), "%s", username ? username : "");
    taskENTER_CRITICAL(&s_user_mux);
    s_user_switching = true;
    memcpy(s_switch_user, target, sizeof(s_switch_user));
    s_switch_pending = true;
    taskEXIT_CRITICAL(&s_user_mux);
}

const char *tdsh_espidf_console_user(void)
{
    static char user[TDSH_USERNAME_MAX];
    uint32_t generation;
    taskENTER_CRITICAL(&s_user_mux);
    bool blocked = s_user_switching || s_switch_pending;
    if (blocked)
        user[0] = 0;
    else
        memcpy(user, s_published_user, sizeof(user));
    generation = s_published_generation;
    taskEXIT_CRITICAL(&s_user_mux);
    if (!user[0] || !generation || tdsh_user_generation(user) != generation)
        user[0] = 0;
    return user;
}

/* Apply a pending switch. Returns true if the user changed. */
static bool apply_user_switch(void)
{
    char target[TDSH_USERNAME_MAX];
    taskENTER_CRITICAL(&s_user_mux);
    bool pending = s_switch_pending;
    memcpy(target, s_switch_user, sizeof(target));
    s_switch_pending = false;
    taskEXIT_CRITICAL(&s_user_mux);
    if (!pending)
        return false;
    if (!target[0])
    {
        s_session.logout_requested = true;
        if (s_console_flush)
            s_console_flush();
        return false;
    }
    if (!tdsh_user_exists(target) || tdsh_session_set_user(&s_session, target) != 0)
        return false;
    printf("\033[2J\033[HSession for %s.\r\n\r\n", s_session.username);
    return true;
}

static void local_login_loop(void)
{
    taskENTER_CRITICAL(&s_user_mux);
    s_user_switching = true;
    taskEXIT_CRITICAL(&s_user_mux);
    for (;;)
    {
        if (apply_user_switch())
            return;
        char user[TDSH_USERNAME_MAX];
        char pass[129];

        int n = tdsh_console_readline("login: ", user, sizeof(user), true);
        if (n <= 0)
        {
            continue;
        }
        if (!tdsh_user_exists(user))
        {
            printf("Login incorrect.\n");
            continue;
        }

        n = tdsh_console_readline("Password: ", pass, sizeof(pass), false);
        uint32_t generation = n > 0 ? tdsh_user_login(user, pass) : 0;
        if (!generation)
        {
            memset(pass, 0, sizeof(pass));
            printf("Login incorrect.\n");
            continue;
        }

        memset(pass, 0, sizeof(pass));
        if (tdsh_session_set_user_generation(&s_session, user, generation) != 0)
        {
            printf("tdsh: unable to start user session\n");
            continue;
        }

        printf("Login successful.\n");
        (void)tdsh_run_user_startup(&s_session);
        return;
    }
}

/* The interactive loop of the physical console. Runs in the calling task and
 * uses whatever stdin/stdout that task has. */
static void local_console_loop(void)
{
    s_local_shell_task = xTaskGetCurrentTaskHandle();

    setvbuf(stdout, NULL, _IONBF, 0);

    ESP_LOGI(TAG, "Interactive VT100 editor enabled (TAB/history/cursor keys, no DSR polling)");
    print_banner();
    (void)tdsh_run_user_startup(&s_session);
    if (s_session.logout_requested)
        local_login_loop();

    for (;;)
    {
        char prompt[TDSH_MAX_PATH + 96];
        char line[TDSH_MAX_LINE + 1];
        if (s_session.logout_requested || !tdsh_session_valid(&s_session))
            local_login_loop();
        (void)apply_user_switch();
        if (s_session.logout_requested)
            continue;
        build_prompt(&s_session, prompt, sizeof(prompt));

        int n = tdsh_interactive_readline(&s_session, prompt, line, sizeof(line));
        if (n < 0)
        {
            /* A local console read failure must never turn into a tight prompt loop. */
            ESP_LOGE(TAG, "USB Serial/JTAG console readline failed; retrying after delay");
            vTaskDelay(pdMS_TO_TICKS(500));
            continue;
        }
        if (n > 0)
        {
            (void)tdsh_execute_line(&s_session, line);
            if (s_session.logout_requested)
                local_login_loop();

            UBaseType_t stack_free = uxTaskGetStackHighWaterMark(NULL);
            if (stack_free < 4096U)
            {
                ESP_LOGW(TAG, "local USB shell low stack: minimum free=%u bytes",
                         (unsigned)stack_free);
            }
            else
            {
                ESP_LOGD(TAG, "local USB shell minimum free stack=%u bytes",
                         (unsigned)stack_free);
            }
        }
    }
}

static void shell_task(void *arg)
{
    (void)arg;
    /* Let app_main return first so its informational log does not split the
     * first shell prompt. */
    vTaskDelay(pdMS_TO_TICKS(50));
    local_console_loop();
}

/* run the physical console in the calling task, on the
 * stdin/stdout it already has (for example streams connected to a window).
 * Call after tdsh_espidf_init(); never returns. */
void tdsh_espidf_run_console(void)
{
    local_console_loop();
}


static bool espidf_translate_path(void *context,
                                  const char *logical,
                                  char *real_out,
                                  size_t real_out_size)
{
    (void)context;
    return tdsh_netmount_translate_logical(logical, real_out, real_out_size) ||
           tdsh_sdcard_translate_logical(logical, real_out, real_out_size);
}

esp_err_t tdsh_espidf_init(const tdsh_espidf_config_t *config)
{
    if (s_initialized)
        return ESP_OK;
    if (!config || !config->hostname || !config->default_user)
        return ESP_ERR_INVALID_ARG;

    s_config = *config;
    if (s_config.history_length == 0)
        s_config.history_length = 50;

    tdsh_core_config_t core = TDSH_CORE_CONFIG_DEFAULT();
    core.hostname = config->hostname;
    core.default_user = config->default_user;
    core.fs_root = TDSH_MOUNT_POINT;
    core.history_length = config->history_length;
    core.platform = tdsh_espidf_platform();
    core.path_translate = espidf_translate_path;
    core.user_role = tdsh_user_role;
    core.user_generation = tdsh_user_generation;
    core.user_rights = tdsh_user_rights;

    int core_rc = tdsh_core_init(&core);
    if (core_rc != 0)
    {
        ESP_LOGE(TAG, "portable core init failed: %d", core_rc);
        return ESP_FAIL;
    }
    if (config->register_core_builtins)
    {
        core_rc = tdsh_register_core_builtins();
        if (core_rc != 0)
        {
            ESP_LOGE(TAG, "core command registration failed: %d", core_rc);
            return ESP_FAIL;
        }
    }
    core_rc = tdsh_espidf_register_commands(config);
    if (core_rc != 0)
    {
        ESP_LOGE(TAG, "ESP-IDF command registration failed: %d", core_rc);
        return ESP_FAIL;
    }

    esp_err_t fs_err = tdsh_fs_init(s_config.format_fs_if_mount_failed);
    if (fs_err != ESP_OK)
    {
        ESP_LOGE(TAG, "filesystem init failed: %s", esp_err_to_name(fs_err));
        return fs_err;
    }

    /* Board configuration (pins and other hardware settings) before any
     * module that reads it: built-in text, then /fs/etc/board.conf. */
    (void)mkdir(TDSH_MOUNT_POINT "/etc", 0755);
    int bad_line = tdsh_board_load(config->board_config, TDSH_MOUNT_POINT "/etc/board.conf");
    if (bad_line)
        ESP_LOGW(TAG, "/etc/board.conf line %d is not \"key = value\"; skipped", bad_line);
    ESP_LOGI(TAG, "board configuration: %d settings", tdsh_board_count());

    esp_err_t users_err = tdsh_users_init();
    if (users_err != ESP_OK)
    {
        ESP_LOGE(TAG, "users init failed: %s", esp_err_to_name(users_err));
        return users_err;
    }

    memset(&s_session, 0, sizeof(s_session));
    if (tdsh_session_init(&s_session, config->default_user, true) != 0)
        return ESP_FAIL;
    s_session.terminal_caps = TDSH_TERM_CAP_ANSI | TDSH_TERM_CAP_COLOR | TDSH_TERM_CAP_FULLSCREEN;

    const char *fallback_user = config->default_user;
    if (!tdsh_user_exists(fallback_user))
    {
        ESP_LOGW(TAG, "default user '%s' does not exist; using root", fallback_user);
        fallback_user = "root";
    }
    char boot_user[TDSH_USERNAME_MAX];
    if (tdsh_boot_user_get(boot_user, sizeof(boot_user)) != 0)
    {
        snprintf(boot_user, sizeof(boot_user), "%s", fallback_user);
        (void)tdsh_boot_user_default(boot_user);
    }
    if (!tdsh_user_exists(boot_user))
    {
        snprintf(boot_user, sizeof(boot_user), "root");
        (void)tdsh_boot_user_default(boot_user);
    }
    if (tdsh_session_set_user(&s_session, boot_user) != 0)
        return ESP_FAIL;
    ESP_LOGI(TAG, "local console boot user: %s", boot_user);

    if (config->init_network_manager)
    {
        esp_err_t net_err = tdsh_network_init();
        if (net_err != ESP_OK)
        {
            ESP_LOGE(TAG, "network manager init failed: %s", esp_err_to_name(net_err));
            return net_err;
        }
    }

    /* The SD card (sd.automount = 1); a missing card is not an error. */
    (void)tdsh_sdcard_init();

    s_initialized = true;
    return ESP_OK;
}

esp_err_t tdsh_espidf_start(void)
{
    if (!s_initialized)
        return ESP_ERR_INVALID_STATE;
    if (s_started)
        return ESP_OK;

    esp_err_t console_err = tdsh_console_transport_init();
    if (console_err != ESP_OK)
        return console_err;

    ESP_LOGI(TAG, "creating the console shell task with %u-byte stack",
             (unsigned)TDSH_LOCAL_SHELL_STACK_BYTES);
    BaseType_t ok = xTaskCreate(shell_task, "tdsh",
                                TDSH_LOCAL_SHELL_STACK_BYTES,
                                NULL, 5, NULL);
    if (ok != pdPASS)
        return ESP_ERR_NO_MEM;
    s_started = true;
    return ESP_OK;
}

esp_err_t tdsh_init(const tdsh_config_t *config)
{
    return tdsh_espidf_init(config);
}

esp_err_t tdsh_start(void)
{
    return tdsh_espidf_start();
}

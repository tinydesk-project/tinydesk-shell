/*
 * main.c - the standalone TinyDesk Shell firmware: the shell on the chip's
 * console (USB Serial/JTAG on the ESP32-C6, UART0 on the classic ESP32 and
 * the ESP32-S3),
 * with one example application command.
 */
#include <stdio.h>

#include "esp_err.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "sdkconfig.h"
#include "tdsh_espidf.h"

static const char *TAG = "tdsh-main";

/* The board configuration built into the firmware (board.conf of the
 * project, or its board.example.conf; see main/CMakeLists.txt).
 * /fs/etc/board.conf on the device overrides it. */
extern const char s_board_builtin[] asm("_binary_board_builtin_conf_start");

/* An application command: add your own the same way. */
static int cmd_hello(tdsh_session_t *session, int argc, char **argv)
{
    printf("Hello %s, from TinyDesk Shell on %s.\n", argc > 1 ? argv[1] : session->username, CONFIG_IDF_TARGET);
    return 0;
}

static const tdsh_command_t s_app_commands[] = {
    {
        .name = "hello",
        .usage = "hello [name]",
        .help = "Example application command",
        .fn = cmd_hello,
        .flags = 0,
    },
};

void app_main(void)
{
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES ||
        err == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK(err);

    tdsh_espidf_config_t cfg = TDSH_ESP_IDF_CONFIG_DEFAULT();
    cfg.hostname = CONFIG_IDF_TARGET;
    cfg.default_user = "root";
    cfg.board_config = s_board_builtin;

    ESP_ERROR_CHECK(tdsh_espidf_init(&cfg));
    int rc = tdsh_register_commands(s_app_commands,
                                    sizeof(s_app_commands) / sizeof(s_app_commands[0]));
    if (rc != 0)
    {
        ESP_LOGE(TAG, "application command registration failed: %d", rc);
        return;
    }
    ESP_ERROR_CHECK(tdsh_espidf_start());
}

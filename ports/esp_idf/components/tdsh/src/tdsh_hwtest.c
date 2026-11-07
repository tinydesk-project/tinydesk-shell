/*
 * Board hardware diagnostics for TinyDesk Shell.
 *
 * the pins come from the board configuration (see
 * tdsh_board.h and board.example.conf): sd.*, eth.* (the shared
 * SPI bus) and rs485.1.* / rs485.2.*. A test whose pins are not configured
 * is skipped. The TTL UART test uses the ESP32-C6's LP UART (fixed pins).
 *
 * Tests implemented:
 *   - SD card over the SPI2 bus shared with W6100
 *   - plain TTL UART using ESP32-C6 LP UART
 *   - two RS-485 channels connected to each other
 *
 * IMPORTANT:
 *   These are electrical loopback tests.  A driver successfully starting is
 *   not considered a PASS.  Transmitted data must be received and verified.
 */

#include "tdsh_espidf_internal.h"
#include "sdkconfig.h"


#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "driver/gpio.h"
#include "driver/sdspi_host.h"
#include "driver/spi_master.h"
#include "driver/uart.h"
#include "esp_err.h"
#include "esp_timer.h"
#include "esp_vfs_fat.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sdkconfig.h"
#include "sdmmc_cmd.h"
#include "tdsh_board.h"

/* Wiring, read from the board configuration when the command starts. */
typedef struct
{
    int spi_host, miso, mosi, sclk, sd_cs;   /* SD card on the SPI bus (shared with a W6100) */
    int r1_uart, r1_tx, r1_rx, r1_de;        /* RS-485 line 1: UART RS-485 mode, DE on RTS */
    int r2_uart, r2_tx, r2_rx, r2_de;        /* RS-485 line 2: DE driven by hand */
} hwtest_pins_t;

static hwtest_pins_t s_pin;

static void hwtest_load_pins(void)
{
    s_pin.spi_host = tdsh_board_int("sd.spi_host", tdsh_board_int("eth.spi_host", 1));
    s_pin.miso = tdsh_board_int("sd.miso", tdsh_board_int("eth.miso", -1));
    s_pin.mosi = tdsh_board_int("sd.mosi", tdsh_board_int("eth.mosi", -1));
    s_pin.sclk = tdsh_board_int("sd.sclk", tdsh_board_int("eth.sclk", -1));
    s_pin.sd_cs = tdsh_board_int("sd.cs", -1);
    s_pin.r1_uart = tdsh_board_int("rs485.1.uart", -1);
    s_pin.r1_tx = tdsh_board_int("rs485.1.tx", -1);
    s_pin.r1_rx = tdsh_board_int("rs485.1.rx", -1);
    s_pin.r1_de = tdsh_board_int("rs485.1.de", -1);
    s_pin.r2_uart = tdsh_board_int("rs485.2.uart", -1);
    s_pin.r2_tx = tdsh_board_int("rs485.2.tx", -1);
    s_pin.r2_rx = tdsh_board_int("rs485.2.rx", -1);
    s_pin.r2_de = tdsh_board_int("rs485.2.de", -1);
}

static bool sd_configured(void)
{
    return s_pin.miso >= 0 && s_pin.mosi >= 0 && s_pin.sclk >= 0 && s_pin.sd_cs >= 0;
}
static bool rs485_configured(void)
{
    return s_pin.r1_uart >= 0 && s_pin.r1_tx >= 0 && s_pin.r1_rx >= 0 && s_pin.r1_de >= 0 &&
           s_pin.r2_uart >= 0 && s_pin.r2_tx >= 0 && s_pin.r2_rx >= 0 && s_pin.r2_de >= 0;
}

#define HWTEST_SPI_HOST        ((spi_host_device_t)s_pin.spi_host)
#define HWTEST_SPI_MISO_GPIO   ((gpio_num_t)s_pin.miso)
#define HWTEST_SPI_MOSI_GPIO   ((gpio_num_t)s_pin.mosi)
#define HWTEST_SPI_SCLK_GPIO   ((gpio_num_t)s_pin.sclk)
#define HWTEST_SD_CS_GPIO      ((gpio_num_t)s_pin.sd_cs)
#define HWTEST_SD_MAX_FREQ_KHZ 10000
#define HWTEST_SD_MOUNT_POINT  "/sd"
#define HWTEST_SD_FILE         "/sd/HWTEST.BIN"
#define HWTEST_SD_TEST_BYTES   4096U
#define HWTEST_UART_BAUD       115200

/* ESP32-C6 LP UART: its pins are fixed (TX GPIO5, RX GPIO4). */
#define HWTEST_UART_TX_GPIO GPIO_NUM_5
#define HWTEST_UART_RX_GPIO GPIO_NUM_4

#define HWTEST_RS485_1_UART     ((uart_port_t)s_pin.r1_uart)
#define HWTEST_RS485_1_TX_GPIO  ((gpio_num_t)s_pin.r1_tx)
#define HWTEST_RS485_1_RX_GPIO  ((gpio_num_t)s_pin.r1_rx)
#define HWTEST_RS485_1_DIR_GPIO ((gpio_num_t)s_pin.r1_de)
#define HWTEST_RS485_2_UART     ((uart_port_t)s_pin.r2_uart)
#define HWTEST_RS485_2_TX_GPIO  ((gpio_num_t)s_pin.r2_tx)
#define HWTEST_RS485_2_RX_GPIO  ((gpio_num_t)s_pin.r2_rx)
#define HWTEST_RS485_2_DIR_GPIO ((gpio_num_t)s_pin.r2_de)

#define HWTEST_RS485_BAUD      9600
#define HWTEST_UART_RX_BUFFER  256
#define HWTEST_READ_TIMEOUT_MS 700
#define HWTEST_TX_TIMEOUT_MS   500

/*
 * LP-UART reconfiguration can create a short receive-side transient while
 * GPIO5/GPIO4 and the driver/FIFO settle.  Give the peripheral time to settle,
 * drain anything that arrived during reconfiguration, then start the real
 * loopback transaction.
 */
#define HWTEST_UART_SETTLE_MS    30
#define HWTEST_UART_DRAIN_GAP_MS 5
#define HWTEST_UART_MAX_ATTEMPTS 2

/* Optional command repeat/stress count. */
#define HWTEST_REPEAT_MAX     100000U
#define HWTEST_PROGRESS_STEPS 10U

#if CONFIG_IDF_TARGET_ESP32C6   /* the LP UART loopback test */
static const uint8_t s_uart_pattern[] = {
    0x55, 0xAA, 0x00, 0xFF, 0x11, 0x22, 0x33, 0x44,
    'u', 'S', 'h', 'e', 'l', 'l', '-', 'U',
    'A', 'R', 'T', '-', 'L', 'O', 'O', 'P'};
#endif

static const uint8_t s_rs485_1_to_2[] = {
    0xA5, 0x5A, 0x01, 0x10, 0x20, 0x30, 0x40, 0x50,
    'R', 'S', '4', '8', '5', '-', '1', '>',
    '2', '-', 'u', 'S', 'h', 'e', 'l', 'l'};

static const uint8_t s_rs485_2_to_1[] = {
    0x5A, 0xA5, 0x02, 0x60, 0x70, 0x80, 0x90, 0xF0,
    'R', 'S', '4', '8', '5', '-', '2', '>',
    '1', '-', 'u', 'S', 'h', 'e', 'l', 'l'};

/*
 * Detailed per-cycle output is suppressed during repeat/stress tests so
 * commands such as `hwtest uart 1000` do not flood the terminal.
 */
static bool s_hwtest_quiet = false;

#define HWTEST_DETAIL(...)       \
    do                           \
    {                            \
        if (!s_hwtest_quiet)     \
        {                        \
            printf(__VA_ARGS__); \
        }                        \
    } while (0)

static void print_result(const char *name, bool pass)
{
    printf("%-12s %s\n", name, pass ? "PASS" : "FAIL");
}

static int uart_read_expected(uart_port_t port,
                              uint8_t *buffer,
                              size_t expected,
                              uint32_t timeout_ms)
{
    if (buffer == NULL || expected == 0U)
    {
        return -1;
    }

    size_t total = 0U;
    const int64_t deadline =
        esp_timer_get_time() + ((int64_t)timeout_ms * 1000LL);

    while (total < expected && esp_timer_get_time() < deadline)
    {
        int got = uart_read_bytes(port,
                                  buffer + total,
                                  expected - total,
                                  pdMS_TO_TICKS(20));
        if (got < 0)
        {
            return -1;
        }
        if (got > 0)
        {
            total += (size_t)got;
        }
    }

    return (int)total;
}

static void print_mismatch(const uint8_t *expected,
                           const uint8_t *actual,
                           size_t expected_len,
                           size_t actual_len)
{
    HWTEST_DETAIL("  expected %u byte(s), received %u byte(s)\n",
                  (unsigned)expected_len,
                  (unsigned)actual_len);

    size_t compare = actual_len < expected_len ? actual_len : expected_len;
    for (size_t i = 0U; i < compare; ++i)
    {
        if (expected[i] != actual[i])
        {
            HWTEST_DETAIL("  first mismatch at byte %u: expected=0x%02X actual=0x%02X\n",
                          (unsigned)i,
                          (unsigned)expected[i],
                          (unsigned)actual[i]);
            return;
        }
    }

    if (actual_len != expected_len)
    {
        HWTEST_DETAIL("  payload prefix matched, but byte count differed\n");
    }
}

/* --------------------------------------------------------------------------
 * SD CARD
 * -------------------------------------------------------------------------- */

static uint8_t sd_pattern_byte(size_t offset)
{
    return (uint8_t)(((offset * 37U) + 0x5BU) ^ (offset >> 3U));
}

static esp_err_t ensure_shared_spi_bus(void)
{
    /*
     * W6100 normally initializes SPI2 before hwtest runs.  Remember that fact
     * after the first probe so repeated SD stress cycles do not repeatedly call
     * spi_bus_initialize() and generate an expected "already initialized" log.
     */
    static bool s_spi_bus_ready = false;

    if (s_spi_bus_ready)
    {
        return ESP_OK;
    }

    spi_bus_config_t bus_cfg = {
        .mosi_io_num = HWTEST_SPI_MOSI_GPIO,
        .miso_io_num = HWTEST_SPI_MISO_GPIO,
        .sclk_io_num = HWTEST_SPI_SCLK_GPIO,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 4096,
    };

    esp_err_t err =
        spi_bus_initialize(HWTEST_SPI_HOST, &bus_cfg, SPI_DMA_CH_AUTO);

    if (err == ESP_OK)
    {
        HWTEST_DETAIL("  SPI2 bus initialized by hwtest\n");
        s_spi_bus_ready = true;
        return ESP_OK;
    }

    if (err == ESP_ERR_INVALID_STATE)
    {
        /*
         * Expected when W6100 has already initialized the same SPI2 bus.
         * The SD device is simply attached with its own CS pin.
         */
        HWTEST_DETAIL("  SPI2 bus already initialized; attaching SD as shared device\n");
        s_spi_bus_ready = true;
        return ESP_OK;
    }

    return err;
}

static esp_err_t hwtest_sd(void)
{
    if (!sd_configured())
    {
        HWTEST_DETAIL("  SD card pins are not configured (board keys sd.cs and eth.* or sd.miso/mosi/sclk)\n");
        return ESP_ERR_NOT_SUPPORTED;
    }
    HWTEST_DETAIL("\n[SD CARD]\n");
    HWTEST_DETAIL("  SPI2 MISO=%d MOSI=%d SCLK=%d CS=%d @ <=%d kHz\n",
                  HWTEST_SPI_MISO_GPIO,
                  HWTEST_SPI_MOSI_GPIO,
                  HWTEST_SPI_SCLK_GPIO,
                  HWTEST_SD_CS_GPIO,
                  HWTEST_SD_MAX_FREQ_KHZ);

    /* Mounted with `sd mount` (or at boot): test on it, leave it mounted. */
    const bool premounted = tdsh_sdcard_mounted();
    sdmmc_card_t *card = premounted ? (sdmmc_card_t *)tdsh_sdcard_card() : NULL;
    esp_err_t err = ESP_OK;
    if (premounted)
    {
        HWTEST_DETAIL("  Card already mounted at %s (sd mount); testing on it\n", HWTEST_SD_MOUNT_POINT);
        goto mounted;
    }

    err = ensure_shared_spi_bus();
    if (err != ESP_OK)
    {
        HWTEST_DETAIL("  SPI bus initialization failed: %s\n", esp_err_to_name(err));
        return err;
    }

    sdmmc_host_t host = SDSPI_HOST_DEFAULT();
    host.slot = HWTEST_SPI_HOST;
    host.max_freq_khz = HWTEST_SD_MAX_FREQ_KHZ;

    sdspi_device_config_t slot_cfg = SDSPI_DEVICE_CONFIG_DEFAULT();
    slot_cfg.gpio_cs = HWTEST_SD_CS_GPIO;
    slot_cfg.host_id = HWTEST_SPI_HOST;

    esp_vfs_fat_sdmmc_mount_config_t mount_cfg = {
        .format_if_mount_failed = false,
        .max_files = 4,
        .allocation_unit_size = 16 * 1024,
    };

    err = esp_vfs_fat_sdspi_mount(HWTEST_SD_MOUNT_POINT,
                                  &host,
                                  &slot_cfg,
                                  &mount_cfg,
                                  &card);
    if (err != ESP_OK)
    {
        HWTEST_DETAIL("  SD mount failed: %s\n", esp_err_to_name(err));
        HWTEST_DETAIL("  Card is NOT formatted automatically by this test.\n");
        HWTEST_DETAIL("  Use a FAT-formatted card and verify SPI pull-ups/wiring.\n");
        return err;
    }

    HWTEST_DETAIL("  Card mounted at %s\n", HWTEST_SD_MOUNT_POINT);
mounted:
    if (!s_hwtest_quiet)
    {
        sdmmc_card_print_info(stdout, card);
    }

    /* Remove a stale test file from an interrupted prior test. */
    (void)unlink(HWTEST_SD_FILE);

    FILE *fp = fopen(HWTEST_SD_FILE, "wb");
    if (fp == NULL)
    {
        err = ESP_FAIL;
        HWTEST_DETAIL("  fopen(write) failed: errno=%d (%s)\n", errno, strerror(errno));
        goto cleanup;
    }

    uint8_t block[512];
    for (size_t offset = 0U;
         offset < HWTEST_SD_TEST_BYTES;
         offset += sizeof(block))
    {
        size_t n = HWTEST_SD_TEST_BYTES - offset;
        if (n > sizeof(block))
        {
            n = sizeof(block);
        }

        for (size_t i = 0U; i < n; ++i)
        {
            block[i] = sd_pattern_byte(offset + i);
        }

        if (fwrite(block, 1U, n, fp) != n)
        {
            HWTEST_DETAIL("  SD write failed at offset %u\n", (unsigned)offset);
            fclose(fp);
            fp = NULL;
            err = ESP_FAIL;
            goto cleanup;
        }
    }

    if (fflush(fp) != 0)
    {
        HWTEST_DETAIL("  fflush failed: errno=%d (%s)\n", errno, strerror(errno));
        fclose(fp);
        fp = NULL;
        err = ESP_FAIL;
        goto cleanup;
    }

    if (fclose(fp) != 0)
    {
        fp = NULL;
        HWTEST_DETAIL("  fclose(write) failed: errno=%d (%s)\n", errno, strerror(errno));
        err = ESP_FAIL;
        goto cleanup;
    }
    fp = NULL;

    fp = fopen(HWTEST_SD_FILE, "rb");
    if (fp == NULL)
    {
        HWTEST_DETAIL("  fopen(read) failed: errno=%d (%s)\n", errno, strerror(errno));
        err = ESP_FAIL;
        goto cleanup;
    }

    for (size_t offset = 0U;
         offset < HWTEST_SD_TEST_BYTES;
         offset += sizeof(block))
    {
        size_t n = HWTEST_SD_TEST_BYTES - offset;
        if (n > sizeof(block))
        {
            n = sizeof(block);
        }

        memset(block, 0, sizeof(block));
        size_t got = fread(block, 1U, n, fp);
        if (got != n)
        {
            HWTEST_DETAIL("  SD read failed at offset %u: expected=%u got=%u\n",
                          (unsigned)offset,
                          (unsigned)n,
                          (unsigned)got);
            fclose(fp);
            fp = NULL;
            err = ESP_FAIL;
            goto cleanup;
        }

        for (size_t i = 0U; i < n; ++i)
        {
            uint8_t expected = sd_pattern_byte(offset + i);
            if (block[i] != expected)
            {
                HWTEST_DETAIL("  verify mismatch at offset %u: expected=0x%02X got=0x%02X\n",
                              (unsigned)(offset + i),
                              (unsigned)expected,
                              (unsigned)block[i]);
                fclose(fp);
                fp = NULL;
                err = ESP_FAIL;
                goto cleanup;
            }
        }
    }

    fclose(fp);
    fp = NULL;

    HWTEST_DETAIL("  Write/read/verify: %u bytes OK\n",
                  (unsigned)HWTEST_SD_TEST_BYTES);
    err = ESP_OK;

cleanup:
    if (fp != NULL)
    {
        fclose(fp);
    }

    if (unlink(HWTEST_SD_FILE) != 0 && errno != ENOENT)
    {
        HWTEST_DETAIL("  warning: could not remove test file: %s\n", strerror(errno));
    }

    if (premounted)
    {
        return err;
    }

    esp_err_t unmount_err =
        esp_vfs_fat_sdcard_unmount(HWTEST_SD_MOUNT_POINT, card);
    if (unmount_err != ESP_OK)
    {
        HWTEST_DETAIL("  SD unmount warning: %s\n", esp_err_to_name(unmount_err));
        if (err == ESP_OK)
        {
            err = unmount_err;
        }
    }
    else
    {
        HWTEST_DETAIL("  Card unmounted; shared SPI2 bus left active for W6100\n");
    }

    return err;
}

/* --------------------------------------------------------------------------
 * PLAIN TTL UART -- ESP32-C6 LP UART
 * -------------------------------------------------------------------------- */

#if CONFIG_IDF_TARGET_ESP32C6   /* only the LP UART test uses it */
/*
 * Prepare RX for a deterministic loopback test.
 *
 * uart_flush_input() clears the driver's RX ring buffer.  Immediately after
 * LP-UART/pin reconfiguration, however, a transient byte may still arrive
 * shortly afterwards.  This helper therefore:
 *
 *   1. flushes the software RX buffer,
 *   2. waits for the LP UART / fixed pins to settle,
 *   3. drains any byte that arrived during that settling interval,
 *   4. flushes again,
 *   5. verifies the receive path stays quiet for a short guard interval.
 *
 * The loopback wire remains connected during this procedure.  No valid test
 * packet has been transmitted yet, so every byte found here is startup noise
 * and may safely be discarded.
 */
static int uart_prepare_clean_rx(uart_port_t port)
{
    uint8_t junk[32];
    int discarded = 0;

    (void)uart_flush_input(port);
    vTaskDelay(pdMS_TO_TICKS(HWTEST_UART_SETTLE_MS));

    for (;;)
    {
        int got = uart_read_bytes(port,
                                  junk,
                                  sizeof(junk),
                                  0);
        if (got <= 0)
        {
            break;
        }
        discarded += got;
    }

    (void)uart_flush_input(port);

    /*
     * Small quiet-time guard.  If one final transient was still in the
     * hardware path, allow the ISR to move it into the ring buffer and drain
     * it before sending the real test frame.
     */
    vTaskDelay(pdMS_TO_TICKS(HWTEST_UART_DRAIN_GAP_MS));

    for (;;)
    {
        int got = uart_read_bytes(port,
                                  junk,
                                  sizeof(junk),
                                  0);
        if (got <= 0)
        {
            break;
        }
        discarded += got;
    }

    (void)uart_flush_input(port);
    return discarded;
}
#endif

static esp_err_t hwtest_uart(void)
{
    HWTEST_DETAIL("\n[TTL UART]\n");

#if CONFIG_IDF_TARGET_ESP32C6
    const uart_port_t port = LP_UART_NUM_0;

    HWTEST_DETAIL("  LP_UART0 TX=GPIO%d RX=GPIO%d, %d 8N1\n",
                  HWTEST_UART_TX_GPIO,
                  HWTEST_UART_RX_GPIO,
                  HWTEST_UART_BAUD);
    HWTEST_DETAIL("  Required loopback: connect GPIO%d (TX) -> GPIO%d (RX)\n",
                  HWTEST_UART_TX_GPIO,
                  HWTEST_UART_RX_GPIO);

    uart_config_t cfg = {
        .baud_rate = HWTEST_UART_BAUD,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .rx_flow_ctrl_thresh = 0,
        .lp_source_clk = LP_UART_SCLK_XTAL_D2,
    };

    bool installed = false;
    esp_err_t err = uart_driver_install(port,
                                        HWTEST_UART_RX_BUFFER,
                                        0,
                                        0,
                                        NULL,
                                        0);
    if (err != ESP_OK)
    {
        HWTEST_DETAIL("  LP UART driver install failed: %s\n", esp_err_to_name(err));
        if (err == ESP_ERR_INVALID_STATE)
        {
            HWTEST_DETAIL("  LP UART is already owned by another service.\n");
        }
        return err;
    }
    installed = true;

    err = uart_param_config(port, &cfg);
    if (err != ESP_OK)
    {
        HWTEST_DETAIL("  uart_param_config failed: %s\n", esp_err_to_name(err));
        goto cleanup;
    }

    /*
     * On ESP32-C6 the LP UART pins are fixed in hardware.  Passing the fixed
     * GPIO5/GPIO4 pair documents and validates the intended route.
     */
    err = uart_set_pin(port,
                       HWTEST_UART_TX_GPIO,
                       HWTEST_UART_RX_GPIO,
                       UART_PIN_NO_CHANGE,
                       UART_PIN_NO_CHANGE);
    if (err != ESP_OK)
    {
        HWTEST_DETAIL("  uart_set_pin failed: %s\n", esp_err_to_name(err));
        goto cleanup;
    }

    /*
     * Run up to two attempts.
     *
     * A second attempt is only for the specific startup/reconfiguration
     * transient seen on repeated LP-UART tests.  A genuine wiring/baud/data
     * corruption problem will fail both attempts and therefore still FAIL the
     * hardware test.
     */
    err = ESP_FAIL;

    for (int attempt = 1; attempt <= HWTEST_UART_MAX_ATTEMPTS; ++attempt)
    {
        int discarded = uart_prepare_clean_rx(port);

        if (discarded > 0)
        {
            HWTEST_DETAIL("  RX cleanup discarded %d startup byte(s)\n", discarded);
        }

        uint8_t rx[sizeof(s_uart_pattern)];
        memset(rx, 0, sizeof(rx));

        int written = uart_write_bytes(port,
                                       (const char *)s_uart_pattern,
                                       sizeof(s_uart_pattern));
        if (written != (int)sizeof(s_uart_pattern))
        {
            HWTEST_DETAIL("  TX failed on attempt %d: expected=%u written=%d\n",
                          attempt,
                          (unsigned)sizeof(s_uart_pattern),
                          written);
            err = ESP_FAIL;
            continue;
        }

        esp_err_t tx_err =
            uart_wait_tx_done(port, pdMS_TO_TICKS(HWTEST_TX_TIMEOUT_MS));
        if (tx_err != ESP_OK)
        {
            HWTEST_DETAIL("  TX completion failed on attempt %d: %s\n",
                          attempt,
                          esp_err_to_name(tx_err));
            err = tx_err;
            continue;
        }

        int got = uart_read_expected(port,
                                     rx,
                                     sizeof(rx),
                                     HWTEST_READ_TIMEOUT_MS);

        if (got == (int)sizeof(s_uart_pattern) &&
            memcmp(rx, s_uart_pattern, sizeof(s_uart_pattern)) == 0)
        {
            HWTEST_DETAIL("  Loopback verified: %u/%u bytes identical",
                          (unsigned)sizeof(s_uart_pattern),
                          (unsigned)sizeof(s_uart_pattern));

            if (attempt > 1)
            {
                HWTEST_DETAIL(" (attempt %d)", attempt);
            }

            HWTEST_DETAIL("\n");
            err = ESP_OK;
            break;
        }

        HWTEST_DETAIL("  UART loopback verify failed on attempt %d\n", attempt);
        print_mismatch(s_uart_pattern,
                       rx,
                       sizeof(s_uart_pattern),
                       got > 0 ? (size_t)got : 0U);

        if (attempt < HWTEST_UART_MAX_ATTEMPTS)
        {
            HWTEST_DETAIL("  Re-cleaning LP-UART RX and retrying once...\n");
        }
    }

cleanup:
    if (installed)
    {
        (void)uart_driver_delete(port);
    }
    return err;
#else
    HWTEST_DETAIL("  This direct test currently targets ESP32-C6 only.\n");
    return ESP_ERR_NOT_SUPPORTED;
#endif
}

/* --------------------------------------------------------------------------
 * RS-485 PAIR
 * -------------------------------------------------------------------------- */

static esp_err_t rs485_ch1_init(bool *installed)
{
    *installed = false;

    uart_config_t cfg = {
        .baud_rate = HWTEST_RS485_BAUD,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .rx_flow_ctrl_thresh = 0,
        .source_clk = UART_SCLK_DEFAULT,
    };

    esp_err_t err = uart_driver_install(HWTEST_RS485_1_UART,
                                        HWTEST_UART_RX_BUFFER,
                                        0,
                                        0,
                                        NULL,
                                        0);
    if (err != ESP_OK)
    {
        return err;
    }
    *installed = true;

    err = uart_param_config(HWTEST_RS485_1_UART, &cfg);
    if (err != ESP_OK)
    {
        return err;
    }

    err = uart_set_pin(HWTEST_RS485_1_UART,
                       HWTEST_RS485_1_TX_GPIO,
                       HWTEST_RS485_1_RX_GPIO,
                       HWTEST_RS485_1_DIR_GPIO,
                       UART_PIN_NO_CHANGE);
    if (err != ESP_OK)
    {
        return err;
    }

    return uart_set_mode(HWTEST_RS485_1_UART,
                         UART_MODE_RS485_HALF_DUPLEX);
}

static esp_err_t rs485_ch2_init(bool *installed)
{
    *installed = false;

    uart_config_t cfg = {
        .baud_rate = HWTEST_RS485_BAUD,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .rx_flow_ctrl_thresh = 0,
        .source_clk = UART_SCLK_DEFAULT,
    };

    esp_err_t err = uart_driver_install(HWTEST_RS485_2_UART,
                                        HWTEST_UART_RX_BUFFER,
                                        0,
                                        0,
                                        NULL,
                                        0);
    if (err != ESP_OK)
    {
        return err;
    }
    *installed = true;

    err = uart_param_config(HWTEST_RS485_2_UART, &cfg);
    if (err != ESP_OK)
    {
        return err;
    }

    /*
     * Channel 2 uses a separate GPIO7 direction line in the existing board
     * firmware rather than the UART RTS signal.
     */
    err = uart_set_pin(HWTEST_RS485_2_UART,
                       HWTEST_RS485_2_TX_GPIO,
                       HWTEST_RS485_2_RX_GPIO,
                       UART_PIN_NO_CHANGE,
                       UART_PIN_NO_CHANGE);
    if (err != ESP_OK)
    {
        return err;
    }

    gpio_config_t dir_cfg = {
        .pin_bit_mask = 1ULL << HWTEST_RS485_2_DIR_GPIO,
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    err = gpio_config(&dir_cfg);
    if (err != ESP_OK)
    {
        return err;
    }

    return gpio_set_level(HWTEST_RS485_2_DIR_GPIO, 0); /* RX */
}

static esp_err_t hwtest_rs485(void)
{
    if (!rs485_configured())
    {
        HWTEST_DETAIL("  RS-485 lines are not configured (board keys rs485.1.* and rs485.2.*)\n");
        return ESP_ERR_NOT_SUPPORTED;
    }
    HWTEST_DETAIL("\n[RS-485 PAIR]\n");
    HWTEST_DETAIL("  CH1 UART1: TX=%d RX=%d RTS/DE=%d, %d 8N1\n",
                  HWTEST_RS485_1_TX_GPIO,
                  HWTEST_RS485_1_RX_GPIO,
                  HWTEST_RS485_1_DIR_GPIO,
                  HWTEST_RS485_BAUD);
    HWTEST_DETAIL("  CH2 UART0: TX=%d RX=%d DIR/DE=%d, %d 8N1\n",
                  HWTEST_RS485_2_TX_GPIO,
                  HWTEST_RS485_2_RX_GPIO,
                  HWTEST_RS485_2_DIR_GPIO,
                  HWTEST_RS485_BAUD);
    HWTEST_DETAIL("  Required loopback: CH1 A->CH2 A, CH1 B->CH2 B, GND->GND\n");

    bool ch1_installed = false;
    bool ch2_installed = false;

    esp_err_t err = rs485_ch1_init(&ch1_installed);
    if (err != ESP_OK)
    {
        HWTEST_DETAIL("  RS485-1 init failed: %s\n", esp_err_to_name(err));
        if (err == ESP_ERR_INVALID_STATE)
        {
            HWTEST_DETAIL("  UART1 is already owned by another service.\n");
        }
        goto cleanup;
    }

    err = rs485_ch2_init(&ch2_installed);
    if (err != ESP_OK)
    {
        HWTEST_DETAIL("  RS485-2 init failed: %s\n", esp_err_to_name(err));
        if (err == ESP_ERR_INVALID_STATE)
        {
            HWTEST_DETAIL("  UART0 is already owned by another service.\n");
        }
        goto cleanup;
    }

    (void)uart_flush_input(HWTEST_RS485_1_UART);
    (void)uart_flush_input(HWTEST_RS485_2_UART);

    /* ---------------- CH1 -> CH2 ---------------- */
    int written = uart_write_bytes(HWTEST_RS485_1_UART,
                                   (const char *)s_rs485_1_to_2,
                                   sizeof(s_rs485_1_to_2));
    if (written != (int)sizeof(s_rs485_1_to_2))
    {
        HWTEST_DETAIL("  CH1->CH2 TX failed: expected=%u written=%d\n",
                      (unsigned)sizeof(s_rs485_1_to_2),
                      written);
        err = ESP_FAIL;
        goto cleanup;
    }

    err = uart_wait_tx_done(HWTEST_RS485_1_UART,
                            pdMS_TO_TICKS(HWTEST_TX_TIMEOUT_MS));
    if (err != ESP_OK)
    {
        HWTEST_DETAIL("  CH1 TX completion failed: %s\n", esp_err_to_name(err));
        goto cleanup;
    }

    uint8_t rx12[sizeof(s_rs485_1_to_2)];
    memset(rx12, 0, sizeof(rx12));

    int got12 = uart_read_expected(HWTEST_RS485_2_UART,
                                   rx12,
                                   sizeof(rx12),
                                   HWTEST_READ_TIMEOUT_MS);
    if (got12 != (int)sizeof(s_rs485_1_to_2) ||
        memcmp(rx12, s_rs485_1_to_2, sizeof(s_rs485_1_to_2)) != 0)
    {
        HWTEST_DETAIL("  CH1 -> CH2 verify FAILED\n");
        print_mismatch(s_rs485_1_to_2,
                       rx12,
                       sizeof(s_rs485_1_to_2),
                       got12 > 0 ? (size_t)got12 : 0U);
        err = ESP_FAIL;
        goto cleanup;
    }

    HWTEST_DETAIL("  CH1 -> CH2: %u bytes verified\n",
                  (unsigned)sizeof(s_rs485_1_to_2));

    /* Clear any echo/noise before testing the opposite direction. */
    (void)uart_flush_input(HWTEST_RS485_1_UART);
    (void)uart_flush_input(HWTEST_RS485_2_UART);

    /* ---------------- CH2 -> CH1 ---------------- */
    err = gpio_set_level(HWTEST_RS485_2_DIR_GPIO, 1); /* TX */
    if (err != ESP_OK)
    {
        HWTEST_DETAIL("  CH2 direction -> TX failed: %s\n", esp_err_to_name(err));
        goto cleanup;
    }

    vTaskDelay(pdMS_TO_TICKS(2));

    written = uart_write_bytes(HWTEST_RS485_2_UART,
                               (const char *)s_rs485_2_to_1,
                               sizeof(s_rs485_2_to_1));
    if (written != (int)sizeof(s_rs485_2_to_1))
    {
        HWTEST_DETAIL("  CH2->CH1 TX failed: expected=%u written=%d\n",
                      (unsigned)sizeof(s_rs485_2_to_1),
                      written);
        (void)gpio_set_level(HWTEST_RS485_2_DIR_GPIO, 0);
        err = ESP_FAIL;
        goto cleanup;
    }

    err = uart_wait_tx_done(HWTEST_RS485_2_UART,
                            pdMS_TO_TICKS(HWTEST_TX_TIMEOUT_MS));

    /*
     * Do not return to receive mode until the final stop bit has physically
     * left the UART.  uart_wait_tx_done() provides that guarantee.
     */
    vTaskDelay(pdMS_TO_TICKS(2));
    (void)gpio_set_level(HWTEST_RS485_2_DIR_GPIO, 0); /* RX */

    if (err != ESP_OK)
    {
        HWTEST_DETAIL("  CH2 TX completion failed: %s\n", esp_err_to_name(err));
        goto cleanup;
    }

    uint8_t rx21[sizeof(s_rs485_2_to_1)];
    memset(rx21, 0, sizeof(rx21));

    int got21 = uart_read_expected(HWTEST_RS485_1_UART,
                                   rx21,
                                   sizeof(rx21),
                                   HWTEST_READ_TIMEOUT_MS);
    if (got21 != (int)sizeof(s_rs485_2_to_1) ||
        memcmp(rx21, s_rs485_2_to_1, sizeof(s_rs485_2_to_1)) != 0)
    {
        HWTEST_DETAIL("  CH2 -> CH1 verify FAILED\n");
        print_mismatch(s_rs485_2_to_1,
                       rx21,
                       sizeof(s_rs485_2_to_1),
                       got21 > 0 ? (size_t)got21 : 0U);
        err = ESP_FAIL;
        goto cleanup;
    }

    HWTEST_DETAIL("  CH2 -> CH1: %u bytes verified\n",
                  (unsigned)sizeof(s_rs485_2_to_1));
    err = ESP_OK;

cleanup:
    /*
     * Always leave the manual RS-485 transceiver in receive mode before
     * releasing the UART driver.
     */
    (void)gpio_set_level(HWTEST_RS485_2_DIR_GPIO, 0);

    if (ch2_installed)
    {
        (void)uart_driver_delete(HWTEST_RS485_2_UART);
    }
    if (ch1_installed)
    {
        (void)uart_driver_delete(HWTEST_RS485_1_UART);
    }

    return err;
}

/* --------------------------------------------------------------------------
 * SHELL COMMAND
 * -------------------------------------------------------------------------- */

static void print_pin_line(const char *label, const char *bus, int a, int b, int c, int d)
{
    if (a < 0 || b < 0 || c < 0 || d < 0)
        printf("%s: not configured\n", label);
    else
        printf("%s: %s %d %d %d %d\n", label, bus, a, b, c, d);
}

static void hwtest_print_status(void)
{
    printf("Hardware test map (board configuration)\n");
    printf("-----------------------------------------------\n");
    print_pin_line("SD card   ", "SPI MISO MOSI SCLK CS:", s_pin.miso, s_pin.mosi, s_pin.sclk, s_pin.sd_cs);
#if CONFIG_IDF_TARGET_ESP32C6
    printf("TTL UART  : LP_UART0 TX5 RX4 @ %d\n", HWTEST_UART_BAUD);
#else
    printf("TTL UART  : not on this chip (the test uses the ESP32-C6 LP UART)\n");
#endif
    print_pin_line("RS485-1   ", "UART TX RX DE:", s_pin.r1_uart, s_pin.r1_tx, s_pin.r1_rx, s_pin.r1_de);
    print_pin_line("RS485-2   ", "UART TX RX DE:", s_pin.r2_uart, s_pin.r2_tx, s_pin.r2_rx, s_pin.r2_de);
    printf("-----------------------------------------------\n");
    printf("Loopback wiring for tests:\n");
    printf("  UART     : LP UART TX -> RX\n");
    printf("  RS485    : line 1 A -> line 2 A, B -> B, GND -> GND\n");
    printf("  SD       : insert a FAT-formatted SD card\n");
    printf("  Repeat   : hwtest uart 1000 | hwtest rs485 1000 | hwtest sd 100\n");
    printf("Set the pins with `board set <key> <value>` (keys: board.example.conf).\n");
}

static int run_named_test(const char *name, esp_err_t (*fn)(void))
{
    esp_err_t err = fn();
    if (err == ESP_ERR_NOT_SUPPORTED)
    {        /* not configured / not on this chip */
        printf("[SKIP] %s\n", name);
        return 0;
    }
    print_result(name, err == ESP_OK);
    if (err != ESP_OK)
    {
        printf("  error: %s (0x%x)\n",
               esp_err_to_name(err),
               (unsigned)err);
        return 1;
    }
    return 0;
}


/* --------------------------------------------------------------------------
 * REPEAT / STRESS RUNNERS
 * -------------------------------------------------------------------------- */

static bool parse_repeat_count(const char *text, uint32_t *count_out)
{
    if (text == NULL || count_out == NULL || *text == '\0')
    {
        return false;
    }

    errno = 0;
    char *end = NULL;
    unsigned long value = strtoul(text, &end, 10);

    if (errno != 0 ||
        end == text ||
        *end != '\0' ||
        value == 0UL ||
        value > HWTEST_REPEAT_MAX)
    {
        return false;
    }

    *count_out = (uint32_t)value;
    return true;
}

static bool should_print_progress(uint32_t done, uint32_t total)
{
    if (total < 20U || done == total)
    {
        return false;
    }

    uint32_t interval = total / HWTEST_PROGRESS_STEPS;
    if (interval == 0U)
    {
        interval = 1U;
    }

    return (done % interval) == 0U;
}

/*
 * Stress wrappers intentionally call the already-proven one-cycle tests.
 *
 * This means SD repeat mode exercises mount -> write -> read/verify -> unmount
 * for every cycle, which is useful for finding lifecycle/shared-SPI problems.
 *
 * UART and RS-485 currently also reinitialize their UART driver each cycle.
 * That deliberately stress-tests init/deinit and direction setup in addition
 * to payload integrity.  A later dedicated throughput benchmark can keep the
 * driver open continuously if desired.
 */
static int run_repeat_test(const char *name,
                           esp_err_t (*fn)(void),
                           uint32_t count)
{
    if (count == 1U)
    {
        return run_named_test(name, fn);
    }

    printf("\n[%s STRESS TEST]\n", name);
    printf("  Cycles requested: %u\n", (unsigned)count);

    uint32_t passed = 0U;
    uint32_t failed = 0U;
    uint32_t first_failed_cycle = 0U;
    esp_err_t first_error = ESP_OK;

    int64_t start_us = esp_timer_get_time();

    bool previous_quiet = s_hwtest_quiet;
    s_hwtest_quiet = true;

    for (uint32_t cycle = 1U; cycle <= count; ++cycle)
    {
        esp_err_t err = fn();

        if (err == ESP_OK)
        {
            ++passed;
        }
        else
        {
            ++failed;
            if (first_failed_cycle == 0U)
            {
                first_failed_cycle = cycle;
                first_error = err;
            }
        }

        if (should_print_progress(cycle, count))
        {
            printf("  Progress: %u/%u cycles, pass=%u fail=%u\n",
                   (unsigned)cycle,
                   (unsigned)count,
                   (unsigned)passed,
                   (unsigned)failed);
        }

        /*
         * Yield so a long hardware test does not monopolize the shell task and
         * starve unrelated FreeRTOS work.
         */
        taskYIELD();
    }

    s_hwtest_quiet = previous_quiet;

    int64_t elapsed_us = esp_timer_get_time() - start_us;
    double elapsed_s = (double)elapsed_us / 1000000.0;

    printf("\n%s STRESS SUMMARY\n", name);
    printf("-----------------------------------------------\n");
    printf("Cycles:        %u\n", (unsigned)count);
    printf("Passed:        %u\n", (unsigned)passed);
    printf("Failed:        %u\n", (unsigned)failed);
    printf("Elapsed:       %.3f s\n", elapsed_s);

    if (first_failed_cycle != 0U)
    {
        printf("First failure: cycle %u, %s (0x%x)\n",
               (unsigned)first_failed_cycle,
               esp_err_to_name(first_error),
               (unsigned)first_error);
    }

    printf("RESULT:        %s\n", failed == 0U ? "PASS" : "FAIL");
    printf("-----------------------------------------------\n");

    return failed == 0U ? 0 : 1;
}


int tdsh_cmd_hwtest(tdsh_session_t *session, int argc, char **argv)
{
    (void)session;
    hwtest_load_pins();

    if (argc == 1 ||
        (argc == 2 && strcmp(argv[1], "status") == 0))
    {
        hwtest_print_status();
        printf("\nusage:\n");
        printf("  hwtest status\n");
        printf("  hwtest sd [count]\n");
        printf("  hwtest uart [count]\n");
        printf("  hwtest rs485 [count]\n");
        printf("  hwtest all\n");
        printf("count range: 1..%u\n", (unsigned)HWTEST_REPEAT_MAX);
        return 0;
    }

    if (argc < 2 || argc > 3)
    {
        printf("usage: hwtest <sd|uart|rs485> [count] | hwtest <status|all>\n");
        return 2;
    }

    uint32_t count = 1U;

    if (argc == 3)
    {
        if (!parse_repeat_count(argv[2], &count))
        {
            printf("hwtest: invalid count '%s' (valid range: 1..%u)\n",
                   argv[2],
                   (unsigned)HWTEST_REPEAT_MAX);
            return 2;
        }
    }

    if (strcmp(argv[1], "sd") == 0)
    {
        return run_repeat_test("SD", hwtest_sd, count);
    }

    if (strcmp(argv[1], "uart") == 0)
    {
        return run_repeat_test("UART", hwtest_uart, count);
    }

    if (strcmp(argv[1], "rs485") == 0)
    {
        return run_repeat_test("RS485", hwtest_rs485, count);
    }

    if (strcmp(argv[1], "all") == 0)
    {
        if (argc != 2)
        {
            printf("hwtest: 'all' does not accept a repeat count\n");
            return 2;
        }

        int failures = 0;

        printf("============================================================\n");
        printf(" PHYSICAL HARDWARE TEST\n");
        printf("============================================================\n");
        hwtest_print_status();

        failures += run_named_test("SD", hwtest_sd);
        failures += run_named_test("UART", hwtest_uart);
        failures += run_named_test("RS485", hwtest_rs485);

        printf("\n============================================================\n");
        printf("RESULT: %s (%d failure%s)\n",
               failures == 0 ? "ALL HARDWARE TESTS PASSED" : "HARDWARE TEST FAILED",
               failures,
               failures == 1 ? "" : "s");
        printf("============================================================\n");

        return failures == 0 ? 0 : 1;
    }

    printf("usage: hwtest <sd|uart|rs485> [count] | hwtest <status|all>\n");
    return 2;
}

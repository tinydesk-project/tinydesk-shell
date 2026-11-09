/*
 * tdsh_sdcard.c - the SD card as /sd: FAT over SPI, pins from the board
 * configuration (sd.cs, and sd.miso/mosi/sclk/spi_host or the W6100's eth.*
 * bus, which the card then shares).
 *
 * The card is mounted in the VFS at /sd, and the shell's logical path /sd
 * maps to it, so the shell, nano, FTP and (for root) SFTP all see the same
 * files. While it is mounted an empty LittleFS directory /fs/sd lets a
 * listing of / show it. Nothing is formatted unless `sd format --yes` asks.
 *
 * Hot-plug (sd.automount, default 1 when the pins are set): a watcher task
 * mounts a card when one is inserted and unmounts it when it is pulled,
 * from the card-detect switch when the board has one (sd.cd, its level
 * with a card in sd.cd_level), else by asking the card every 2 s while it
 * is mounted and trying a mount every 5 s while it is not. `sd unmount`
 * stops that until the card is taken out (with sd.cd) or `sd mount`. A
 * mounted card gets the folder /sd/TinyDesk (TinyDesk's apps and caches);
 * the rest of the card is the user's. Listeners hear every change.
 */
#include "tdsh_espidf_internal.h"
#include "tdsh_board.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "driver/gpio.h"
#include "driver/sdspi_host.h"
#include "driver/spi_common.h"
#include "esp_log.h"
#include "esp_vfs_fat.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "sdmmc_cmd.h"

#define SD_VFS         "/sd"
#define SD_PLACEHOLDER TDSH_MOUNT_POINT "/sd"
#define SD_MAX_KHZ     10000
#define SD_MAX_FILES   5
#define SD_HOME        SD_VFS "/TinyDesk"
#define WATCH_MS       2000
#define RETRY_MS       5000
#define MAX_LISTENERS  4

static const char *TAG = "tdsh-sd";

typedef struct
{
    int host, miso, mosi, sclk, cs;
} sd_pins_t;

static sdmmc_card_t *s_card;
static SemaphoreHandle_t s_lock;
static bool s_held_off;   /* `sd unmount`: no automatic mount for now */
static struct
{
    void (*fn)(bool mounted, void *user);
    void *user;
} s_listeners[MAX_LISTENERS];

static void tell(bool mounted)
{
    for (int i = 0; i < MAX_LISTENERS; i++)
        if (s_listeners[i].fn)
            s_listeners[i].fn(mounted, s_listeners[i].user);
}

void tdsh_sdcard_add_listener(void (*fn)(bool mounted, void *user), void *user)
{
    for (int i = 0; i < MAX_LISTENERS; i++)
        if (!s_listeners[i].fn)
        {
            s_listeners[i].fn = fn;
            s_listeners[i].user = user;
            return;
        }
}

int tdsh_sdcard_space(uint64_t *total, uint64_t *free_bytes)
{
    uint64_t t = 0, f = 0;
    if (!s_card || esp_vfs_fat_info(SD_VFS, &t, &f) != ESP_OK)
        return -1;
    if (total)
        *total = t;
    if (free_bytes)
        *free_bytes = f;
    return 0;
}

static void load_pins(sd_pins_t *p)
{
    p->host = tdsh_board_int("sd.spi_host", tdsh_board_int("eth.spi_host", 1));
    p->miso = tdsh_board_int("sd.miso", tdsh_board_int("eth.miso", -1));
    p->mosi = tdsh_board_int("sd.mosi", tdsh_board_int("eth.mosi", -1));
    p->sclk = tdsh_board_int("sd.sclk", tdsh_board_int("eth.sclk", -1));
    p->cs = tdsh_board_int("sd.cs", -1);
}

static bool pins_ok(const sd_pins_t *p)
{
    return p->host >= 0 && p->miso >= 0 && p->mosi >= 0 && p->sclk >= 0 && p->cs >= 0;
}

static void lock(void)
{
    if (!s_lock)
        s_lock = xSemaphoreCreateMutex();
    if (s_lock)
        xSemaphoreTake(s_lock, portMAX_DELAY);
}

static void unlock(void)
{
    if (s_lock)
        xSemaphoreGive(s_lock);
}

/* The bus may already be up for the W6100 (or the other way round: the
 * W6100 driver accepts a bus that is already initialized). It is never
 * freed here, so the Ethernet chip keeps working after an unmount. */
static esp_err_t bus_up(const sd_pins_t *p)
{
    spi_bus_config_t bus = {
        .mosi_io_num = p->mosi,
        .miso_io_num = p->miso,
        .sclk_io_num = p->sclk,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 4096,
    };
    esp_err_t err = spi_bus_initialize((spi_host_device_t)p->host, &bus, SPI_DMA_CH_AUTO);
    return err == ESP_ERR_INVALID_STATE ? ESP_OK : err;
}

bool tdsh_sdcard_mounted(void)
{
    return s_card != NULL;
}

void *tdsh_sdcard_card(void)
{
    return s_card;
}

bool tdsh_sdcard_configured(void)
{
    sd_pins_t p;
    load_pins(&p);
    return pins_ok(&p);
}

/* ESP-IDF logs routine details while a card is attached (the bus the W6100
 * already set up, CS pin setup, SDIO probes the card rejects): quiet them
 * for the mount; real failures come back as errors. */
static const char *const QUIET_TAGS[] = {"spi", "gpio", "sdspi_transaction", "sdmmc_common"};
static esp_log_level_t s_saved[sizeof(QUIET_TAGS) / sizeof(QUIET_TAGS[0])];

static void quiet_logs(bool on)
{
    for (size_t i = 0; i < sizeof(QUIET_TAGS) / sizeof(QUIET_TAGS[0]); ++i)
    {
        if (on)
        {
            s_saved[i] = esp_log_level_get(QUIET_TAGS[i]);
            esp_log_level_set(QUIET_TAGS[i], ESP_LOG_WARN);
        }
        else
        {
            esp_log_level_set(QUIET_TAGS[i], s_saved[i]);
        }
    }
}

static esp_err_t mount_locked(bool format_if_unformatted)
{
    if (s_card)
        return ESP_OK;
    sd_pins_t p;
    load_pins(&p);
    if (!pins_ok(&p))
        return ESP_ERR_NOT_SUPPORTED;

    quiet_logs(true);
    esp_log_level_set("spi", ESP_LOG_NONE);      /* "SPI bus already initialized" is expected */
    esp_err_t err = bus_up(&p);
    esp_log_level_set("spi", ESP_LOG_WARN);
    if (err != ESP_OK)
    {
        quiet_logs(false);
        return err;
    }

    sdmmc_host_t host = SDSPI_HOST_DEFAULT();
    host.slot = p.host;
    host.max_freq_khz = SD_MAX_KHZ;
    sdspi_device_config_t slot = SDSPI_DEVICE_CONFIG_DEFAULT();
    slot.gpio_cs = p.cs;
    slot.host_id = (spi_host_device_t)p.host;
    esp_vfs_fat_sdmmc_mount_config_t cfg = {
        .format_if_mount_failed = format_if_unformatted,
        .max_files = SD_MAX_FILES,
        .allocation_unit_size = 16 * 1024,
    };
    err = esp_vfs_fat_sdspi_mount(SD_VFS, &host, &slot, &cfg, &s_card);
    quiet_logs(false);
    if (err != ESP_OK)
    {
        s_card = NULL;
        return err;
    }
    if (mkdir(SD_PLACEHOLDER, 0755) != 0 && errno != EEXIST)
    {
        ESP_LOGW(TAG, "could not create %s: errno %d", SD_PLACEHOLDER, errno);
    }
    (void)mkdir(SD_HOME, 0755);   /* TinyDesk's apps and caches */
    ESP_LOGI(TAG, "SD card %s mounted at %s", s_card->cid.name, SD_VFS);
    return ESP_OK;
}

static esp_err_t unmount_locked(void)
{
    if (!s_card)
        return ESP_OK;
    quiet_logs(true);
    esp_err_t err = esp_vfs_fat_sdcard_unmount(SD_VFS, s_card);
    quiet_logs(false);
    s_card = NULL;
    (void)rmdir(SD_PLACEHOLDER);       /* only succeeds while it is the empty placeholder */
    return err;
}

esp_err_t tdsh_sdcard_mount(void)
{
    lock();
    bool was = s_card != NULL;
    esp_err_t err = mount_locked(false);
    if (err == ESP_OK)
        s_held_off = false;
    unlock();
    if (err == ESP_OK && !was)
        tell(true);
    return err;
}

esp_err_t tdsh_sdcard_unmount(void)
{
    lock();
    bool was = s_card != NULL;
    esp_err_t err = unmount_locked();
    s_held_off = true;
    unlock();
    if (was)
        tell(false);
    return err;
}

/* ------------------------------------------------------------ hot-plug */

static int s_cd = -1, s_cd_level;

static bool card_present(void)
{
    return s_cd >= 0 && gpio_get_level((gpio_num_t)s_cd) == s_cd_level;
}

static void watch_task(void *arg)
{
    (void)arg;
    int since_try = RETRY_MS;
    for (;;)
    {
        vTaskDelay(pdMS_TO_TICKS(WATCH_MS));
        since_try += WATCH_MS;
        bool changed = false, now_mounted = false;
        lock();
        if (s_card)
        {
            /* Pulled out: the switch says so, or the card stops answering. */
            bool gone = s_cd >= 0 ? !card_present() : sdmmc_get_status(s_card) != ESP_OK;
            if (gone)
            {
                ESP_LOGW(TAG, "SD card removed");
                quiet_logs(true);
                (void)esp_vfs_fat_sdcard_unmount(SD_VFS, s_card);
                quiet_logs(false);
                s_card = NULL;
                (void)rmdir(SD_PLACEHOLDER);
                changed = true;
            }
        }
        else if (s_cd >= 0 && !card_present())
        {
            s_held_off = false;   /* taken out: the next card mounts again */
        }
        else if (!s_held_off && (s_cd >= 0 || since_try >= RETRY_MS))
        {
            since_try = 0;
            if (mount_locked(false) == ESP_OK)
            {
                changed = true;
                now_mounted = true;
            }
        }
        unlock();
        if (changed)
            tell(now_mounted);
    }
}

bool tdsh_sdcard_translate_logical(const char *logical, char *real_out, size_t real_out_size)
{
    if (!s_card || !logical || !real_out || real_out_size == 0)
        return false;
    if (strncmp(logical, "/sd", 3) != 0 || (logical[3] != '\0' && logical[3] != '/'))
        return false;
    /* "/sd" itself is the card's root directory. */
    int n = snprintf(real_out, real_out_size, "%s%s", SD_VFS, logical[3] ? logical + 3 : "/");
    return n >= 0 && (size_t)n < real_out_size;
}

esp_err_t tdsh_sdcard_init(void)
{
    if (!s_lock)
        s_lock = xSemaphoreCreateMutex();
    /* A card left mounted by an earlier boot leaves its placeholder. */
    (void)rmdir(SD_PLACEHOLDER);
    bool configured = tdsh_sdcard_configured();
    if (tdsh_board_int("sd.automount", configured ? 1 : 0) != 1)
        return ESP_OK;
    if (!configured)
    {
        ESP_LOGW(TAG, "sd.automount is set, but the SD pins are not configured");
        return ESP_ERR_NOT_SUPPORTED;
    }
    s_cd = tdsh_board_int("sd.cd", -1);
    s_cd_level = tdsh_board_int("sd.cd_level", 0);
    if (s_cd >= 0)
    {
        gpio_config_t io = {.pin_bit_mask = 1ULL << s_cd, .mode = GPIO_MODE_INPUT, .pull_up_en = GPIO_PULLUP_ENABLE};
        if (gpio_config(&io) != ESP_OK)
            s_cd = -1;
    }
    esp_err_t err = s_cd < 0 || card_present() ? tdsh_sdcard_mount() : ESP_ERR_NOT_FOUND;
    if (err == ESP_OK)
        ESP_LOGI(TAG, "SD card mounted at boot");
    s_held_off = false;   /* a failed mount at boot is not `sd unmount` */
    xTaskCreate(watch_task, "tdsh_sd", 3072, NULL, 2, NULL);
    return err;
}

static void print_size(const char *label, uint64_t bytes)
{
    if (bytes >= 10ULL * 1024 * 1024 * 1024)
    {
        printf("%s%llu GB\n", label, (unsigned long long)(bytes / (1024ULL * 1024 * 1024)));
    }
    else
    {
        printf("%s%llu MB\n", label, (unsigned long long)(bytes / (1024ULL * 1024)));
    }
}

static int cmd_status(void)
{
    sd_pins_t p;
    load_pins(&p);
    if (!pins_ok(&p))
    {
        printf("SD card: not configured (board keys sd.cs, and sd.miso/mosi/sclk or eth.*)\n");
        return 1;
    }
    printf("SD card:   %s\n", s_card ? "mounted at /sd" : "not mounted (sd mount)");
    printf("Pins:      SPI%d MISO %d MOSI %d SCLK %d CS %d, %d kHz\n",
           p.host + 1, p.miso, p.mosi, p.sclk, p.cs, SD_MAX_KHZ);
    bool hotplug = tdsh_board_int("sd.automount", tdsh_sdcard_configured() ? 1 : 0) == 1;
    printf("Hot-plug:  %s\n", !hotplug    ? "off (board set sd.automount 1)"
                              : s_cd >= 0 ? "on, from the card-detect switch (sd.cd)"
                                          : "on, the card is checked every few seconds");
    if (!s_card)
        return 0;
    printf("Card:      %s, %s\n", s_card->cid.name,
           (s_card->ocr & (1u << 30)) ? "SDHC/SDXC" : "SDSC");
    print_size("Size:      ", (uint64_t)s_card->csd.capacity * s_card->csd.sector_size);
    uint64_t total = 0, free_bytes = 0;
    if (esp_vfs_fat_info(SD_VFS, &total, &free_bytes) == ESP_OK)
    {
        print_size("Free:      ", free_bytes);
    }
    return 0;
}

int tdsh_cmd_sd(tdsh_session_t *session, int argc, char **argv)
{
    (void)session;
    const char *sub = argc >= 2 ? argv[1] : "status";

    if (strcmp(sub, "status") == 0 && argc <= 2)
        return cmd_status();

    if (strcmp(sub, "mount") == 0 && argc == 2)
    {
        if (!tdsh_sdcard_configured())
        {
            printf("sd: the SD pins are not configured (board keys sd.cs, and sd.miso/mosi/sclk or eth.*)\n");
            return 1;
        }
        if (s_card)
        {
            printf("The SD card is already mounted at /sd.\n");
            return 0;
        }
        esp_err_t err = tdsh_sdcard_mount();
        if (err != ESP_OK)
        {
            printf("sd: cannot mount the card: %s\n", esp_err_to_name(err));
            printf("    Is a FAT-formatted card inserted? (sd format --yes erases and formats it)\n");
            return 1;
        }
        printf("SD card %s mounted at /sd.\n", s_card->cid.name);
        return 0;
    }

    if ((strcmp(sub, "umount") == 0 || strcmp(sub, "unmount") == 0) && argc == 2)
    {
        if (!s_card)
        {
            printf("The SD card is not mounted.\n");
            return 0;
        }
        esp_err_t err = tdsh_sdcard_unmount();
        if (err != ESP_OK)
        {
            printf("sd: unmount: %s\n", esp_err_to_name(err));
            return 1;
        }
        printf("SD card unmounted; it can be removed.\n");
        return 0;
    }

    if (strcmp(sub, "format") == 0)
    {
        if (argc != 3 || strcmp(argv[2], "--yes") != 0)
        {
            printf("sd format erases everything on the card and makes a new FAT file system.\n");
            printf("Run it as: sd format --yes\n");
            return 2;
        }
        if (!tdsh_sdcard_configured())
        {
            printf("sd: the SD pins are not configured\n");
            return 1;
        }
        lock();
        esp_err_t err = mount_locked(true);         /* an unformatted card is formatted here */
        if (err == ESP_OK)
            err = esp_vfs_fat_sdcard_format(SD_VFS, s_card);
        unlock();
        if (err != ESP_OK)
        {
            printf("sd: format failed: %s\n", esp_err_to_name(err));
            return 1;
        }
        printf("SD card formatted (FAT) and mounted at /sd.\n");
        return 0;
    }

    printf("usage: sd [status] | sd mount | sd umount | sd format --yes\n");
    return 2;
}

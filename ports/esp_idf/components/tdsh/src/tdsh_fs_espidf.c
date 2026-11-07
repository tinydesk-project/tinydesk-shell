#include "tdsh_espidf_internal.h"

#include <errno.h>
#include <sys/stat.h>

#include "esp_littlefs.h"
#include "esp_log.h"

static const char *TAG = "tdsh-fs";

static void mkdir_if_missing(const char *path)
{
    if (mkdir(path, 0755) != 0 && errno != EEXIST)
    {
        ESP_LOGW(TAG, "mkdir(%s) failed: errno=%d", path, errno);
    }
}

esp_err_t tdsh_fs_init(bool format_if_mount_failed)
{
    const esp_vfs_littlefs_conf_t conf = {
        .base_path = TDSH_MOUNT_POINT,
        .partition_label = TDSH_PARTITION_LABEL,
        .format_if_mount_failed = format_if_mount_failed,
        .dont_mount = false,
        /* A file system made for a smaller partition (an older layout, a
         * Shell firmware) grows to the whole partition, keeping its files;
         * otherwise the rest of the partition is never used. */
        .grow_on_mount = true,
    };

    esp_err_t err = esp_vfs_littlefs_register(&conf);
    if (err != ESP_OK && err != ESP_ERR_INVALID_STATE)
    {
        ESP_LOGE(TAG, "LittleFS mount failed: %s", esp_err_to_name(err));
        return err;
    }

    mkdir_if_missing(TDSH_MOUNT_POINT "/root");
    mkdir_if_missing(TDSH_MOUNT_POINT "/home");
    mkdir_if_missing(TDSH_MOUNT_POINT "/tmp");
    mkdir_if_missing(TDSH_MOUNT_POINT "/etc");

    tdsh_fs_print_info();
    return ESP_OK;
}

void tdsh_fs_print_info(void)
{
    size_t total = 0, used = 0;
    esp_err_t err = esp_littlefs_info(TDSH_PARTITION_LABEL, &total, &used);
    if (err == ESP_OK)
    {
        ESP_LOGI(TAG, "LittleFS: total=%u bytes, used=%u bytes",
                 (unsigned)total, (unsigned)used);
    }
    else
    {
        ESP_LOGW(TAG, "esp_littlefs_info failed: %s", esp_err_to_name(err));
    }
}

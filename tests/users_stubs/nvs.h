#ifndef USERS_TEST_NVS_H
#define USERS_TEST_NVS_H
#include <stddef.h>
#include <stdint.h>
typedef int esp_err_t;
typedef int nvs_handle_t;
#define ESP_OK                0
#define ESP_FAIL              -1
#define ESP_ERR_INVALID_ARG   2
#define ESP_ERR_INVALID_STATE 3
#define ESP_ERR_NO_MEM        4
#define ESP_ERR_NVS_NOT_FOUND 5
#define NVS_READONLY          0
#define NVS_READWRITE         1
esp_err_t nvs_open(const char *, int, nvs_handle_t *);
void nvs_close(nvs_handle_t);
esp_err_t nvs_get_blob(nvs_handle_t, const char *, void *, size_t *);
esp_err_t nvs_set_blob(nvs_handle_t, const char *, const void *, size_t);
esp_err_t nvs_get_str(nvs_handle_t, const char *, char *, size_t *);
esp_err_t nvs_set_str(nvs_handle_t, const char *, const char *);
esp_err_t nvs_get_u8(nvs_handle_t, const char *, uint8_t *);
esp_err_t nvs_set_u8(nvs_handle_t, const char *, uint8_t);
esp_err_t nvs_commit(nvs_handle_t);
esp_err_t nvs_erase_key(nvs_handle_t, const char *);
#endif

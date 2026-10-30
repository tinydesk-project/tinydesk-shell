#include "tdsh_espidf.h"

#include <errno.h>
#include <stdio.h>
#include <string.h>

#include "esp_heap_caps.h"
#include "esp_log.h"
#include "esp_random.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/task.h"
#include "sdkconfig.h"
#include "soc/reg_base.h"
#include "soc/soc.h"
#if CONFIG_SPIRAM
#include "esp_psram.h"
#endif

static const char *TAG = "tdsh-port";

typedef struct
{
    tdsh_worker_fn_t worker;
    tdsh_worker_cleanup_fn_t cleanup;
    void *arg;
    SemaphoreHandle_t done;
    int result;
    bool background;
    char name[20];
    /* the worker inherits the caller's stdio so script
     * output reaches the same terminal (window, SSH session, ...). */
    FILE *std_in, *std_out, *std_err;
} worker_ctx_t;

static uint64_t idf_monotonic_ms(void *ctx)
{
    (void)ctx;
    return (uint64_t)esp_timer_get_time() / 1000ULL;
}

static void idf_sleep_ms(void *ctx, uint32_t ms)
{
    (void)ctx;
    if (ms == 0)
    {
        taskYIELD();
        return;
    }
    TickType_t ticks = pdMS_TO_TICKS(ms);
    if (ticks == 0)
        ticks = 1;
    vTaskDelay(ticks);
}

static void idf_yield(void *ctx)
{
    (void)ctx;
    taskYIELD();
}

static int idf_random_bytes(void *ctx, void *buffer, size_t length)
{
    (void)ctx;
    if (!buffer && length)
        return -EINVAL;
    esp_fill_random(buffer, length);
    return 0;
}

static void *idf_malloc(void *ctx, size_t size)
{
    (void)ctx;
    return heap_caps_malloc(size, MALLOC_CAP_8BIT);
}

static void *idf_calloc(void *ctx, size_t count, size_t size)
{
    (void)ctx;
    return heap_caps_calloc(count, size, MALLOC_CAP_8BIT);
}

static void *idf_realloc(void *ctx, void *ptr, size_t size)
{
    (void)ctx;
    return heap_caps_realloc(ptr, size, MALLOC_CAP_8BIT);
}

static void idf_free(void *ctx, void *ptr)
{
    (void)ctx;
    heap_caps_free(ptr);
}

static void worker_task(void *opaque)
{
    worker_ctx_t *ctx = opaque;
    stdin = ctx->std_in;
    stdout = ctx->std_out;
    stderr = ctx->std_err;
    ctx->result = ctx->worker(ctx->arg);
    if (ctx->cleanup)
        ctx->cleanup(ctx->arg);
    /* Newlib closes a deleted task's stdio when it differs from the global
     * streams; hand the borrowed streams back first. */
    stdin = _REENT_STDIN(_GLOBAL_REENT);
    stdout = _REENT_STDOUT(_GLOBAL_REENT);
    stderr = _REENT_STDERR(_GLOBAL_REENT);

    UBaseType_t free_stack = uxTaskGetStackHighWaterMark(NULL);
    if (free_stack < 4096U)
    {
        ESP_LOGW(TAG, "%s low stack: minimum free=%u bytes",
                 ctx->name, (unsigned)free_stack);
    }
    else
    {
        ESP_LOGD(TAG, "%s minimum free stack=%u bytes",
                 ctx->name, (unsigned)free_stack);
    }

    if (ctx->background)
    {
        ESP_LOGI(TAG, "%s finished status=%d", ctx->name, ctx->result);
        heap_caps_free(ctx);
        vTaskDelete(NULL);
        return;
    }

    xSemaphoreGive(ctx->done);
    vTaskDelete(NULL);
}

static int idf_worker_run(void *context,
                          const char *name,
                          size_t stack_bytes,
                          int priority,
                          bool background,
                          tdsh_worker_fn_t worker,
                          void *arg,
                          tdsh_worker_cleanup_fn_t cleanup,
                          int *result_out)
{
    (void)context;
    if (!worker || stack_bytes == 0)
        return -EINVAL;

    worker_ctx_t *ctx = heap_caps_calloc(1, sizeof(*ctx), MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
    if (!ctx)
        return -ENOMEM;
    ctx->worker = worker;
    ctx->cleanup = cleanup;
    ctx->arg = arg;
    ctx->background = background;
    /* Foreground workers always share the caller's stdio (the caller waits
     * for them). Background workers only do so from the local console, whose
     * streams live forever; an SSH stream is closed when its session ends. */
    bool inherit = !background || tdsh_is_local_console_task();
    ctx->std_in = inherit ? stdin : _REENT_STDIN(_GLOBAL_REENT);
    ctx->std_out = inherit ? stdout : _REENT_STDOUT(_GLOBAL_REENT);
    ctx->std_err = inherit ? stderr : _REENT_STDERR(_GLOBAL_REENT);
    snprintf(ctx->name, sizeof(ctx->name), "%s", name ? name : "tdsh_worker");

    if (!background)
    {
        ctx->done = xSemaphoreCreateBinary();
        if (!ctx->done)
        {
            heap_caps_free(ctx);
            return -ENOMEM;
        }
    }

    BaseType_t ok = xTaskCreate(worker_task,
                                ctx->name,
                                (uint32_t)stack_bytes,
                                ctx,
                                (UBaseType_t)priority,
                                NULL);
    if (ok != pdPASS)
    {
        if (ctx->done)
            vSemaphoreDelete(ctx->done);
        heap_caps_free(ctx);
        return -ENOMEM;
    }

    /* Ownership of arg transferred after successful xTaskCreate. */
    if (background)
        return 0;

    xSemaphoreTake(ctx->done, portMAX_DELAY);
    if (result_out)
        *result_out = ctx->result;
    vSemaphoreDelete(ctx->done);
    heap_caps_free(ctx);
    return 0;
}

/*
 * Memory regions for peek and poke. peek reads RAM, ROM and a few register
 * blocks that are always clocked and have no read side effects: GPIO,
 * IO_MUX and eFuse. poke writes only the GPIO output and output-enable
 * registers (OUT .. ENABLE1_W1TC, the same on all three chips); RAM is read-only
 * because the firmware lives there. A writable window may lie inside a
 * read-only block: peek and poke use whichever region allows the access.
 */
#define GPIO_OUT_FIRST 0x04u /* GPIO_OUT_REG */
#define GPIO_OUT_SIZE  0x34u /* to GPIO_ENABLE1_W1TC_REG (0x34) inclusive */
#define MEM_ALL        (TDSH_MEM_8 | TDSH_MEM_16 | TDSH_MEM_32)
#define MEM_RO         TDSH_MEM_READONLY

#if CONFIG_IDF_TARGET_ESP32
#define MEM_REGIONS 9
static tdsh_mem_region_t s_regions[MEM_REGIONS] = {
    {"gpio_out", DR_REG_GPIO_BASE + GPIO_OUT_FIRST, GPIO_OUT_SIZE, TDSH_MEM_32},
    {"gpio", DR_REG_GPIO_BASE, 0x5D0u, TDSH_MEM_32 | MEM_RO},
    {"io_mux", DR_REG_IO_MUX_BASE, 0x94u, TDSH_MEM_32 | MEM_RO},
    {"efuse", DR_REG_EFUSE_BASE, 0x200u, TDSH_MEM_32 | MEM_RO},
    {"dram", SOC_DRAM_LOW, SOC_DRAM_HIGH - SOC_DRAM_LOW, MEM_ALL | MEM_RO},
    {"rtc_slow", SOC_RTC_DATA_LOW, SOC_RTC_DATA_HIGH - SOC_RTC_DATA_LOW, MEM_ALL | MEM_RO},
    /* The mask ROM twice: its data on the data bus, byte by byte, and all of
     * it on the instruction bus, which takes only 32-bit reads. */
    {"rom_data", SOC_BYTE_ACCESSIBLE_LOW, 0x10000u, MEM_ALL | MEM_RO},
    {"rom", SOC_IROM_MASK_LOW, 0x60000u, TDSH_MEM_32 | MEM_RO},
    {"psram", SOC_EXTRAM_DATA_LOW, 0, MEM_ALL | MEM_RO}, /* size set at run time */
};
#elif CONFIG_IDF_TARGET_ESP32C6
#define MEM_REGIONS 7
static tdsh_mem_region_t s_regions[MEM_REGIONS] = {
    {"gpio_out", DR_REG_GPIO_BASE + GPIO_OUT_FIRST, GPIO_OUT_SIZE, TDSH_MEM_32},
    {"gpio", DR_REG_GPIO_BASE, 0x700u, TDSH_MEM_32 | MEM_RO},
    {"io_mux", DR_REG_IO_MUX_BASE, 0x100u, TDSH_MEM_32 | MEM_RO},
    {"efuse", DR_REG_EFUSE_BASE, 0x200u, TDSH_MEM_32 | MEM_RO},
    {"sram", SOC_DRAM_LOW, SOC_DRAM_HIGH - SOC_DRAM_LOW, MEM_ALL | MEM_RO},
    {"lp_ram", SOC_RTC_DATA_LOW, SOC_RTC_DATA_HIGH - SOC_RTC_DATA_LOW, MEM_ALL | MEM_RO},
    {"rom", SOC_IROM_MASK_LOW, SOC_IROM_MASK_HIGH - SOC_IROM_MASK_LOW, MEM_ALL | MEM_RO},
};
#elif CONFIG_IDF_TARGET_ESP32S3
/* No PSRAM window: the S3 maps external RAM through its MMU at run time. */
#define MEM_REGIONS 7
static tdsh_mem_region_t s_regions[MEM_REGIONS] = {
    {"gpio_out", DR_REG_GPIO_BASE + GPIO_OUT_FIRST, GPIO_OUT_SIZE, TDSH_MEM_32},
    {"gpio", DR_REG_GPIO_BASE, 0x700u, TDSH_MEM_32 | MEM_RO},
    {"io_mux", DR_REG_IO_MUX_BASE, 0x100u, TDSH_MEM_32 | MEM_RO},
    {"efuse", DR_REG_EFUSE_BASE, 0x200u, TDSH_MEM_32 | MEM_RO},
    {"sram", SOC_DRAM_LOW, SOC_DRAM_HIGH - SOC_DRAM_LOW, MEM_ALL | MEM_RO},
    {"rtc_slow", SOC_RTC_DATA_LOW, SOC_RTC_DATA_HIGH - SOC_RTC_DATA_LOW, MEM_ALL | MEM_RO},
    /* The mask ROM on the instruction bus, which takes only 32-bit reads. */
    {"rom", SOC_IROM_MASK_LOW, SOC_IROM_MASK_HIGH - SOC_IROM_MASK_LOW, TDSH_MEM_32 | MEM_RO},
};
#else
#define MEM_REGIONS 0 /* no table for this chip yet: no peek and poke */
#endif

static const tdsh_mem_region_t *idf_mem_regions(void *ctx, size_t *count)
{
    (void)ctx;
#if MEM_REGIONS > 0
#if CONFIG_IDF_TARGET_ESP32 && CONFIG_SPIRAM
    /* External RAM is mapped from 0x3F800000, at most 4 MB. */
    if (esp_psram_is_initialized())
    {
        size_t size = esp_psram_get_size();
        size_t window = SOC_EXTRAM_DATA_HIGH - SOC_EXTRAM_DATA_LOW;
        s_regions[MEM_REGIONS - 1].size = size < window ? size : window;
    }
#endif
    *count = MEM_REGIONS;
    return s_regions;
#else
    *count = 0;
    return NULL;
#endif
}

static const tdsh_platform_api_t s_idf_platform = {
    .name = "esp-idf/freertos",
    .context = NULL,
    .monotonic_ms = idf_monotonic_ms,
    .sleep_ms = idf_sleep_ms,
    .yield = idf_yield,
    .random_bytes = idf_random_bytes,
    .malloc_fn = idf_malloc,
    .calloc_fn = idf_calloc,
    .realloc_fn = idf_realloc,
    .free_fn = idf_free,
    .worker_run = idf_worker_run,
    .mem_regions = idf_mem_regions,
};

const tdsh_platform_api_t *tdsh_espidf_platform(void)
{
    return &s_idf_platform;
}

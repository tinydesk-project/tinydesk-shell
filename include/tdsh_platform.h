#ifndef TDSH_PLATFORM_H
#define TDSH_PLATFORM_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int (*tdsh_worker_fn_t)(void *arg);
typedef void (*tdsh_worker_cleanup_fn_t)(void *arg);

/* Access widths a memory region allows (at least one), and whether poke may
 * write it. */
#define TDSH_MEM_8        (1u << 0)
#define TDSH_MEM_16       (1u << 1)
#define TDSH_MEM_32       (1u << 2)
#define TDSH_MEM_READONLY (1u << 3)

/* A range of the address space that peek and poke may access. */
typedef struct
{
    const char *name; /* shown by peek -l, e.g. "sram" or "gpio" */
    uintptr_t start;
    size_t size; /* bytes */
    uint32_t flags; /* TDSH_MEM_8 | TDSH_MEM_16 | TDSH_MEM_32 | TDSH_MEM_READONLY */
} tdsh_mem_region_t;

typedef struct tdsh_platform_api
{
    const char *name;
    void *context;

    uint64_t (*monotonic_ms)(void *context);
    void (*sleep_ms)(void *context, uint32_t ms);
    void (*yield)(void *context);
    int (*random_bytes)(void *context, void *buffer, size_t length);

    void *(*malloc_fn)(void *context, size_t size);
    void *(*calloc_fn)(void *context, size_t count, size_t size);
    void *(*realloc_fn)(void *context, void *ptr, size_t size);
    void (*free_fn)(void *context, void *ptr);

    /*
     * Execute worker(arg) using a platform-owned thread/task wrapper.
     *
     * background=false: block until completion and write worker status to result_out.
     * background=true: return after successful start; worker/cleanup happen later.
     *
     * Ownership contract:
     * - On return 0, the platform owns arg and MUST call cleanup(arg) exactly once
     *   after worker returns (for foreground or background execution).
     * - On non-zero return, ownership remains with the caller and cleanup MUST NOT
     *   be called by the platform.
     */
    int (*worker_run)(void *context,
                      const char *name,
                      size_t stack_bytes,
                      int priority,
                      bool background,
                      tdsh_worker_fn_t worker,
                      void *arg,
                      tdsh_worker_cleanup_fn_t cleanup,
                      int *result_out);

    /*
     * Optional: the memory regions root may read with peek and write with poke.
     * Return the table and store its length in *count.  The table must stay
     * valid while the shell runs.  Without this hook, or with an empty table
     * when tdsh_register_core_builtins() runs, neither command is registered.
     * List only addresses that are safe to access: leave out registers that
     * change state when read (clear-on-read, FIFOs) and peripherals that may be
     * clock-gated or powered down.  Regions may overlap: an access is allowed
     * when one region allows all of it (a writable window inside a read-only
     * block).
     */
    const tdsh_mem_region_t *(*mem_regions)(void *context, size_t *count);
} tdsh_platform_api_t;

#ifdef __cplusplus
}
#endif

#endif /* TDSH_PLATFORM_H */

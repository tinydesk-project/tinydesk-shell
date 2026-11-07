#include "tdsh_espidf_internal.h"

#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "esp_log.h"
#include "esp_vfs.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "nvs.h"
#include "smb2/libsmb2.h"

#define NETMOUNT_NS              "ush_smb"
#define NETMOUNT_KEY             "db"
#define NETMOUNT_DB_MAGIC        0x554E4D54u
#define NETMOUNT_DB_VERSION      1u
#define NETMOUNT_VFS_BASE        "/net"
#define NETMOUNT_MAX             6
#define NETMOUNT_ACTIVE_MAX      2
#define NETMOUNT_FD_MAX          8
#define NETMOUNT_NAME_MAX        24
#define NETMOUNT_SERVER_MAX      64
#define NETMOUNT_SHARE_MAX       64
#define NETMOUNT_BASE_MAX        128
#define NETMOUNT_SMB_USER_MAX    64
#define NETMOUNT_DOMAIN_MAX      64
#define NETMOUNT_PASSWORD_MAX    96
#define NETMOUNT_TIMEOUT_SECONDS 15

static const char *TAG = "tdsh-smb";

typedef struct
{
    uint8_t used;
    uint8_t persistent;
    char owner[TDSH_USERNAME_MAX];
    char name[NETMOUNT_NAME_MAX];
    char server[NETMOUNT_SERVER_MAX];
    char share[NETMOUNT_SHARE_MAX];
    char base_path[NETMOUNT_BASE_MAX];
    char smb_user[NETMOUNT_SMB_USER_MAX];
    char domain[NETMOUNT_DOMAIN_MAX];
    char password[NETMOUNT_PASSWORD_MAX];
} netmount_cfg_entry_t;

typedef struct
{
    uint32_t magic;
    uint16_t version;
    uint16_t count;
    netmount_cfg_entry_t entries[NETMOUNT_MAX];
} netmount_db_t;

typedef struct
{
    netmount_cfg_entry_t cfg;
    struct smb2_context *ctx;
    SemaphoreHandle_t lock;
    unsigned open_refs;
} netmount_runtime_t;

typedef struct
{
    bool used;
    netmount_runtime_t *mount;
    struct smb2fh *fh;
} netmount_fd_t;

typedef enum
{
    NETDIR_OWNER = 1,
    NETDIR_REMOTE = 2,
} netdir_kind_t;

typedef struct
{
    netdir_kind_t kind;
    netmount_runtime_t *mount;
    struct smb2dir *remote;
    char owner[TDSH_USERNAME_MAX];
    size_t virtual_index;
    struct dirent entry;
} netmount_dir_t;

typedef struct
{
    char owner[TDSH_USERNAME_MAX];
    netmount_runtime_t *mount;
    char remote[TDSH_MAX_PATH * 2];
    bool owner_root;
    bool mount_root;
} resolved_path_t;

static netmount_runtime_t s_mounts[NETMOUNT_MAX];
static netmount_fd_t s_fds[NETMOUNT_FD_MAX];
static SemaphoreHandle_t s_global_lock;
static bool s_initialized;
static unsigned s_active_contexts;

static bool valid_simple_name(const char *name, size_t max_len)
{
    if (!name || !name[0] || strlen(name) >= max_len)
        return false;
    for (const unsigned char *p = (const unsigned char *)name; *p; ++p)
    {
        if (!(isalnum(*p) || *p == '_' || *p == '-' || *p == '.'))
            return false;
    }
    return true;
}

static void copy_field(char *dst, size_t dst_size, const char *src)
{
    if (!dst || dst_size == 0)
        return;
    snprintf(dst, dst_size, "%s", src ? src : "");
}

static void trim_slashes(char *path)
{
    if (!path)
        return;
    while (*path == '/')
        memmove(path, path + 1, strlen(path));
    size_t n = strlen(path);
    while (n > 0 && path[n - 1] == '/')
        path[--n] = '\0';
}

static int neg_to_errno(int rc)
{
    if (rc >= 0)
        return rc;
    errno = -rc;
    if (errno <= 0)
        errno = EIO;
    return -1;
}

static int pointer_failure(struct smb2_context *ctx, int fallback_errno)
{
    /*
     * The ESP-IDF managed libsmb2 3.0.1 public header exposes
     * smb2_get_error(), but not the newer NT-status getter API.
     * Pointer-returning failures therefore keep the detailed SMB error
     * string for diagnostics and use the caller-supplied errno fallback.
     *
     * Integer-returning APIs such as smb2_stat(), smb2_read(), smb2_write()
     * and smb2_ftruncate() already return negative errno values and are
     * handled by neg_to_errno().
     */
    const char *msg = ctx ? smb2_get_error(ctx) : NULL;
    if (msg && msg[0])
        ESP_LOGD(TAG, "SMB error: %s", msg);

    errno = fallback_errno > 0 ? fallback_errno : EIO;
    return -1;
}

static void smb_stat_to_posix(const struct smb2_stat_64 *src, struct stat *dst)
{
    memset(dst, 0, sizeof(*dst));
    if (!src)
        return;
    if (src->smb2_type == SMB2_TYPE_DIRECTORY)
        dst->st_mode = S_IFDIR | 0775;
    else if (src->smb2_type == SMB2_TYPE_LINK)
        dst->st_mode = S_IFLNK | 0777;
    else
        dst->st_mode = S_IFREG | 0664;
    dst->st_nlink = src->smb2_nlink ? src->smb2_nlink : 1;
    dst->st_ino = (ino_t)src->smb2_ino;
    dst->st_size = (off_t)src->smb2_size;
    dst->st_atime = (time_t)src->smb2_atime;
    dst->st_mtime = (time_t)src->smb2_mtime;
    dst->st_ctime = (time_t)src->smb2_ctime;
}

static void virtual_dir_stat(struct stat *st)
{
    memset(st, 0, sizeof(*st));
    st->st_mode = S_IFDIR | 0755;
    st->st_nlink = 1;
}

static int count_persistent(void)
{
    int count = 0;
    for (int i = 0; i < NETMOUNT_MAX; ++i)
    {
        if (s_mounts[i].cfg.used && s_mounts[i].cfg.persistent)
            count++;
    }
    return count;
}

static esp_err_t db_save(void)
{
    /* Keep the persistent SMB database off the caller's stack.
     * netmount_db_t is >3 KB with the current field sizes and tdsh_network_init()
     * runs from app_main(), whose stack is intentionally modest. */
    netmount_db_t *db = calloc(1, sizeof(*db));
    if (!db)
        return ESP_ERR_NO_MEM;

    db->magic = NETMOUNT_DB_MAGIC;
    db->version = NETMOUNT_DB_VERSION;
    db->count = (uint16_t)count_persistent();

    int out = 0;
    for (int i = 0; i < NETMOUNT_MAX && out < NETMOUNT_MAX; ++i)
    {
        if (!s_mounts[i].cfg.used || !s_mounts[i].cfg.persistent)
            continue;
        db->entries[out++] = s_mounts[i].cfg;
    }

    nvs_handle_t h;
    esp_err_t err = nvs_open(NETMOUNT_NS, NVS_READWRITE, &h);
    if (err == ESP_OK)
    {
        err = nvs_set_blob(h, NETMOUNT_KEY, db, sizeof(*db));
        if (err == ESP_OK)
            err = nvs_commit(h);
        nvs_close(h);
    }

    free(db);
    return err;
}

static void mount_runtime_clear(netmount_runtime_t *m)
{
    if (!m)
        return;
    SemaphoreHandle_t lock = m->lock;
    memset(m, 0, sizeof(*m));
    m->lock = lock;
}

static esp_err_t db_load(void)
{
    /* This database is several kilobytes. Allocate it from the heap instead of
     * consuming nearly the whole ESP-IDF main-task stack during boot. */
    netmount_db_t *db = calloc(1, sizeof(*db));
    if (!db)
        return ESP_ERR_NO_MEM;

    nvs_handle_t h;
    esp_err_t err = nvs_open(NETMOUNT_NS, NVS_READWRITE, &h);
    if (err != ESP_OK)
    {
        free(db);
        return err;
    }

    size_t len = sizeof(*db);
    err = nvs_get_blob(h, NETMOUNT_KEY, db, &len);
    nvs_close(h);

    if (err == ESP_ERR_NVS_NOT_FOUND)
    {
        free(db);
        return db_save();
    }
    if (err != ESP_OK)
    {
        free(db);
        return err;
    }
    if (len != sizeof(*db) || db->magic != NETMOUNT_DB_MAGIC ||
        db->version != NETMOUNT_DB_VERSION)
    {
        ESP_LOGW(TAG, "discarding incompatible network-mount database");
        free(db);
        return db_save();
    }

    for (int i = 0; i < NETMOUNT_MAX; ++i)
    {
        if (!db->entries[i].used || !db->entries[i].persistent)
            continue;
        for (int j = 0; j < NETMOUNT_MAX; ++j)
        {
            if (s_mounts[j].cfg.used)
                continue;
            s_mounts[j].cfg = db->entries[i];
            s_mounts[j].cfg.persistent = 1;
            break;
        }
    }

    free(db);
    return ESP_OK;
}

static netmount_runtime_t *find_mount(const char *owner, const char *name)
{
    for (int i = 0; i < NETMOUNT_MAX; ++i)
    {
        if (!s_mounts[i].cfg.used)
            continue;
        if (strcmp(s_mounts[i].cfg.owner, owner) == 0 &&
            strcmp(s_mounts[i].cfg.name, name) == 0)
            return &s_mounts[i];
    }
    return NULL;
}

static netmount_runtime_t *alloc_mount(void)
{
    for (int i = 0; i < NETMOUNT_MAX; ++i)
    {
        if (!s_mounts[i].cfg.used)
            return &s_mounts[i];
    }
    return NULL;
}

static int mount_parent_real_path(const char *owner, char *out, size_t out_size)
{
    if (!owner || !owner[0] || !out || out_size == 0)
        return -EINVAL;
    int n;
    if (strcmp(owner, "root") == 0)
    {
        n = snprintf(out, out_size, "%s/root/mnt", TDSH_MOUNT_POINT);
    }
    else
    {
        n = snprintf(out, out_size, "%s/home/%s/mnt", TDSH_MOUNT_POINT, owner);
    }
    return (n < 0 || (size_t)n >= out_size) ? -ENAMETOOLONG : 0;
}

static int mount_placeholder_real_path(const char *owner, const char *name,
                                       char *out, size_t out_size)
{
    if (!name || !name[0])
        return -EINVAL;
    char parent[TDSH_MAX_PATH + sizeof(TDSH_MOUNT_POINT) + 32];
    int rc = mount_parent_real_path(owner, parent, sizeof(parent));
    if (rc != 0)
        return rc;
    int n = snprintf(out, out_size, "%s/%s", parent, name);
    return (n < 0 || (size_t)n >= out_size) ? -ENAMETOOLONG : 0;
}

/*
 * ~/mnt itself is a real LittleFS directory.  Each network mapping gets one
 * empty LittleFS directory below it purely so normal POSIX directory listing
 * can discover the mount name.  Access to ~/mnt/<name> and anything below it
 * is redirected by tdsh_netmount_translate_logical() to the SMB VFS.
 */
static void make_mount_placeholder(const char *owner, const char *name)
{
    char parent[TDSH_MAX_PATH + sizeof(TDSH_MOUNT_POINT) + 32];
    char path[TDSH_MAX_PATH + sizeof(TDSH_MOUNT_POINT) + NETMOUNT_NAME_MAX + 40];

    if (mount_parent_real_path(owner, parent, sizeof(parent)) != 0 ||
        mount_placeholder_real_path(owner, name, path, sizeof(path)) != 0)
    {
        ESP_LOGW(TAG, "mount placeholder path too long for %s/%s",
                 owner ? owner : "?", name ? name : "?");
        return;
    }

    if (mkdir(parent, 0755) != 0 && errno != EEXIST)
    {
        ESP_LOGW(TAG, "could not create mount parent %s: errno=%d", parent, errno);
        return;
    }
    if (mkdir(path, 0755) != 0 && errno != EEXIST)
    {
        ESP_LOGW(TAG, "could not create mount placeholder %s: errno=%d", path, errno);
    }
}

static void remove_mount_placeholder(const char *owner, const char *name)
{
    char path[TDSH_MAX_PATH + sizeof(TDSH_MOUNT_POINT) + NETMOUNT_NAME_MAX + 40];
    if (mount_placeholder_real_path(owner, name, path, sizeof(path)) != 0)
        return;

    /* A proper placeholder is empty.  rmdir() is deliberately used instead
     * of recursive deletion so an accidental user-created non-empty directory
     * can never be destroyed by netmount cleanup. */
    if (rmdir(path) != 0 && errno != ENOENT && errno != ENOTEMPTY && errno != EEXIST)
    {
        ESP_LOGW(TAG, "could not remove mount placeholder %s: errno=%d", path, errno);
    }
}

static void cleanup_stale_placeholders_for_owner(const char *owner)
{
    char parent[TDSH_MAX_PATH + sizeof(TDSH_MOUNT_POINT) + 32];
    if (mount_parent_real_path(owner, parent, sizeof(parent)) != 0)
        return;

    DIR *dir = opendir(parent);
    if (!dir)
        return;

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;
        if (find_mount(owner, entry->d_name))
            continue;

        char path[TDSH_MAX_PATH + sizeof(TDSH_MOUNT_POINT) + NETMOUNT_NAME_MAX + 40];
        if (mount_placeholder_real_path(owner, entry->d_name, path, sizeof(path)) != 0)
            continue;

        struct stat st;
        if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
        {
            /* Only stale *empty* placeholders are removed. */
            (void)rmdir(path);
        }
    }
    closedir(dir);
}

static void cleanup_stale_placeholders(void)
{
    cleanup_stale_placeholders_for_owner("root");

    char home_root[TDSH_MAX_PATH + sizeof(TDSH_MOUNT_POINT) + 8];
    snprintf(home_root, sizeof(home_root), "%s/home", TDSH_MOUNT_POINT);
    DIR *dir = opendir(home_root);
    if (!dir)
        return;

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;
        if (!valid_simple_name(entry->d_name, TDSH_USERNAME_MAX))
            continue;
        cleanup_stale_placeholders_for_owner(entry->d_name);
    }
    closedir(dir);
}

static int build_remote_path(const char *base, const char *suffix, char *out, size_t out_size)
{
    const char *s = suffix ? suffix : "";
    while (*s == '/')
        s++;
    if (base && base[0])
    {
        if (s[0])
        {
            int n = snprintf(out, out_size, "%s/%s", base, s);
            return (n < 0 || (size_t)n >= out_size) ? -ENAMETOOLONG : 0;
        }
        int n = snprintf(out, out_size, "%s", base);
        return (n < 0 || (size_t)n >= out_size) ? -ENAMETOOLONG : 0;
    }
    int n = snprintf(out, out_size, "%s", s);
    return (n < 0 || (size_t)n >= out_size) ? -ENAMETOOLONG : 0;
}

static int resolve_vfs_path(const char *path, resolved_path_t *out)
{
    if (!path || !out)
    {
        errno = EINVAL;
        return -1;
    }
    memset(out, 0, sizeof(*out));

    char work[TDSH_MAX_PATH * 2];
    const char *src = path;
    while (*src == '/')
        src++;
    if (snprintf(work, sizeof(work), "%s", src) >= (int)sizeof(work))
    {
        errno = ENAMETOOLONG;
        return -1;
    }

    char *save = NULL;
    char *owner = strtok_r(work, "/", &save);
    if (!owner || !owner[0])
    {
        errno = ENOENT;
        return -1;
    }
    copy_field(out->owner, sizeof(out->owner), owner);
    char *name = strtok_r(NULL, "/", &save);
    if (!name)
    {
        out->owner_root = true;
        return 0;
    }

    netmount_runtime_t *m = find_mount(owner, name);
    if (!m)
    {
        errno = ENOENT;
        return -1;
    }
    out->mount = m;

    const char *remaining = save ? save : "";
    if (!remaining[0])
        out->mount_root = true;
    int rc = build_remote_path(m->cfg.base_path, remaining, out->remote, sizeof(out->remote));
    if (rc != 0)
    {
        errno = -rc;
        return -1;
    }
    return 0;
}

static int context_slot_take(void)
{
    if (xSemaphoreTake(s_global_lock, pdMS_TO_TICKS(5000)) != pdTRUE)
    {
        errno = EBUSY;
        return -1;
    }
    if (s_active_contexts >= NETMOUNT_ACTIVE_MAX)
    {
        xSemaphoreGive(s_global_lock);
        errno = EMFILE;
        return -1;
    }
    s_active_contexts++;
    xSemaphoreGive(s_global_lock);
    return 0;
}

static void context_slot_release(void)
{
    if (xSemaphoreTake(s_global_lock, pdMS_TO_TICKS(5000)) == pdTRUE)
    {
        if (s_active_contexts)
            s_active_contexts--;
        xSemaphoreGive(s_global_lock);
    }
}

static int connect_locked(netmount_runtime_t *m)
{
    if (!m)
    {
        errno = ENOENT;
        return -1;
    }
    if (m->ctx)
        return 0;
    if (!tdsh_network_is_online())
    {
        errno = ENETDOWN;
        return -1;
    }
    if (context_slot_take() != 0)
        return -1;

    struct smb2_context *ctx = smb2_init_context();
    if (!ctx)
    {
        context_slot_release();
        errno = ENOMEM;
        return -1;
    }
    smb2_set_timeout(ctx, NETMOUNT_TIMEOUT_SECONDS);
    smb2_set_version(ctx, SMB2_VERSION_ANY);
    smb2_set_user(ctx, m->cfg.smb_user);
    smb2_set_password(ctx, m->cfg.password);
    if (m->cfg.domain[0])
        smb2_set_domain(ctx, m->cfg.domain);

    int rc = smb2_connect_share(ctx, m->cfg.server, m->cfg.share,
                                m->cfg.smb_user[0] ? m->cfg.smb_user : NULL);
    if (rc < 0)
    {
        ESP_LOGW(TAG, "SMB connect %s/%s failed: %s",
                 m->cfg.server, m->cfg.share, smb2_get_error(ctx));
        smb2_destroy_context(ctx);
        context_slot_release();
        errno = -rc;
        if (errno <= 0)
            errno = EIO;
        return -1;
    }
    m->ctx = ctx;
    ESP_LOGI(TAG, "SMB mounted %s/%s for %s as %s",
             m->cfg.server, m->cfg.share, m->cfg.owner, m->cfg.name);
    return 0;
}

static int ensure_connected(netmount_runtime_t *m)
{
    if (!m || !m->lock)
    {
        errno = ENODEV;
        return -1;
    }
    if (xSemaphoreTake(m->lock, pdMS_TO_TICKS(30000)) != pdTRUE)
    {
        errno = EBUSY;
        return -1;
    }
    int rc = connect_locked(m);
    xSemaphoreGive(m->lock);
    return rc;
}

static int disconnect_mount(netmount_runtime_t *m, bool force)
{
    if (!m || !m->lock)
    {
        errno = ENODEV;
        return -1;
    }
    if (xSemaphoreTake(m->lock, pdMS_TO_TICKS(30000)) != pdTRUE)
    {
        errno = EBUSY;
        return -1;
    }
    if (m->open_refs && !force)
    {
        xSemaphoreGive(m->lock);
        errno = EBUSY;
        return -1;
    }
    if (m->ctx)
    {
        (void)smb2_disconnect_share(m->ctx);
        smb2_destroy_context(m->ctx);
        m->ctx = NULL;
        context_slot_release();
    }
    xSemaphoreGive(m->lock);
    return 0;
}

static int fd_alloc(netmount_runtime_t *m, struct smb2fh *fh)
{
    if (xSemaphoreTake(s_global_lock, pdMS_TO_TICKS(5000)) != pdTRUE)
    {
        errno = EBUSY;
        return -1;
    }
    for (int i = 0; i < NETMOUNT_FD_MAX; ++i)
    {
        if (s_fds[i].used)
            continue;
        s_fds[i].used = true;
        s_fds[i].mount = m;
        s_fds[i].fh = fh;
        m->open_refs++;
        xSemaphoreGive(s_global_lock);
        return i;
    }
    xSemaphoreGive(s_global_lock);
    errno = EMFILE;
    return -1;
}

static netmount_fd_t *fd_get(int fd)
{
    if (fd < 0 || fd >= NETMOUNT_FD_MAX || !s_fds[fd].used)
    {
        errno = EBADF;
        return NULL;
    }
    return &s_fds[fd];
}

static void fd_release(int fd)
{
    if (fd < 0 || fd >= NETMOUNT_FD_MAX)
        return;
    if (xSemaphoreTake(s_global_lock, pdMS_TO_TICKS(5000)) != pdTRUE)
        return;
    if (s_fds[fd].used && s_fds[fd].mount && s_fds[fd].mount->open_refs)
    {
        s_fds[fd].mount->open_refs--;
    }
    memset(&s_fds[fd], 0, sizeof(s_fds[fd]));
    xSemaphoreGive(s_global_lock);
}

static int netfs_open(const char *path, int flags, int mode)
{
    (void)mode;
    resolved_path_t r;
    if (resolve_vfs_path(path, &r) != 0)
        return -1;
    if (r.owner_root || r.mount_root)
    {
        errno = EISDIR;
        return -1;
    }
    if (ensure_connected(r.mount) != 0)
        return -1;

    if (xSemaphoreTake(r.mount->lock, pdMS_TO_TICKS(30000)) != pdTRUE)
    {
        errno = EBUSY;
        return -1;
    }
    /*
     * libsmb2 supports the access mode plus O_SYNC/O_CREAT/O_EXCL.
     * O_TRUNC and O_APPEND are handled explicitly below.
     */
    int smb_flags = (flags & O_ACCMODE);
#ifdef O_SYNC
    smb_flags |= (flags & O_SYNC);
#endif
    smb_flags |= (flags & (O_CREAT | O_EXCL));

    struct smb2fh *fh = smb2_open(r.mount->ctx, r.remote, smb_flags);
    if (!fh)
    {
        int ret = pointer_failure(r.mount->ctx, EIO);
        xSemaphoreGive(r.mount->lock);
        return ret;
    }
    if (flags & O_TRUNC)
    {
        int rc = smb2_ftruncate(r.mount->ctx, fh, 0);
        if (rc < 0)
        {
            (void)smb2_close(r.mount->ctx, fh);
            xSemaphoreGive(r.mount->lock);
            return neg_to_errno(rc);
        }
    }
    if (flags & O_APPEND)
    {
        uint64_t current = 0;
        int64_t pos = smb2_lseek(r.mount->ctx, fh, 0, SEEK_END, &current);
        if (pos < 0)
        {
            (void)smb2_close(r.mount->ctx, fh);
            xSemaphoreGive(r.mount->lock);
            errno = (int)-pos;
            return -1;
        }
    }
    xSemaphoreGive(r.mount->lock);

    int fd = fd_alloc(r.mount, fh);
    if (fd < 0)
    {
        if (xSemaphoreTake(r.mount->lock, pdMS_TO_TICKS(30000)) == pdTRUE)
        {
            (void)smb2_close(r.mount->ctx, fh);
            xSemaphoreGive(r.mount->lock);
        }
        return -1;
    }
    return fd;
}

static int netfs_close(int fd)
{
    netmount_fd_t *f = fd_get(fd);
    if (!f)
        return -1;
    netmount_runtime_t *m = f->mount;
    struct smb2fh *fh = f->fh;
    int rc = 0;
    if (xSemaphoreTake(m->lock, pdMS_TO_TICKS(30000)) != pdTRUE)
    {
        errno = EBUSY;
        return -1;
    }
    if (m->ctx && fh)
        rc = smb2_close(m->ctx, fh);
    xSemaphoreGive(m->lock);
    fd_release(fd);
    return rc < 0 ? neg_to_errno(rc) : 0;
}

static ssize_t netfs_read(int fd, void *dst, size_t size)
{
    netmount_fd_t *f = fd_get(fd);
    if (!f)
        return -1;
    netmount_runtime_t *m = f->mount;
    if (xSemaphoreTake(m->lock, pdMS_TO_TICKS(30000)) != pdTRUE)
    {
        errno = EBUSY;
        return -1;
    }
    uint32_t max = m->ctx ? smb2_get_max_read_size(m->ctx) : 0;
    size_t ask = size;
    if (max && ask > max)
        ask = max;
    int rc = m->ctx ? smb2_read(m->ctx, f->fh, (uint8_t *)dst, (uint32_t)ask) : -ENOTCONN;
    xSemaphoreGive(m->lock);
    return rc < 0 ? neg_to_errno(rc) : rc;
}

static ssize_t netfs_write(int fd, const void *src, size_t size)
{
    netmount_fd_t *f = fd_get(fd);
    if (!f)
        return -1;
    netmount_runtime_t *m = f->mount;
    if (xSemaphoreTake(m->lock, pdMS_TO_TICKS(30000)) != pdTRUE)
    {
        errno = EBUSY;
        return -1;
    }
    uint32_t max = m->ctx ? smb2_get_max_write_size(m->ctx) : 0;
    size_t ask = size;
    if (max && ask > max)
        ask = max;
    int rc = m->ctx ? smb2_write(m->ctx, f->fh, (const uint8_t *)src, (uint32_t)ask) : -ENOTCONN;
    xSemaphoreGive(m->lock);
    return rc < 0 ? neg_to_errno(rc) : rc;
}

static off_t netfs_lseek(int fd, off_t offset, int whence)
{
    netmount_fd_t *f = fd_get(fd);
    if (!f)
        return (off_t)-1;
    netmount_runtime_t *m = f->mount;
    if (xSemaphoreTake(m->lock, pdMS_TO_TICKS(30000)) != pdTRUE)
    {
        errno = EBUSY;
        return (off_t)-1;
    }
    uint64_t current = 0;
    int64_t rc = m->ctx ? smb2_lseek(m->ctx, f->fh, offset, whence, &current) : -ENOTCONN;
    xSemaphoreGive(m->lock);
    if (rc < 0)
    {
        errno = (int)-rc;
        return (off_t)-1;
    }
    return (off_t)current;
}

static int netfs_fstat(int fd, struct stat *st)
{
    netmount_fd_t *f = fd_get(fd);
    if (!f || !st)
    {
        if (!st)
            errno = EINVAL;
        return -1;
    }
    netmount_runtime_t *m = f->mount;
    if (xSemaphoreTake(m->lock, pdMS_TO_TICKS(30000)) != pdTRUE)
    {
        errno = EBUSY;
        return -1;
    }
    struct smb2_stat_64 ss;
    int rc = m->ctx ? smb2_fstat(m->ctx, f->fh, &ss) : -ENOTCONN;
    xSemaphoreGive(m->lock);
    if (rc < 0)
        return neg_to_errno(rc);
    smb_stat_to_posix(&ss, st);
    return 0;
}

static int netfs_fsync(int fd)
{
    netmount_fd_t *f = fd_get(fd);
    if (!f)
        return -1;
    netmount_runtime_t *m = f->mount;
    if (xSemaphoreTake(m->lock, pdMS_TO_TICKS(30000)) != pdTRUE)
    {
        errno = EBUSY;
        return -1;
    }
    int rc = m->ctx ? smb2_fsync(m->ctx, f->fh) : -ENOTCONN;
    xSemaphoreGive(m->lock);
    return rc < 0 ? neg_to_errno(rc) : 0;
}

static int netfs_ftruncate(int fd, off_t length)
{
    if (length < 0)
    {
        errno = EINVAL;
        return -1;
    }
    netmount_fd_t *f = fd_get(fd);
    if (!f)
        return -1;
    netmount_runtime_t *m = f->mount;
    if (xSemaphoreTake(m->lock, pdMS_TO_TICKS(30000)) != pdTRUE)
    {
        errno = EBUSY;
        return -1;
    }
    int rc = m->ctx ? smb2_ftruncate(m->ctx, f->fh, (uint64_t)length) : -ENOTCONN;
    xSemaphoreGive(m->lock);
    return rc < 0 ? neg_to_errno(rc) : 0;
}

static int netfs_stat(const char *path, struct stat *st)
{
    if (!st)
    {
        errno = EINVAL;
        return -1;
    }
    resolved_path_t r;
    if (resolve_vfs_path(path, &r) != 0)
        return -1;
    if (r.owner_root || r.mount_root)
    {
        virtual_dir_stat(st);
        return 0;
    }
    if (ensure_connected(r.mount) != 0)
        return -1;
    if (xSemaphoreTake(r.mount->lock, pdMS_TO_TICKS(30000)) != pdTRUE)
    {
        errno = EBUSY;
        return -1;
    }
    struct smb2_stat_64 ss;
    int rc = smb2_stat(r.mount->ctx, r.remote, &ss);
    xSemaphoreGive(r.mount->lock);
    if (rc < 0)
        return neg_to_errno(rc);
    smb_stat_to_posix(&ss, st);
    return 0;
}

static int netfs_unlink(const char *path)
{
    resolved_path_t r;
    if (resolve_vfs_path(path, &r) != 0)
        return -1;
    if (r.owner_root || r.mount_root)
    {
        errno = EPERM;
        return -1;
    }
    if (ensure_connected(r.mount) != 0)
        return -1;
    if (xSemaphoreTake(r.mount->lock, pdMS_TO_TICKS(30000)) != pdTRUE)
    {
        errno = EBUSY;
        return -1;
    }
    int rc = smb2_unlink(r.mount->ctx, r.remote);
    xSemaphoreGive(r.mount->lock);
    return rc < 0 ? neg_to_errno(rc) : 0;
}

static int netfs_mkdir(const char *path, mode_t mode)
{
    (void)mode;
    resolved_path_t r;
    if (resolve_vfs_path(path, &r) != 0)
        return -1;
    if (r.owner_root || r.mount_root)
    {
        errno = EEXIST;
        return -1;
    }
    if (ensure_connected(r.mount) != 0)
        return -1;
    if (xSemaphoreTake(r.mount->lock, pdMS_TO_TICKS(30000)) != pdTRUE)
    {
        errno = EBUSY;
        return -1;
    }
    int rc = smb2_mkdir(r.mount->ctx, r.remote);
    xSemaphoreGive(r.mount->lock);
    return rc < 0 ? neg_to_errno(rc) : 0;
}

static int netfs_rmdir(const char *path)
{
    resolved_path_t r;
    if (resolve_vfs_path(path, &r) != 0)
        return -1;
    if (r.owner_root || r.mount_root)
    {
        errno = EBUSY;
        return -1;
    }
    if (ensure_connected(r.mount) != 0)
        return -1;
    if (xSemaphoreTake(r.mount->lock, pdMS_TO_TICKS(30000)) != pdTRUE)
    {
        errno = EBUSY;
        return -1;
    }
    int rc = smb2_rmdir(r.mount->ctx, r.remote);
    xSemaphoreGive(r.mount->lock);
    return rc < 0 ? neg_to_errno(rc) : 0;
}

static int netfs_rename(const char *src, const char *dst)
{
    resolved_path_t a, b;
    if (resolve_vfs_path(src, &a) != 0 || resolve_vfs_path(dst, &b) != 0)
        return -1;
    if (!a.mount || !b.mount || a.mount != b.mount || a.owner_root || b.owner_root ||
        a.mount_root || b.mount_root)
    {
        errno = EXDEV;
        return -1;
    }
    if (ensure_connected(a.mount) != 0)
        return -1;
    if (xSemaphoreTake(a.mount->lock, pdMS_TO_TICKS(30000)) != pdTRUE)
    {
        errno = EBUSY;
        return -1;
    }
    int rc = smb2_rename(a.mount->ctx, a.remote, b.remote);
    xSemaphoreGive(a.mount->lock);
    return rc < 0 ? neg_to_errno(rc) : 0;
}

static int netfs_truncate(const char *path, off_t length)
{
    if (length < 0)
    {
        errno = EINVAL;
        return -1;
    }
    resolved_path_t r;
    if (resolve_vfs_path(path, &r) != 0)
        return -1;
    if (r.owner_root || r.mount_root)
    {
        errno = EISDIR;
        return -1;
    }
    if (ensure_connected(r.mount) != 0)
        return -1;
    if (xSemaphoreTake(r.mount->lock, pdMS_TO_TICKS(30000)) != pdTRUE)
    {
        errno = EBUSY;
        return -1;
    }
    int rc = smb2_truncate(r.mount->ctx, r.remote, (uint64_t)length);
    xSemaphoreGive(r.mount->lock);
    return rc < 0 ? neg_to_errno(rc) : 0;
}

static int netfs_access(const char *path, int amode)
{
    (void)amode;
    struct stat st;
    return netfs_stat(path, &st);
}

static DIR *netfs_opendir(const char *path)
{
    resolved_path_t r;
    if (resolve_vfs_path(path, &r) != 0)
        return NULL;
    netmount_dir_t *d = calloc(1, sizeof(*d));
    if (!d)
    {
        errno = ENOMEM;
        return NULL;
    }

    if (r.owner_root)
    {
        d->kind = NETDIR_OWNER;
        copy_field(d->owner, sizeof(d->owner), r.owner);
        return (DIR *)d;
    }

    if (ensure_connected(r.mount) != 0)
    {
        free(d);
        return NULL;
    }
    if (xSemaphoreTake(r.mount->lock, pdMS_TO_TICKS(30000)) != pdTRUE)
    {
        free(d);
        errno = EBUSY;
        return NULL;
    }
    struct smb2dir *remote = smb2_opendir(r.mount->ctx, r.remote);
    if (!remote)
    {
        pointer_failure(r.mount->ctx, EIO);
        xSemaphoreGive(r.mount->lock);
        free(d);
        return NULL;
    }
    r.mount->open_refs++;
    xSemaphoreGive(r.mount->lock);
    d->kind = NETDIR_REMOTE;
    d->mount = r.mount;
    d->remote = remote;
    return (DIR *)d;
}

static struct dirent *netfs_readdir(DIR *pdir)
{
    netmount_dir_t *d = (netmount_dir_t *)pdir;
    if (!d)
    {
        errno = EBADF;
        return NULL;
    }
    memset(&d->entry, 0, sizeof(d->entry));

    if (d->kind == NETDIR_OWNER)
    {
        while (d->virtual_index < NETMOUNT_MAX)
        {
            size_t i = d->virtual_index++;
            if (!s_mounts[i].cfg.used || strcmp(s_mounts[i].cfg.owner, d->owner) != 0)
                continue;
            copy_field(d->entry.d_name, sizeof(d->entry.d_name), s_mounts[i].cfg.name);
            d->entry.d_type = DT_DIR;
            return &d->entry;
        }
        return NULL;
    }

    if (!d->mount || !d->remote)
    {
        errno = EBADF;
        return NULL;
    }
    if (xSemaphoreTake(d->mount->lock, pdMS_TO_TICKS(30000)) != pdTRUE)
    {
        errno = EBUSY;
        return NULL;
    }
    struct smb2dirent *ent = d->mount->ctx ? smb2_readdir(d->mount->ctx, d->remote) : NULL;
    if (ent)
    {
        copy_field(d->entry.d_name, sizeof(d->entry.d_name), ent->name);
        d->entry.d_type = ent->st.smb2_type == SMB2_TYPE_DIRECTORY ? DT_DIR : DT_REG;
    }
    xSemaphoreGive(d->mount->lock);
    return ent ? &d->entry : NULL;
}

static int netfs_readdir_r(DIR *pdir, struct dirent *entry, struct dirent **out_dirent)
{
    if (!entry || !out_dirent)
        return EINVAL;
    errno = 0;
    struct dirent *got = netfs_readdir(pdir);
    if (!got)
    {
        *out_dirent = NULL;
        return errno == 0 ? 0 : errno;
    }
    *entry = *got;
    *out_dirent = entry;
    return 0;
}

static long netfs_telldir(DIR *pdir)
{
    netmount_dir_t *d = (netmount_dir_t *)pdir;
    if (!d)
    {
        errno = EBADF;
        return -1;
    }
    if (d->kind == NETDIR_OWNER)
        return (long)d->virtual_index;
    if (!d->mount || !d->remote)
    {
        errno = EBADF;
        return -1;
    }
    if (xSemaphoreTake(d->mount->lock, pdMS_TO_TICKS(30000)) != pdTRUE)
    {
        errno = EBUSY;
        return -1;
    }
    long pos = d->mount->ctx ? smb2_telldir(d->mount->ctx, d->remote) : -1;
    xSemaphoreGive(d->mount->lock);
    return pos;
}

static void netfs_seekdir(DIR *pdir, long offset)
{
    netmount_dir_t *d = (netmount_dir_t *)pdir;
    if (!d || offset < 0)
        return;
    if (d->kind == NETDIR_OWNER)
    {
        d->virtual_index = (size_t)offset;
        if (d->virtual_index > NETMOUNT_MAX)
            d->virtual_index = NETMOUNT_MAX;
        return;
    }
    if (!d->mount || !d->remote)
        return;
    if (xSemaphoreTake(d->mount->lock, pdMS_TO_TICKS(30000)) == pdTRUE)
    {
        if (d->mount->ctx)
            smb2_seekdir(d->mount->ctx, d->remote, offset);
        xSemaphoreGive(d->mount->lock);
    }
}

static int netfs_closedir(DIR *pdir)
{
    netmount_dir_t *d = (netmount_dir_t *)pdir;
    if (!d)
    {
        errno = EBADF;
        return -1;
    }
    if (d->kind == NETDIR_REMOTE && d->mount && d->remote)
    {
        if (xSemaphoreTake(d->mount->lock, pdMS_TO_TICKS(30000)) == pdTRUE)
        {
            if (d->mount->ctx)
                smb2_closedir(d->mount->ctx, d->remote);
            if (d->mount->open_refs)
                d->mount->open_refs--;
            xSemaphoreGive(d->mount->lock);
        }
    }
    free(d);
    return 0;
}

bool tdsh_netmount_translate_logical(const char *logical, char *real_out, size_t real_out_size)
{
    if (!logical || !real_out || real_out_size == 0)
        return false;
    const char *owner = NULL;
    const char *suffix = NULL;
    char owner_buf[TDSH_USERNAME_MAX];

    if (strcmp(logical, "/root/mnt") == 0 || strncmp(logical, "/root/mnt/", 10) == 0)
    {
        owner = "root";
        suffix = logical + strlen("/root/mnt");
    }
    else if (strncmp(logical, "/home/", 6) == 0)
    {
        const char *name = logical + 6;
        const char *slash = strchr(name, '/');
        if (!slash)
            return false;
        size_t n = (size_t)(slash - name);
        if (n == 0 || n >= sizeof(owner_buf) || strncmp(slash, "/mnt", 4) != 0 ||
            (slash[4] != '\0' && slash[4] != '/'))
            return false;
        memcpy(owner_buf, name, n);
        owner_buf[n] = '\0';
        owner = owner_buf;
        suffix = slash + 4;
    }
    else
    {
        return false;
    }

    /* Keep the mount container itself (~/mnt) on LittleFS.  This lets normal
     * opendir()/readdir() enumerate the per-mapping placeholder directories.
     * Only a mount name or a path below it is redirected into /net. */
    if (!suffix || suffix[0] == '\0')
        return false;

    int written = snprintf(real_out, real_out_size, "%s/%s%s", NETMOUNT_VFS_BASE, owner, suffix);
    return written >= 0 && (size_t)written < real_out_size;
}

static int command_connect(netmount_runtime_t *m)
{
    if (!m)
        return 1;
    if (ensure_connected(m) != 0)
    {
        printf("netmount: connect failed: %s\n", strerror(errno));
        return 1;
    }
    printf("%s connected: smb://%s/%s\n", m->cfg.name, m->cfg.server, m->cfg.share);
    return 0;
}

static void print_mount(const netmount_runtime_t *m)
{
    if (!m || !m->cfg.used)
        return;
    printf("%-12s %-10s %-18s %-16s %s\n",
           m->cfg.name,
           m->ctx ? "connected" : "offline",
           m->cfg.server,
           m->cfg.share,
           m->cfg.persistent ? "persistent" : "temporary");
}

static int parse_add_options(tdsh_session_t *session, int argc, char **argv,
                             netmount_cfg_entry_t *cfg)
{
    bool guest = false;
    bool user_explicit = false;
    for (int i = 4; i < argc; ++i)
    {
        if (strcmp(argv[i], "--persistent") == 0)
        {
            cfg->persistent = 1;
        }
        else if (strcmp(argv[i], "--guest") == 0)
        {
            guest = true;
            cfg->smb_user[0] = '\0';
            cfg->password[0] = '\0';
        }
        else if (strcmp(argv[i], "--user") == 0 && i + 1 < argc)
        {
            copy_field(cfg->smb_user, sizeof(cfg->smb_user), argv[++i]);
            user_explicit = true;
        }
        else if (strcmp(argv[i], "--domain") == 0 && i + 1 < argc)
        {
            copy_field(cfg->domain, sizeof(cfg->domain), argv[++i]);
        }
        else
        {
            printf("netmount: unknown/incomplete option: %s\n", argv[i]);
            return 1;
        }
    }

    if (!guest)
    {
        if (!cfg->smb_user[0] && !user_explicit)
        {
            copy_field(cfg->smb_user, sizeof(cfg->smb_user), session->username);
        }
        char password[NETMOUNT_PASSWORD_MAX];
        int n = tdsh_console_readline("SMB password (hidden, Enter for empty): ",
                                      password, sizeof(password), false);
        if (n < 0)
            return 1;
        copy_field(cfg->password, sizeof(cfg->password), password);
        memset(password, 0, sizeof(password));
    }
    return 0;
}

static int command_add(tdsh_session_t *session, int argc, char **argv)
{
    if (argc < 4 || !valid_simple_name(argv[2], NETMOUNT_NAME_MAX))
    {
        printf("usage: netmount add <name> <smb://server/share[/path]> [--user USER] [--domain DOMAIN] [--guest] [--persistent]\n");
        return 2;
    }
    if (find_mount(session->username, argv[2]))
    {
        printf("netmount: mapping '%s' already exists\n", argv[2]);
        return 1;
    }
    netmount_runtime_t *slot = alloc_mount();
    if (!slot)
    {
        printf("netmount: mapping table full (%d maximum)\n", NETMOUNT_MAX);
        return 1;
    }

    struct smb2_context *parser = smb2_init_context();
    if (!parser)
    {
        printf("netmount: out of memory\n");
        return 1;
    }
    struct smb2_url *url = smb2_parse_url(parser, argv[3]);
    if (!url || !url->server || !url->share)
    {
        printf("netmount: invalid SMB URL (use smb://server/share[/path])\n");
        if (url)
            smb2_destroy_url(url);
        smb2_destroy_context(parser);
        return 1;
    }

    netmount_cfg_entry_t cfg;
    memset(&cfg, 0, sizeof(cfg));
    cfg.used = 1;
    copy_field(cfg.owner, sizeof(cfg.owner), session->username);
    copy_field(cfg.name, sizeof(cfg.name), argv[2]);
    copy_field(cfg.server, sizeof(cfg.server), url->server);
    copy_field(cfg.share, sizeof(cfg.share), url->share);
    copy_field(cfg.base_path, sizeof(cfg.base_path), url->path ? url->path : "");
    trim_slashes(cfg.base_path);
    if (url->user && url->user[0])
        copy_field(cfg.smb_user, sizeof(cfg.smb_user), url->user);
    if (url->domain && url->domain[0])
        copy_field(cfg.domain, sizeof(cfg.domain), url->domain);
    smb2_destroy_url(url);
    smb2_destroy_context(parser);

    if (parse_add_options(session, argc, argv, &cfg) != 0)
        return 1;
    slot->cfg = cfg;
    make_mount_placeholder(session->username, cfg.name);

    if (cfg.persistent)
    {
        esp_err_t err = db_save();
        if (err != ESP_OK)
        {
            remove_mount_placeholder(cfg.owner, cfg.name);
            mount_runtime_clear(slot);
            printf("netmount: failed to save mapping: %s\n", esp_err_to_name(err));
            return 1;
        }
        printf("Warning: persistent SMB credentials are stored in NVS. Enable NVS encryption for encrypted-at-rest credentials.\n");
    }

    printf("Mapped ~/mnt/%s -> smb://%s/%s%s%s (%s)\n",
           cfg.name, cfg.server, cfg.share,
           cfg.base_path[0] ? "/" : "", cfg.base_path,
           cfg.persistent ? "persistent" : "temporary");
    if (tdsh_network_is_online())
    {
        (void)command_connect(slot);
    }
    else
    {
        printf("Network is offline; mapping will connect lazily when accessed.\n");
    }
    return 0;
}


void tdsh_netmount_remove_owner(const char *owner)
{
    if (!owner || !owner[0] || !s_initialized)
        return;
    bool persistent_changed = false;
    for (int i = 0; i < NETMOUNT_MAX; ++i)
    {
        netmount_runtime_t *m = &s_mounts[i];
        if (!m->cfg.used || strcmp(m->cfg.owner, owner) != 0)
            continue;
        if (m->cfg.persistent)
            persistent_changed = true;
        char mount_owner[TDSH_USERNAME_MAX];
        char mount_name[NETMOUNT_NAME_MAX];
        copy_field(mount_owner, sizeof(mount_owner), m->cfg.owner);
        copy_field(mount_name, sizeof(mount_name), m->cfg.name);
        (void)disconnect_mount(m, true);
        mount_runtime_clear(m);
        remove_mount_placeholder(mount_owner, mount_name);
    }
    if (persistent_changed)
        (void)db_save();
}

int tdsh_cmd_netmount(tdsh_session_t *session, int argc, char **argv)
{
    if (!session)
        return 1;
    if (argc == 1 || (argc == 2 && strcmp(argv[1], "list") == 0))
    {
        printf("NAME         STATUS     SERVER             SHARE            TYPE\n");
        bool any = false;
        for (int i = 0; i < NETMOUNT_MAX; ++i)
        {
            if (!s_mounts[i].cfg.used || strcmp(s_mounts[i].cfg.owner, session->username) != 0)
                continue;
            print_mount(&s_mounts[i]);
            any = true;
        }
        if (!any)
            printf("(no mappings for %s)\n", session->username);
        return 0;
    }
    if (strcmp(argv[1], "add") == 0)
        return command_add(session, argc, argv);

    if (argc >= 3 && (strcmp(argv[1], "connect") == 0 || strcmp(argv[1], "disconnect") == 0 ||
                      strcmp(argv[1], "remove") == 0 || strcmp(argv[1], "status") == 0))
    {
        netmount_runtime_t *m = find_mount(session->username, argv[2]);
        if (!m)
        {
            printf("netmount: no such mapping: %s\n", argv[2]);
            return 1;
        }
        if (strcmp(argv[1], "connect") == 0)
            return command_connect(m);
        if (strcmp(argv[1], "disconnect") == 0)
        {
            if (disconnect_mount(m, false) != 0)
            {
                printf("netmount: disconnect failed: %s\n", strerror(errno));
                return 1;
            }
            printf("%s disconnected.\n", m->cfg.name);
            return 0;
        }
        if (strcmp(argv[1], "status") == 0)
        {
            printf("Name:       %s\n", m->cfg.name);
            printf("Path:       ~/mnt/%s\n", m->cfg.name);
            printf("Remote:     smb://%s/%s%s%s\n", m->cfg.server, m->cfg.share,
                   m->cfg.base_path[0] ? "/" : "", m->cfg.base_path);
            printf("User:       %s\n", m->cfg.smb_user[0] ? m->cfg.smb_user : "guest/anonymous");
            printf("Domain:     %s\n", m->cfg.domain[0] ? m->cfg.domain : "-");
            printf("Persistent: %s\n", m->cfg.persistent ? "yes" : "no");
            printf("Connected:  %s\n", m->ctx ? "yes" : "no");
            printf("Open refs:  %u\n", m->open_refs);
            return 0;
        }
        if (strcmp(argv[1], "remove") == 0)
        {
            if (disconnect_mount(m, false) != 0)
            {
                printf("netmount: remove failed: %s\n", strerror(errno));
                return 1;
            }
            bool was_persistent = m->cfg.persistent;
            char mount_owner[TDSH_USERNAME_MAX];
            char mount_name[NETMOUNT_NAME_MAX];
            copy_field(mount_owner, sizeof(mount_owner), m->cfg.owner);
            copy_field(mount_name, sizeof(mount_name), m->cfg.name);
            mount_runtime_clear(m);
            remove_mount_placeholder(mount_owner, mount_name);
            if (was_persistent && db_save() != ESP_OK)
            {
                printf("netmount: mapping removed from RAM but NVS update failed\n");
                return 1;
            }
            printf("Mapping removed.\n");
            return 0;
        }
    }

    printf("usage:\n");
    printf("  netmount list\n");
    printf("  netmount add <name> <smb://server/share[/path]> [--user USER] [--domain DOMAIN] [--guest] [--persistent]\n");
    printf("  netmount connect <name>\n");
    printf("  netmount disconnect <name>\n");
    printf("  netmount status <name>\n");
    printf("  netmount remove <name>\n");
    return 2;
}

esp_err_t tdsh_netmount_init(void)
{
    if (s_initialized)
        return ESP_OK;
    s_global_lock = xSemaphoreCreateMutex();
    if (!s_global_lock)
        return ESP_ERR_NO_MEM;
    for (int i = 0; i < NETMOUNT_MAX; ++i)
    {
        s_mounts[i].lock = xSemaphoreCreateMutex();
        if (!s_mounts[i].lock)
            return ESP_ERR_NO_MEM;
    }

    esp_vfs_t vfs = {
        .flags = ESP_VFS_FLAG_DEFAULT,
        .write = netfs_write,
        .lseek = netfs_lseek,
        .read = netfs_read,
        .open = netfs_open,
        .close = netfs_close,
        .fstat = netfs_fstat,
#ifdef CONFIG_VFS_SUPPORT_DIR
        .stat = netfs_stat,
        .unlink = netfs_unlink,
        .rename = netfs_rename,
        .opendir = netfs_opendir,
        .readdir = netfs_readdir,
        .readdir_r = netfs_readdir_r,
        .telldir = netfs_telldir,
        .seekdir = netfs_seekdir,
        .closedir = netfs_closedir,
        .mkdir = netfs_mkdir,
        .rmdir = netfs_rmdir,
#endif
        .fsync = netfs_fsync,
#ifdef CONFIG_VFS_SUPPORT_DIR
        .access = netfs_access,
        .truncate = netfs_truncate,
        .ftruncate = netfs_ftruncate,
#endif
    };
    esp_err_t err = esp_vfs_register(NETMOUNT_VFS_BASE, &vfs, NULL);
    if (err != ESP_OK)
        return err;
    err = db_load();
    if (err != ESP_OK)
        return err;

    /* Remove empty placeholders left by temporary mappings from an earlier
     * boot, then recreate placeholders for the mappings that actually exist. */
    cleanup_stale_placeholders();
    for (int i = 0; i < NETMOUNT_MAX; ++i)
    {
        if (s_mounts[i].cfg.used)
        {
            make_mount_placeholder(s_mounts[i].cfg.owner, s_mounts[i].cfg.name);
        }
    }
    s_initialized = true;
    ESP_LOGI(TAG, "SMB2/SMB3 VFS registered at %s (%d mappings, %d active max)",
             NETMOUNT_VFS_BASE, NETMOUNT_MAX, NETMOUNT_ACTIVE_MAX);
    return ESP_OK;
}

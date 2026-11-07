#include "tdsh_espidf_internal.h"

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>

#include "esp_log.h"
#include "esp_random.h"
#include "mbedtls/md.h"
#include "nvs.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

#define USER_NS         "ush_users"
#define USER_KEY        "db"
#define BOOT_USER_KEY   "boot_user"
#define USER_DB_MAGIC   0x55534855u
#define USER_DB_VERSION 1u
#define USER_MAX        12
#define USER_SALT_LEN   16
#define USER_HASH_LEN   32
#define HASH_ROUNDS     2048

static SemaphoreHandle_t s_users_mutex;
typedef struct
{
    bool locked;
} users_guard_t;
static void users_unguard(users_guard_t *guard)
{
    if (guard->locked)
        xSemaphoreGiveRecursive(s_users_mutex);
}
#define USERS_GUARD users_guard_t guard __attribute__((cleanup(users_unguard))) = {s_users_mutex && xSemaphoreTakeRecursive(s_users_mutex, portMAX_DELAY) == pdTRUE}

static const char *TAG = "tdsh-users";
static void hint_forget(const char *name);   /* tdsh_users_hint.inc */

/* The factory password root gets on a fresh device (change it with passwd). */
#define DEFAULT_ROOT_PASSWORD TDSH_FACTORY_ROOT_PASSWORD

typedef struct
{
    uint8_t used;
    char name[TDSH_USERNAME_MAX];
    uint8_t salt[USER_SALT_LEN];
    uint8_t hash[USER_HASH_LEN];
} user_entry_t;

typedef struct
{
    uint32_t magic;
    uint16_t version;
    uint16_t count;
    user_entry_t entries[USER_MAX];
} user_db_t;

static user_db_t s_db;
static bool s_ready;
static uint8_t s_roles[USER_MAX];
static uint32_t s_rights[USER_MAX];
static bool s_verified[USER_MAX];
static void access_load(void);
static esp_err_t access_save(nvs_handle_t handle);
static void remember_verified(const char *username);
static bool access_can_manage(const char *actor, const char *name);


static void ensure_user_startup_file(const char *username)
{
    if (!username || !username[0])
        return;
    char dir[TDSH_MAX_PATH + sizeof(TDSH_MOUNT_POINT) + 16];
    char path[TDSH_MAX_PATH + sizeof(TDSH_MOUNT_POINT) + 32];
    if (strcmp(username, "root") == 0)
    {
        snprintf(dir, sizeof(dir), "%s/root", TDSH_MOUNT_POINT);
    }
    else
    {
        snprintf(dir, sizeof(dir), "%s/home/%s", TDSH_MOUNT_POINT, username);
    }
    (void)mkdir(dir, 0755);
    char mnt_dir[TDSH_MAX_PATH + sizeof(TDSH_MOUNT_POINT) + 24];
    snprintf(mnt_dir, sizeof(mnt_dir), "%s/mnt", dir);
    (void)mkdir(mnt_dir, 0755);
    snprintf(path, sizeof(path), "%s/" TDSH_STARTUP_FILE, dir);
    struct stat st;
    if (stat(path, &st) == 0)
        return;
    FILE *f = fopen(path, "w");
    if (!f)
        return;
    /* wording that fits every board and console. */
    fprintf(f, "# Startup script of %s: runs when %s's local shell starts\n", username, username);
    fprintf(f, "# (the console, or the desktop's Terminal window). One command per line,\n");
    fprintf(f, "# e.g. wificonnect to join the saved Wi-Fi network at boot.\n");
    fclose(f);
}

int tdsh_boot_user_get(char *out, size_t out_size)
{
    USERS_GUARD;
    if (!out || out_size < 2)
        return -EINVAL;
    out[0] = '\0';
    nvs_handle_t h;
    esp_err_t err = nvs_open(USER_NS, NVS_READONLY, &h);
    if (err != ESP_OK)
        return -ENOENT;
    size_t len = out_size;
    err = nvs_get_str(h, BOOT_USER_KEY, out, &len);
    nvs_close(h);
    if (err != ESP_OK || out[0] == '\0' || !tdsh_user_exists(out))
    {
        out[0] = '\0';
        return -ENOENT;
    }
    return 0;
}

static int boot_user_write(const char *username, bool remember)
{
    USERS_GUARD;
    if (!username || !username[0] || !tdsh_user_exists(username))
        return -EINVAL;
    nvs_handle_t h;
    esp_err_t err = nvs_open(USER_NS, NVS_READWRITE, &h);
    if (err != ESP_OK)
        return -EIO;
    char previous[TDSH_USERNAME_MAX];
    size_t length = sizeof(previous);
    bool same = nvs_get_str(h, BOOT_USER_KEY, previous, &length) == ESP_OK && !strcmp(previous, username);
    if (!remember || !same)
    {
        err = nvs_set_u8(h, "remember", 0);
        if (err == ESP_OK)
        {
            esp_err_t erased = nvs_erase_key(h, "proof");
            if (erased != ESP_OK && erased != ESP_ERR_NVS_NOT_FOUND)
                err = erased;
        }
    }
    if (err == ESP_OK)
        err = nvs_set_str(h, BOOT_USER_KEY, username);
    if (err == ESP_OK)
        err = nvs_set_u8(h, "remember", remember ? 1 : 0);
    if (err == ESP_OK)
        err = nvs_commit(h);
    nvs_close(h);
    if (err == ESP_OK && remember)
        remember_verified(username);
    return err == ESP_OK ? 0 : -EIO;
}
int tdsh_boot_user_set(const char *username)
{
    return boot_user_write(username, true);
}
/* Choosing a fallback console identity must not opt a new device into
 * remembered desktop login without the owner's explicit choice. */
int tdsh_boot_user_default(const char *username)
{
    return boot_user_write(username, false);
}

static bool valid_username(const char *name)
{
    if (!name || !name[0] || !strcmp(name, ".") || !strcmp(name, "..") || strlen(name) >= TDSH_USERNAME_MAX)
        return false;
    for (const unsigned char *p = (const unsigned char *)name; *p; ++p)
    {
        if (!((*p >= 'a' && *p <= 'z') || (*p >= 'A' && *p <= 'Z') || (*p >= '0' && *p <= '9') || *p == '_' || *p == '-' || *p == '.'))
            return false;
    }
    return true;
}

static int find_user(const char *name)
{
    if (!name)
        return -1;
    for (int i = 0; i < USER_MAX; ++i)
    {
        if (s_db.entries[i].used && strcmp(s_db.entries[i].name, name) == 0)
            return i;
    }
    return -1;
}

static esp_err_t save_db(void)
{
    nvs_handle_t h;
    esp_err_t err = nvs_open(USER_NS, NVS_READWRITE, &h);
    if (err != ESP_OK)
        return err;
    err = access_save(h);
    if (err == ESP_OK)
        err = nvs_set_blob(h, USER_KEY, &s_db, sizeof(s_db));
    if (err == ESP_OK)
        err = nvs_commit(h);
    nvs_close(h);
    return err;
}

static int sha256(const void *data, size_t len, uint8_t out[USER_HASH_LEN])
{
    const mbedtls_md_info_t *info = mbedtls_md_info_from_type(MBEDTLS_MD_SHA256);
    if (!info)
        return -1;
    return mbedtls_md(info, (const unsigned char *)data, len, out);
}

static int make_hash(const char *password, const uint8_t salt[USER_SALT_LEN], uint8_t out[USER_HASH_LEN])
{
    if (!password)
        return -1;
    size_t plen = strlen(password);
    if (plen > 128)
        return -1;

    uint8_t initial[USER_SALT_LEN + 128];
    memcpy(initial, salt, USER_SALT_LEN);
    memcpy(initial + USER_SALT_LEN, password, plen);
    if (sha256(initial, USER_SALT_LEN + plen, out) != 0)
        return -1;

    uint8_t round_buf[USER_HASH_LEN + USER_SALT_LEN];
    for (unsigned i = 1; i < HASH_ROUNDS; ++i)
    {
        memcpy(round_buf, out, USER_HASH_LEN);
        memcpy(round_buf + USER_HASH_LEN, salt, USER_SALT_LEN);
        if (sha256(round_buf, sizeof(round_buf), out) != 0)
            return -1;
    }
    return 0;
}

static bool hash_equal(const uint8_t *a, const uint8_t *b, size_t n)
{
    uint8_t diff = 0;
    for (size_t i = 0; i < n; ++i)
        diff |= a[i] ^ b[i];
    return diff == 0;
}

static esp_err_t set_password_idx(int idx, const char *password)
{
    USERS_GUARD;
    if (idx < 0 || idx >= USER_MAX || !password || strlen(password) < 1)
        return ESP_ERR_INVALID_ARG;
    user_entry_t old = s_db.entries[idx];
    esp_fill_random(s_db.entries[idx].salt, USER_SALT_LEN);
    if (make_hash(password, s_db.entries[idx].salt, s_db.entries[idx].hash) != 0)
    {
        s_db.entries[idx] = old;
        return ESP_FAIL;
    }
    esp_err_t result = save_db();
    if (result != ESP_OK)
        s_db.entries[idx] = old;
    else
        s_verified[idx] = false;
    return result;
}

static bool check_password(int idx, const char *password)
{
    uint8_t hash[USER_HASH_LEN];
    if (make_hash(password, s_db.entries[idx].salt, hash) != 0)
        return false;
    return hash_equal(hash, s_db.entries[idx].hash, USER_HASH_LEN);
}

esp_err_t tdsh_users_init(void)
{
    if (s_ready)
        return ESP_OK;
    if (!s_users_mutex)
        s_users_mutex = xSemaphoreCreateRecursiveMutex();
    if (!s_users_mutex)
        return ESP_ERR_NO_MEM;
    memset(&s_db, 0, sizeof(s_db));

    nvs_handle_t h;
    esp_err_t err = nvs_open(USER_NS, NVS_READWRITE, &h);
    if (err != ESP_OK)
        return err;
    size_t len = sizeof(s_db);
    err = nvs_get_blob(h, USER_KEY, &s_db, &len);
    nvs_close(h);

    if (err != ESP_ERR_NVS_NOT_FOUND && (err != ESP_OK || len != sizeof(s_db) || s_db.magic != USER_DB_MAGIC || s_db.version != USER_DB_VERSION))
        return ESP_ERR_INVALID_STATE;
    memset(s_roles, 0, sizeof(s_roles));
    memset(s_verified, 0, sizeof(s_verified));
    for (int i = 0; i < USER_MAX; i++)
        s_rights[i] = TDSH_RIGHTS_USER;
    if (err == ESP_ERR_NVS_NOT_FOUND)
    {
        memset(&s_db, 0, sizeof(s_db));
        s_db.magic = USER_DB_MAGIC;
        s_db.version = USER_DB_VERSION;
        s_db.entries[0].used = 1;
        snprintf(s_db.entries[0].name, sizeof(s_db.entries[0].name), "root");
        s_db.count = 1;
        esp_fill_random(s_db.entries[0].salt, USER_SALT_LEN);
        if (make_hash(DEFAULT_ROOT_PASSWORD, s_db.entries[0].salt, s_db.entries[0].hash) != 0)
            return ESP_FAIL;
        err = save_db();
        if (err != ESP_OK)
            return err;
        ESP_LOGW(TAG, "Created root user with the factory password '" DEFAULT_ROOT_PASSWORD "'; change it with passwd");
    }

    for (int i = 0; i < USER_MAX; i++)
        if (s_db.entries[i].used && (!memchr(s_db.entries[i].name, 0, TDSH_USERNAME_MAX) || !valid_username(s_db.entries[i].name)))
            return ESP_ERR_INVALID_STATE;
    unsigned used = 0;
    bool root_found = false;
    for (int i = 0; i < USER_MAX; i++)
        if (s_db.entries[i].used)
        {
            if (s_db.entries[i].used != 1)
                return ESP_ERR_INVALID_STATE;
            used++;
            if (!strcmp(s_db.entries[i].name, "root"))
                root_found = true;
            for (int j = 0; j < i; j++)
                if (s_db.entries[j].used && !strcmp(s_db.entries[i].name, s_db.entries[j].name))
                    return ESP_ERR_INVALID_STATE;
        }
    if (!root_found || used != s_db.count)
        return ESP_ERR_INVALID_STATE;
    access_load();
    (void)mkdir(TDSH_MOUNT_POINT "/shared", 0755);
    s_ready = true;
    for (int i = 0; i < USER_MAX; ++i)
    {
        if (s_db.entries[i].used)
            ensure_user_startup_file(s_db.entries[i].name);
    }
    return ESP_OK;
}

bool tdsh_user_exists(const char *username)
{
    USERS_GUARD;
    return s_ready && find_user(username) >= 0;
}

bool tdsh_user_authenticate(const char *username, const char *password)
{
    USERS_GUARD;
    if (!s_ready)
        return false;
    int idx = find_user(username);
    if (idx < 0 || !password)
        return false;
    return check_password(idx, password);
}

bool tdsh_remote_access_ready(void)
{
    USERS_GUARD;
    int idx = find_user("root");
    uint8_t hash[USER_HASH_LEN];
    if (!s_ready || idx < 0 ||
        make_hash(DEFAULT_ROOT_PASSWORD, s_db.entries[idx].salt, hash) != 0)
        return false;
    return !hash_equal(hash, s_db.entries[idx].hash, USER_HASH_LEN);
}

bool tdsh_user_authenticate_remote(const char *username, const char *password)
{
    return tdsh_remote_access_ready() && tdsh_user_authenticate(username, password);
}

static int read_password(const char *prompt, char *out, size_t out_size)
{
    int n = tdsh_console_readline(prompt, out, out_size, false);
    if (n <= 0)
        return 1;
    return 0;
}

static int remove_tree(const char *path)
{
    struct stat st;
    if (stat(path, &st) != 0)
        return errno == ENOENT ? 0 : -errno;
    if (!S_ISDIR(st.st_mode))
        return unlink(path) == 0 ? 0 : -errno;
    DIR *d = opendir(path);
    if (!d)
        return -errno;
    struct dirent *e;
    int rc = 0;
    while ((e = readdir(d)) != NULL)
    {
        if (!strcmp(e->d_name, ".") || !strcmp(e->d_name, ".."))
            continue;
        char child[TDSH_MAX_PATH + sizeof(TDSH_MOUNT_POINT) + 64];
        int n = snprintf(child, sizeof(child), "%s/%s", path, e->d_name);
        if (n < 0 || n >= (int)sizeof(child))
        {
            rc = -ENAMETOOLONG;
            break;
        }
        rc = remove_tree(child);
        if (rc != 0)
            break;
    }
    closedir(d);
    if (rc == 0 && rmdir(path) != 0)
        rc = -errno;
    return rc;
}

int tdsh_cmd_users(tdsh_session_t *session, int argc, char **argv)
{
    USERS_GUARD;
    (void)session;
    (void)argc;
    (void)argv;
    for (int i = 0; i < USER_MAX; ++i)
        if (s_db.entries[i].used)
            printf("%s\n", s_db.entries[i].name);
    return 0;
}

int tdsh_cmd_useradd(tdsh_session_t *session, int argc, char **argv)
{
    if (argc < 2 || argc > 3 || !valid_username(argv[1]))
    {
        printf("usage: useradd <username> [admin|user]\n");
        return 2;
    }
    if (tdsh_session_role(session) < TDSH_ROLE_ADMIN || !tdsh_session_has_right(session, TDSH_RIGHT_USERS))
    {
        printf("tdsh: administrator required\n");
        return 1;
    }
    tdsh_role_t role = argc == 3 && !strcmp(argv[2], "admin") ? TDSH_ROLE_ADMIN : TDSH_ROLE_USER;
    if (argc == 3 && strcmp(argv[2], "admin") && strcmp(argv[2], "user"))
        return 2;
    char p1[129] = {0}, p2[129] = {0};
    int rc = 1;
    if (!read_password("New password: ", p1, sizeof(p1)) && !read_password("Retype new password: ", p2, sizeof(p2)) && !strcmp(p1, p2))
    {
        uint32_t rights = (role == TDSH_ROLE_ADMIN ? TDSH_RIGHTS_ADMIN : TDSH_RIGHTS_USER) & tdsh_session_rights(session);
        rc = tdsh_user_create(session->username, argv[1], p1, role, rights);
        char hint[TDSH_HINT_MAX] = {0};
        if (!rc && tdsh_console_readline("Password hint (optional, shown at Sign in): ", hint, sizeof(hint), true) > 0)
        {
            if (tdsh_hint_reveals(hint, p1))
                printf("useradd: the hint contains the password; no hint saved.\n");
            else if (tdsh_user_hint_set(session->username, argv[1], hint))
                printf("useradd: hint not saved.\n");
        }
    }
    volatile char *a = p1, *b = p2;
    for (unsigned i = 0; i < sizeof(p1); i++)
        a[i] = b[i] = 0;
    if (rc)
        printf("useradd: account not created (%d)\n", rc);
    else
        printf("Created %s (%s).\n", argv[1], role == TDSH_ROLE_ADMIN ? "admin" : "user");
    return rc ? 1 : 0;
}

int tdsh_cmd_userdel(tdsh_session_t *session, int argc, char **argv)
{
    if (argc < 2 || !access_can_manage(session->username, argv[1]))
    {
        printf("tdsh: permission denied: root required\n");
        return 1;
    }
    if (argc < 2 || argc > 3 || (argc == 3 && strcmp(argv[2], "-f")))
    {
        printf("usage: userdel <username> [-f]\n");
        return 2;
    }
    if (!strcmp(argv[1], "root"))
    {
        printf("tdsh: root user cannot be deleted\n");
        return 1;
    }
    int idx = find_user(argv[1]);
    if (idx < 0)
    {
        printf("tdsh: no user named '%s'\n", argv[1]);
        return 1;
    }

    bool force = argc == 3 && strcmp(argv[2], "-f") == 0;
    if (!force)
    {
        char pass[129] = {0};
        bool ok = !read_password("Password for user being deleted: ", pass, sizeof(pass)) && tdsh_user_authenticate(argv[1], pass);
        volatile char *wipe = pass;
        for (unsigned i = 0; i < sizeof(pass); i++)
            wipe[i] = 0;
        if (!ok)
        {
            printf("Incorrect password.\n");
            return 1;
        }
    }

    USERS_GUARD;
    idx = find_user(argv[1]);
    if (idx < 0 || !access_can_manage(session->username, argv[1]))
        return 1;
    user_entry_t old = s_db.entries[idx];
    uint8_t old_role = s_roles[idx];
    uint32_t old_rights = s_rights[idx];
    memset(&s_db.entries[idx], 0, sizeof(s_db.entries[idx]));
    s_roles[idx] = TDSH_ROLE_USER;
    s_rights[idx] = TDSH_RIGHTS_USER;
    if (s_db.count)
        s_db.count--;
    if (save_db() != ESP_OK)
    {
        s_db.entries[idx] = old;
        s_roles[idx] = old_role;
        s_rights[idx] = old_rights;
        s_db.count++;
        printf("tdsh: failed to update user database\n");
        return 1;
    }
    s_verified[idx] = false;
    hint_forget(argv[1]);
    /* Keep removal and name reuse serialized with account creation. */
    tdsh_netmount_remove_owner(argv[1]);
    char home[TDSH_MAX_PATH + sizeof(TDSH_MOUNT_POINT) + 8];
    snprintf(home, sizeof(home), "%s/home/%s", TDSH_MOUNT_POINT, argv[1]);
    (void)remove_tree(home);
    printf("User %s deleted successfully.\n", argv[1]);
    return 0;
}

int tdsh_cmd_login(tdsh_session_t *session, int argc, char **argv)
{
    if (!session->interactive)
    {
        printf("tdsh: login requires an interactive shell\n");
        return 1;
    }
    if (argc != 2)
    {
        printf("usage: login <username>\n");
        return 2;
    }
    if (!tdsh_user_exists(argv[1]))
    {
        printf("No user found named '%s'.\n", argv[1]);
        return 1;
    }
    char pass[129] = {0};
    if (read_password("Password: ", pass, sizeof(pass)))
        return 1;
    uint32_t generation = tdsh_user_login(argv[1], pass);
    volatile char *wipe = pass;
    for (unsigned i = 0; i < sizeof(pass); i++)
        wipe[i] = 0;
    if (!generation)
    {
        printf("Incorrect password.\n");
        return 1;
    }
    if (tdsh_session_set_user_generation(session, argv[1], generation) != 0)
        return 1;
    printf("Login successful.\n");
    if (tdsh_is_local_console_task())
    {
        (void)tdsh_run_user_startup(session);
    }
    return 0;
}

int tdsh_cmd_logout(tdsh_session_t *session, int argc, char **argv)
{
    (void)argv;
    if (!session->interactive)
    {
        printf("tdsh: logout requires an interactive shell\n");
        return 1;
    }
    if (argc != 1)
    {
        printf("usage: logout\n");
        return 2;
    }
    session->logout_requested = true;
    printf("Logged out.\n");
    return 0;
}

int tdsh_cmd_passwd(tdsh_session_t *session, int argc, char **argv)
{
    (void)argc;
    (void)argv;
    if (!session->interactive)
    {
        printf("tdsh: passwd requires an interactive shell\n");
        return 1;
    }
    int idx = find_user(session->username);
    if (idx < 0)
        return 1;
    char oldp[129], p1[129], p2[129];
    if (strcmp(session->username, "root") == 0 && tdsh_user_authenticate("root", DEFAULT_ROOT_PASSWORD))
    {
        printf("root still has the factory password, " DEFAULT_ROOT_PASSWORD
               " (capital T and D): type it as the old password.\n");
    }
    if (read_password("Old password: ", oldp, sizeof(oldp)))
        return 1;
    if (!tdsh_user_authenticate(session->username, oldp))
    {
        printf("Incorrect old password.\n");
        return 1;
    }
    if (read_password("New password: ", p1, sizeof(p1)) || read_password("Retype new password: ", p2, sizeof(p2)))
        return 1;
    if (strcmp(p1, p2) != 0)
    {
        printf("Passwords do not match.\n");
        return 1;
    }
    if (tdsh_user_password_set(session->username, session->username, oldp, p1) != 0)
    {
        printf("tdsh: failed to save password\n");
        return 1;
    }
    printf("Password updated.\n");
    char hint[TDSH_HINT_MAX] = {0};
    if (tdsh_console_readline("Password hint (Enter: keep it, -: remove it): ", hint, sizeof(hint), true) > 0)
    {
        if (!strcmp(hint, "-"))
            hint[0] = 0;
        if (tdsh_hint_reveals(hint, p1))
            printf("The hint contains the password; the old hint is kept.\n");
        else if (tdsh_user_hint_set(session->username, session->username, hint))
            printf("tdsh: failed to save the hint\n");
    }
    return 0;
}


static int recover_root_password(void)
{
    int root_idx = find_user("root");
    if (root_idx < 0)
    {
        printf("rootrecover: root account is missing\n");
        return 1;
    }

    char p1[129];
    char p2[129];
    printf("Physical USB Serial/JTAG root password recovery.\n");
    if (read_password("New root password: ", p1, sizeof(p1)) ||
        read_password("Retype new root password: ", p2, sizeof(p2)))
    {
        memset(p1, 0, sizeof(p1));
        memset(p2, 0, sizeof(p2));
        return 1;
    }
    if (strlen(p1) < 8)
    {
        printf("rootrecover: password must be at least 8 characters\n");
        memset(p1, 0, sizeof(p1));
        memset(p2, 0, sizeof(p2));
        return 1;
    }
    if (strcmp(p1, p2) != 0)
    {
        printf("Passwords do not match.\n");
        memset(p1, 0, sizeof(p1));
        memset(p2, 0, sizeof(p2));
        return 1;
    }

    esp_err_t err = set_password_idx(root_idx, p1);
    memset(p1, 0, sizeof(p1));
    memset(p2, 0, sizeof(p2));
    if (err != ESP_OK)
    {
        printf("rootrecover: failed to save root password\n");
        return 1;
    }

    printf("Root password reset. Run 'login root', then 'bootuser root' if desired.\n");
    return 0;
}

int tdsh_cmd_rootrecover(tdsh_session_t *session, int argc, char **argv)
{
    (void)argv;
    if (argc != 1)
    {
        printf("usage: rootrecover\n");
        return 2;
    }
    if (!session || !session->interactive || !tdsh_console_begin_recovery())
    {
        printf("rootrecover: physical console only; reboot locally after remote desktop use\n");
        return 1;
    }
    int result = recover_root_password();
    tdsh_console_end_recovery();
    return result;
}

int tdsh_cmd_bootuser(tdsh_session_t *session, int argc, char **argv)
{
    char current[TDSH_USERNAME_MAX];
    bool have_current = tdsh_boot_user_get(current, sizeof(current)) == 0;
    if (argc == 1)
    {
        printf("Boot user: %s\n", have_current ? current : "not configured");
        return 0;
    }
    if (argc != 2)
    {
        printf("usage: bootuser [username|--require-password]\n");
        return 2;
    }
    if (strcmp(session->username, "root") != 0)
    {
        printf("tdsh: permission denied: root required\n");
        return 1;
    }
    if (!strcmp(argv[1], "--require-password") || !strcmp(argv[1], "off"))
        return tdsh_boot_login_require_password() ? 1 : 0;
    if (!tdsh_user_exists(argv[1]))
    {
        printf("No user found named '%s'.\n", argv[1]);
        return 1;
    }
    if (tdsh_boot_user_set(argv[1]) != 0)
    {
        printf("tdsh: failed to save boot user\n");
        return 1;
    }
    printf("Boot user set to %s. Remembered login requires a successful password login.\n", argv[1]);
    return 0;
}

#include "tdsh_users_access.inc"
#include "tdsh_users_hint.inc"

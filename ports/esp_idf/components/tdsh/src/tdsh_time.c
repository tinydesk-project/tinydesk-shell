#include "tdsh_espidf_internal.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "esp_log.h"
#include "esp_sntp.h"
#include "nvs.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "tdsh-time";

static int tz_file(tdsh_session_t *session, char *out, size_t out_size)
{
    char logical[TDSH_MAX_PATH];
    int n = snprintf(logical, sizeof(logical), "%s/.tdsh_tz", session->home);
    if (n < 0 || n >= (int)sizeof(logical))
        return -ENAMETOOLONG;
    return tdsh_path_to_real(session, logical, out, out_size, NULL, 0);
}

static long get_offset(tdsh_session_t *session)
{
    char path[TDSH_MAX_PATH + sizeof(TDSH_MOUNT_POINT) + 16];
    if (tz_file(session, path, sizeof(path)) != 0)
        return 0;
    FILE *f = fopen(path, "r");
    if (!f)
        return 0;
    long offset = 0;
    if (fscanf(f, "%ld", &offset) != 1)
        offset = 0;
    fclose(f);
    return offset;
}

static int set_offset(tdsh_session_t *session, long offset)
{
    char path[TDSH_MAX_PATH + sizeof(TDSH_MOUNT_POINT) + 16];
    int rc = tz_file(session, path, sizeof(path));
    if (rc != 0)
        return rc;
    FILE *f = fopen(path, "w");
    if (!f)
        return -errno;
    fprintf(f, "%ld\n", offset);
    fclose(f);
    return 0;
}

static bool time_valid(void)
{
    time_t now = time(NULL);
    struct tm tmv;
    gmtime_r(&now, &tmv);
    return tmv.tm_year + 1900 >= 2020;
}

/* automatic time on/off, kept in NVS. */
static int s_auto = -1;   /* -1: not read yet */

bool tdsh_time_auto(void)
{
    if (s_auto < 0)
    {
        uint8_t v = 1;
        nvs_handle_t h;
        if (nvs_open("ush_time", NVS_READONLY, &h) == ESP_OK)
        {
            (void)nvs_get_u8(h, "auto", &v);
            nvs_close(h);
        }
        s_auto = v ? 1 : 0;
    }
    return s_auto != 0;
}

int tdsh_time_set_auto(bool on)
{
    nvs_handle_t h;
    if (nvs_open("ush_time", NVS_READWRITE, &h) != ESP_OK)
        return -1;
    esp_err_t err = nvs_set_u8(h, "auto", on ? 1 : 0);
    if (err == ESP_OK)
        err = nvs_commit(h);
    nvs_close(h);
    if (err != ESP_OK)
        return -1;
    s_auto = on ? 1 : 0;
    if (!on && esp_sntp_enabled())
        esp_sntp_stop();
    if (on)
        tdsh_time_sync_start();
    return 0;
}

static void sync_run(void);

void tdsh_time_sync_start(void)
{
    if (!tdsh_time_auto())
        return;
    sync_run();
}

int tdsh_time_sync_now(void)
{
    if (!tdsh_network_is_online())
        return -1;
    (void)sntp_get_sync_status();          /* reading clears an old "completed" */
    if (!esp_sntp_enabled())
    {
        esp_sntp_setoperatingmode(ESP_SNTP_OPMODE_POLL);
        esp_sntp_setservername(0, "pool.ntp.org");
        esp_sntp_init();
    }
    else
    {
        (void)esp_sntp_restart();
    }
    bool done = false;
    for (int i = 0; i < 40 && !done; ++i)
    {
        vTaskDelay(pdMS_TO_TICKS(200));
        done = sntp_get_sync_status() == SNTP_SYNC_STATUS_COMPLETED;
    }
    if (!tdsh_time_auto())
        esp_sntp_stop();   /* a one-off sync */
    ESP_LOGI(TAG, "%s", done ? "system time synchronized" : "SNTP sync timed out");
    return done ? 0 : -1;
}

static void sync_run(void)
{
    if (!tdsh_network_is_online())
        return;

    if (!esp_sntp_enabled())
    {
        esp_sntp_setoperatingmode(ESP_SNTP_OPMODE_POLL);
        esp_sntp_setservername(0, "pool.ntp.org");
        esp_sntp_init();
    }
    else
    {
        (void)esp_sntp_restart();
    }

    for (int i = 0; i < 30 && !time_valid(); ++i)
    {
        vTaskDelay(pdMS_TO_TICKS(200));
    }
    if (time_valid())
        ESP_LOGI(TAG, "system time synchronized");
    else
        ESP_LOGW(TAG, "SNTP started; time has not synchronized yet");
}

static int parse_tz(const char *s, long *offset)
{
    if (!s || !offset)
        return -1;
    bool neg = s[0] == '-';
    bool pos = s[0] == '+';
    const char *p = s + (neg || pos ? 1 : 0);
    const char *colon = strchr(p, ':');
    if (!colon)
        return -1;
    char hb[8];
    size_t hn = (size_t)(colon - p);
    if (hn == 0 || hn >= sizeof(hb))
        return -1;
    memcpy(hb, p, hn);
    hb[hn] = '\0';
    char *end = NULL;
    long h = strtol(hb, &end, 10);
    if (!end || *end)
        return -1;
    long m = strtol(colon + 1, &end, 10);
    if (!end || *end || h > 14 || m < 0 || m > 59)
        return -1;
    long v = h * 3600 + m * 60;
    *offset = neg ? -v : v;
    if (*offset < -14 * 3600L || *offset > 14 * 3600L)
        return -1;
    return 0;
}

static void print_offset(long off)
{
    char sign = off < 0 ? '-' : '+';
    long a = labs(off);
    printf("UTC%c%ld:%02ld\n", sign, a / 3600, (a % 3600) / 60);
}

int tdsh_cmd_tz(tdsh_session_t *session, int argc, char **argv)
{
    if (argc == 1)
    {
        print_offset(get_offset(session));
        return 0;
    }
    if (argc != 2)
    {
        printf("usage: tz [+|-]HH:MM\n");
        return 2;
    }
    long offset;
    if (parse_tz(argv[1], &offset) != 0)
    {
        printf("Invalid timezone. Example: tz +5:30\n");
        return 1;
    }
    int rc = set_offset(session, offset);
    if (rc != 0)
    {
        printf("tz: unable to save timezone: %s\n", strerror(-rc));
        return 1;
    }
    print_offset(offset);
    return 0;
}

static int local_tm(tdsh_session_t *session, struct tm *out)
{
    time_t now = time(NULL);
    if (!time_valid())
        return -1;
    now += (time_t)get_offset(session);
    return gmtime_r(&now, out) ? 0 : -1;
}

int tdsh_cmd_date(tdsh_session_t *session, int argc, char **argv)
{
    (void)argc;
    (void)argv;
    struct tm t;
    if (local_tm(session, &t) != 0)
    {
        printf("System time is not synchronized. Connect Wi-Fi or Ethernet first.\n");
        return 1;
    }
    static const char *wd[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    static const char *mo[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    printf("%s %s %2d %02d:%02d:%02d %d\n", wd[t.tm_wday], mo[t.tm_mon], t.tm_mday,
           t.tm_hour, t.tm_min, t.tm_sec, t.tm_year + 1900);
    return 0;
}

static bool leap(int y)
{
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

/* Gregorian day of week: 0=Sunday..6=Saturday. */
static int day_of_week(int y, int m, int d)
{
    static const int tab[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    if (m < 3)
        y--;
    return (y + y / 4 - y / 100 + y / 400 + tab[m - 1] + d) % 7;
}

int tdsh_cmd_cal(tdsh_session_t *session, int argc, char **argv)
{
    (void)argc;
    (void)argv;
    struct tm t;
    if (local_tm(session, &t) != 0)
    {
        printf("System time is not synchronized. Connect Wi-Fi or Ethernet first.\n");
        return 1;
    }
    static const char *months[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    static const int mdays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int year = t.tm_year + 1900;
    int month = t.tm_mon + 1;
    int days = mdays[t.tm_mon] + (month == 2 && leap(year) ? 1 : 0);
    int sunday0 = day_of_week(year, month, 1);
    int monday0 = (sunday0 + 6) % 7;

    char title[40];
    snprintf(title, sizeof(title), "%s %d", months[t.tm_mon], year);
    int pad = (20 - (int)strlen(title)) / 2;
    if (pad < 0)
        pad = 0;
    printf("%*s%s\n", pad, "", title);
    printf("Mo Tu We Th Fr Sa Su\n");
    for (int i = 0; i < monday0; ++i)
        printf("   ");
    int col = monday0;
    for (int d = 1; d <= days; ++d)
    {
        if (d == t.tm_mday)
            printf("\033[7m%2d\033[0m", d);
        else
            printf("%2d", d);
        col++;
        if (col == 7)
        {
            printf("\n");
            col = 0;
        }
        else
            printf(" ");
    }
    if (col)
        printf("\n");
    return 0;
}

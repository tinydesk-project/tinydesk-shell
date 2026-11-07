#include "tdsh_espidf_internal.h"

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

static int copy_file(const char *src, const char *dst)
{
    FILE *out = fopen(dst, "wb");
    if (!out)
        return -errno;
    FILE *in = fopen(src, "rb");
    if (!in)
    {
        fclose(out);
        return errno == ENOENT ? 0 : -errno;
    }
    char buf[512];
    int rc = 0;
    size_t n;
    while ((n = fread(buf, 1, sizeof(buf), in)) > 0)
    {
        if (fwrite(buf, 1, n, out) != n)
        {
            rc = -EIO;
            break;
        }
    }
    fclose(in);
    fclose(out);
    return rc;
}

/*
 * Prepare the editor buffer from an existing target file.
 *
 * This deliberately uses stat() first instead of fopen() so a non-existent
 * SMB file is treated as a new file.  The SMB stat path returns a real
 * -errno value, while a failed smb2_open() historically fell back to EIO.
 */
static int prepare_editor_buffer(const char *src, const char *tmp)
{
    struct stat st;

    if (stat(src, &st) == 0)
    {
        if (S_ISDIR(st.st_mode))
            return -EISDIR;
        return copy_file(src, tmp);
    }

    int saved = errno;
    if (saved != ENOENT)
        return -saved;

    /* New file: create an empty local editor buffer. */
    FILE *f = fopen(tmp, "wb");
    if (!f)
        return -errno;
    fclose(f);
    return 0;
}

/*
 * Save through normal read/write operations instead of rename().
 *
 * The editor buffer is on LittleFS (/fs/tmp), while an SMB destination is
 * on the /net VFS. POSIX rename() cannot move a file across filesystems
 * (EXDEV), so copying is the portable operation for both local and SMB
 * destinations.
 */
static int save_editor_buffer(const char *tmp, const char *dst)
{
    int rc = copy_file(tmp, dst);
    if (rc != 0)
        return rc;

    if (unlink(tmp) != 0 && errno != ENOENT)
    {
        return -errno;
    }
    return 0;
}

static void show_file(const char *path)
{
    FILE *f = fopen(path, "r");
    if (!f)
        return;
    char line[TDSH_MAX_LINE + 2];
    unsigned n = 1;
    while (fgets(line, sizeof(line), f))
        printf("%4u | %s", n++, line);
    fclose(f);
}

int tdsh_cmd_write(tdsh_session_t *session, int argc, char **argv)
{
    if (argc < 2)
    {
        printf("usage: write <file> [text ...]\n");
        return 2;
    }
    char real[TDSH_MAX_PATH + sizeof(TDSH_MOUNT_POINT) + 16];
    char logical[TDSH_MAX_PATH];
    int rc = tdsh_path_to_real(session, argv[1], real, sizeof(real), logical, sizeof(logical));
    if (rc != 0)
    {
        printf("write: invalid path\n");
        return 1;
    }

    if (argc > 2)
    {
        FILE *f = fopen(real, "w");
        if (!f)
        {
            printf("write: %s: %s\n", logical, strerror(errno));
            return 1;
        }
        for (int i = 2; i < argc; ++i)
            fprintf(f, "%s%s", argv[i], i + 1 < argc ? " " : "");
        fputc('\n', f);
        fclose(f);
        return 0;
    }

    if (!session->interactive)
    {
        printf("write: interactive editor unavailable in background scripts\n");
        return 1;
    }

    const char *tmp = TDSH_MOUNT_POINT "/tmp/.tdsh_write.tmp";
    rc = prepare_editor_buffer(real, tmp);
    if (rc != 0)
    {
        printf("write: unable to prepare editor: %s\n", strerror(-rc));
        return 1;
    }

    printf("tdsh line editor: %s\n", logical);
    printf("Enter text to append. Commands: .save  .quit  .show  .clear  .help\n");
    printf("Existing content:\n");
    show_file(tmp);

    char line[TDSH_MAX_LINE + 1];
    for (;;)
    {
        int n = tdsh_console_readline("write> ", line, sizeof(line), true);
        if (n < 0)
        {
            unlink(tmp);
            return 1;
        }
        if (strcmp(line, ".save") == 0)
        {
            rc = save_editor_buffer(tmp, real);
            if (rc != 0)
            {
                printf("write: save failed: %s\n", strerror(-rc));
                (void)unlink(tmp);
                return 1;
            }
            printf("Saved %s\n", logical);
            return 0;
        }
        if (strcmp(line, ".quit") == 0)
        {
            unlink(tmp);
            printf("Changes discarded.\n");
            return 0;
        }
        if (strcmp(line, ".show") == 0)
        {
            show_file(tmp);
            continue;
        }
        if (strcmp(line, ".clear") == 0)
        {
            FILE *f = fopen(tmp, "w");
            if (f)
                fclose(f);
            printf("Buffer cleared.\n");
            continue;
        }
        if (strcmp(line, ".help") == 0)
        {
            printf(".save save and exit | .quit discard | .show show buffer | .clear erase buffer\n");
            continue;
        }
        FILE *f = fopen(tmp, "a");
        if (!f)
        {
            printf("write: %s\n", strerror(errno));
            unlink(tmp);
            return 1;
        }
        fprintf(f, "%s\n", line);
        fclose(f);
    }
}

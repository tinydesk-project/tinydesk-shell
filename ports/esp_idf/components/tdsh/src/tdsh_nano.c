#include "tdsh_espidf_internal.h"

#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

/*
 * Lightweight VT100 nano-style editor for TinyDesk Shell / ESP32-C6.
 *
 * This is intentionally not GNU nano.  It implements the familiar nano
 * workflow with a small RAM footprint and no external terminal library.
 *
 * Supported:
 *   arrows, Home/End, PageUp/PageDown
 *   insertion, Backspace/Delete, Enter
 *   Ctrl+O save
 *   Ctrl+X exit (save/discard/cancel prompt when modified)
 *   Ctrl+K cut current line
 *   Ctrl+U paste cut line
 *   Ctrl+W search
 *   Ctrl+C cursor position
 *   Ctrl+L redraw
 *   Ctrl+G help/status
 *
 * The path is resolved through tdsh_path_to_real(), therefore files on
 * LittleFS and SMB mappings below ~/mnt/<name> use exactly the same editor.
 */

#define NANO_VERSION      "0.1"
#define NANO_SCREEN_COLS  80U     /* widest screen used (line buffers) */
#define NANO_DEFAULT_ROWS 24U     /* when the terminal does not say */
#define NANO_MIN_ROWS     8U
#define NANO_MAX_ROWS     100U

/* Keep predictable headroom on the ESP32-C6 (no PSRAM required). */
#define NANO_MAX_FILE_BYTES   (64U * 1024U)
#define NANO_MAX_LINES        2048U
#define NANO_MAX_LINE_BYTES   512U
#define NANO_INITIAL_LINE_CAP 32U

enum
{
    NKEY_NONE = 0,
    NKEY_UP = 0x100,
    NKEY_DOWN,
    NKEY_LEFT,
    NKEY_RIGHT,
    NKEY_HOME,
    NKEY_END,
    NKEY_DELETE,
    NKEY_PGUP,
    NKEY_PGDN,
};

typedef struct
{
    char *data;
    uint16_t len;
    uint16_t cap;
} nano_line_t;

typedef struct
{
    nano_line_t *lines;
    size_t line_count;
    size_t line_cap;

    size_t cy;
    size_t cx;   /* byte offset in the line, always at a character's start */
    size_t top;
    size_t left; /* first character column shown */

    bool modified;
    bool loaded_existing;

    char logical[TDSH_MAX_PATH];
    char real[TDSH_MAX_PATH + sizeof(TDSH_MOUNT_POINT) + 32];

    char status[NANO_SCREEN_COLS + 1];
    char *kill_line;
    size_t kill_len;

    unsigned rows;      /* screen: header, text, status line, two help lines */
    unsigned cols;
} nano_editor_t;

/* The screen layout follows the terminal's size (a TinyDesk Terminal window
 * is often smaller than 80x24). */
static unsigned text_rows(const nano_editor_t *ed)
{
    return ed->rows - 4U;
}
static unsigned text_cols(const nano_editor_t *ed)
{
    return ed->cols - 1U;
}
static unsigned status_row(const nano_editor_t *ed)
{
    return ed->rows - 2U;
}

/*
 * UTF-8: lines are kept as bytes, but the cursor moves, deletes and counts
 * columns by character, one column each (as the shell's line editor). A
 * character is a byte that is not a continuation byte (10xxxxxx) together
 * with the continuation bytes after it; invalid bytes are shown as '?'.
 */
static bool utf8_cont(unsigned char c)
{
    return (c & 0xC0U) == 0x80U;
}

/* Bytes in the sequence this lead byte starts: 1 for ASCII and invalid bytes. */
static size_t utf8_seq_len(unsigned char c)
{
    if (c >= 0xC2U && c <= 0xDFU)
        return 2U;
    if (c >= 0xE0U && c <= 0xEFU)
        return 3U;
    if (c >= 0xF0U && c <= 0xF4U)
        return 4U;
    return 1U;
}

static size_t utf8_next(const char *s, size_t len, size_t at)
{
    if (at >= len)
        return len;
    at++;
    while (at < len && utf8_cont((unsigned char)s[at]))
        at++;
    return at;
}

static size_t utf8_prev(const char *s, size_t at)
{
    if (at == 0)
        return 0;
    at--;
    while (at > 0 && utf8_cont((unsigned char)s[at]))
        at--;
    return at;
}

/* The character column of byte offset `at`. */
static size_t utf8_column(const char *s, size_t at)
{
    size_t col = 0;
    for (size_t i = 0; i < at; ++i)
    {
        if (i == 0 || !utf8_cont((unsigned char)s[i]))
            col++;
    }
    return col;
}

/* The byte offset of character column `col`, or the line's end. */
static size_t utf8_offset(const char *s, size_t len, size_t col)
{
    size_t at = 0;
    while (col-- > 0 && at < len)
        at = utf8_next(s, len, at);
    return at;
}

static void term_move(unsigned row, unsigned col)
{
    printf("\033[%u;%uH", row, col);
}

static void term_clear_line(void)
{
    printf("\033[2K");
}

static void status_set(nano_editor_t *ed, const char *text)
{
    if (!ed)
        return;
    snprintf(ed->status, sizeof(ed->status), "%s", text ? text : "");
}

static void status_setf(nano_editor_t *ed, const char *fmt,
                        const char *arg)
{
    if (!ed)
        return;
    snprintf(ed->status, sizeof(ed->status), fmt, arg ? arg : "");
}

static int line_reserve(nano_line_t *line, size_t need)
{
    if (!line)
        return -EINVAL;
    if (need > NANO_MAX_LINE_BYTES + 1U)
        return -E2BIG;
    if (line->cap >= need)
        return 0;

    size_t cap = line->cap ? line->cap : NANO_INITIAL_LINE_CAP;
    while (cap < need)
    {
        cap *= 2U;
        if (cap > NANO_MAX_LINE_BYTES + 1U)
        {
            cap = NANO_MAX_LINE_BYTES + 1U;
            break;
        }
    }
    if (cap < need)
        return -E2BIG;

    char *p = realloc(line->data, cap);
    if (!p)
        return -ENOMEM;
    line->data = p;
    line->cap = (uint16_t)cap;
    return 0;
}

static int line_set(nano_line_t *line, const char *src, size_t len)
{
    if (!line || (!src && len))
        return -EINVAL;
    if (len > NANO_MAX_LINE_BYTES)
        return -E2BIG;
    int rc = line_reserve(line, len + 1U);
    if (rc != 0)
        return rc;
    if (len)
        memcpy(line->data, src, len);
    line->data[len] = '\0';
    line->len = (uint16_t)len;
    return 0;
}

static void line_free(nano_line_t *line)
{
    if (!line)
        return;
    free(line->data);
    memset(line, 0, sizeof(*line));
}

static int editor_reserve_lines(nano_editor_t *ed, size_t need)
{
    if (!ed)
        return -EINVAL;
    if (need > NANO_MAX_LINES)
        return -E2BIG;
    if (ed->line_cap >= need)
        return 0;

    size_t cap = ed->line_cap ? ed->line_cap : 16U;
    while (cap < need)
    {
        cap *= 2U;
        if (cap > NANO_MAX_LINES)
        {
            cap = NANO_MAX_LINES;
            break;
        }
    }
    if (cap < need)
        return -E2BIG;

    nano_line_t *p = realloc(ed->lines, cap * sizeof(*p));
    if (!p)
        return -ENOMEM;

    if (cap > ed->line_cap)
    {
        memset(p + ed->line_cap, 0,
               (cap - ed->line_cap) * sizeof(*p));
    }
    ed->lines = p;
    ed->line_cap = cap;
    return 0;
}

static int editor_insert_line(nano_editor_t *ed, size_t at,
                              const char *src, size_t len)
{
    if (!ed || at > ed->line_count)
        return -EINVAL;
    if (ed->line_count >= NANO_MAX_LINES)
        return -E2BIG;

    int rc = editor_reserve_lines(ed, ed->line_count + 1U);
    if (rc != 0)
        return rc;

    if (at < ed->line_count)
    {
        memmove(&ed->lines[at + 1U], &ed->lines[at],
                (ed->line_count - at) * sizeof(ed->lines[0]));
    }
    memset(&ed->lines[at], 0, sizeof(ed->lines[at]));
    ed->line_count++;

    rc = line_set(&ed->lines[at], src ? src : "", len);
    if (rc != 0)
    {
        if (at + 1U < ed->line_count)
        {
            memmove(&ed->lines[at], &ed->lines[at + 1U],
                    (ed->line_count - at - 1U) * sizeof(ed->lines[0]));
        }
        ed->line_count--;
        memset(&ed->lines[ed->line_count], 0,
               sizeof(ed->lines[ed->line_count]));
    }
    return rc;
}

static void editor_delete_line(nano_editor_t *ed, size_t at)
{
    if (!ed || at >= ed->line_count)
        return;
    line_free(&ed->lines[at]);
    if (at + 1U < ed->line_count)
    {
        memmove(&ed->lines[at], &ed->lines[at + 1U],
                (ed->line_count - at - 1U) * sizeof(ed->lines[0]));
    }
    ed->line_count--;
    if (ed->line_count < ed->line_cap)
    {
        memset(&ed->lines[ed->line_count], 0,
               sizeof(ed->lines[ed->line_count]));
    }
}

static void editor_free(nano_editor_t *ed)
{
    if (!ed)
        return;
    for (size_t i = 0; i < ed->line_count; ++i)
        line_free(&ed->lines[i]);
    free(ed->lines);
    free(ed->kill_line);
    memset(ed, 0, sizeof(*ed));
}

static int editor_init_empty(nano_editor_t *ed)
{
    int rc = editor_insert_line(ed, 0, "", 0);
    if (rc != 0)
        return rc;
    ed->loaded_existing = false;
    return 0;
}

static int editor_load(nano_editor_t *ed)
{
    struct stat st;
    if (stat(ed->real, &st) != 0)
    {
        if (errno == ENOENT)
            return editor_init_empty(ed);
        return -errno;
    }
    if (S_ISDIR(st.st_mode))
        return -EISDIR;
    if ((uint64_t)st.st_size > NANO_MAX_FILE_BYTES)
        return -EFBIG;

    FILE *f = fopen(ed->real, "rb");
    if (!f)
        return -errno;

    char linebuf[NANO_MAX_LINE_BYTES + 1U];
    size_t llen = 0;
    size_t total = 0;
    bool last_was_newline = false;
    int rc = 0;

    for (;;)
    {
        int c = fgetc(f);
        if (c == EOF)
            break;
        total++;
        if (total > NANO_MAX_FILE_BYTES)
        {
            rc = -EFBIG;
            break;
        }

        if (c == '\r')
        {
            /* Normalize CRLF/CR files to LF in the editor buffer. */
            continue;
        }

        if (c == '\n')
        {
            rc = editor_insert_line(ed, ed->line_count, linebuf, llen);
            if (rc != 0)
                break;
            llen = 0;
            last_was_newline = true;
            continue;
        }

        last_was_newline = false;
        if (llen >= NANO_MAX_LINE_BYTES)
        {
            rc = -E2BIG;
            break;
        }
        linebuf[llen++] = (char)c;
    }

    if (rc == 0 && ferror(f))
        rc = -EIO;
    fclose(f);

    if (rc != 0)
        return rc;

    if (llen > 0 || ed->line_count == 0 || last_was_newline)
    {
        rc = editor_insert_line(ed, ed->line_count, linebuf, llen);
        if (rc != 0)
            return rc;
    }

    ed->loaded_existing = true;
    return 0;
}

static int editor_save(nano_editor_t *ed)
{
    if (!ed)
        return -EINVAL;

    FILE *f = fopen(ed->real, "wb");
    if (!f)
        return -errno;

    int rc = 0;
    for (size_t i = 0; i < ed->line_count; ++i)
    {
        nano_line_t *line = &ed->lines[i];

        if (line->len &&
            fwrite(line->data, 1, line->len, f) != line->len)
        {
            rc = -EIO;
            break;
        }

        if (i + 1U < ed->line_count)
        {
            if (fputc('\n', f) == EOF)
            {
                rc = -EIO;
                break;
            }
        }
    }

    if (fflush(f) != 0 && rc == 0)
        rc = -errno;
    if (fclose(f) != 0 && rc == 0)
        rc = -errno;

    if (rc == 0)
    {
        ed->modified = false;
        ed->loaded_existing = true;

        char msg[NANO_SCREEN_COLS + 1];
        snprintf(msg, sizeof(msg), "Wrote %u line%s",
                 (unsigned)ed->line_count,
                 ed->line_count == 1 ? "" : "s");
        status_set(ed, msg);
    }
    return rc;
}

static void editor_scroll(nano_editor_t *ed)
{
    if (!ed || ed->line_count == 0)
        return;

    if (ed->cy >= ed->line_count)
        ed->cy = ed->line_count - 1U;
    if (ed->cx > ed->lines[ed->cy].len)
        ed->cx = ed->lines[ed->cy].len;

    if (ed->cy < ed->top)
        ed->top = ed->cy;
    if (ed->cy >= ed->top + text_rows(ed))
    {
        ed->top = ed->cy - text_rows(ed) + 1U;
    }

    size_t col = utf8_column(ed->lines[ed->cy].data, ed->cx);
    if (col < ed->left)
        ed->left = col;
    if (col >= ed->left + text_cols(ed))
    {
        ed->left = col - text_cols(ed) + 1U;
    }
}

/* At most `width` characters: whole UTF-8 sequences, '?' for control
 * characters and invalid or cut-off bytes. */
static void print_clipped(const char *text, size_t len, size_t width)
{
    size_t i = 0;
    for (size_t col = 0; col < width && i < len; ++col)
    {
        size_t end = utf8_next(text, len, i);
        unsigned char ch = (unsigned char)text[i];
        if (end - i > 1U && end - i == utf8_seq_len(ch))
        {
            fwrite(text + i, 1, end - i, stdout);
        }
        else
        {
            if (ch == '\t')
                ch = ' ';
            if (ch < 0x20 || ch >= 0x7F || end - i > 1U)
                ch = '?';
            putchar((char)ch);
        }
        i = end;
    }
}

static void editor_draw(nano_editor_t *ed)
{
    editor_scroll(ed);

    printf("\033[?25l");

    /* Header. */
    term_move(1, 1);
    term_clear_line();
    printf("\033[7m");
    char header[NANO_SCREEN_COLS + 1];

    /*
     * Keep the complete header provably inside the 81-byte buffer even when
     * the modified marker is present.  The previous %.48s path allowance
     * could produce up to 86 bytes and triggered -Wformat-truncation.
     */
    const char *modified_mark = ed->modified ? " [Modified]" : "";
    snprintf(header, sizeof(header),
             " tdsh nano %s  File: %.42s%s",
             NANO_VERSION,
             ed->logical,
             modified_mark);
    print_clipped(header, strlen(header), text_cols(ed));
    printf("\033[0m");

    /* File area. */
    for (unsigned row = 0; row < text_rows(ed); ++row)
    {
        term_move(2U + row, 1);
        term_clear_line();

        size_t li = ed->top + row;
        if (li >= ed->line_count)
        {
            putchar('~');
            continue;
        }

        nano_line_t *line = &ed->lines[li];
        size_t from = utf8_offset(line->data, line->len, ed->left);
        if (from < line->len)
        {
            print_clipped(line->data + from,
                          line->len - from,
                          text_cols(ed));
        }
    }

    /* Status. */
    term_move(status_row(ed), 1);
    term_clear_line();
    printf("\033[7m");
    char statline[NANO_SCREEN_COLS + 1];
    size_t cur_col = utf8_column(ed->lines[ed->cy].data, ed->cx);
    if (ed->status[0])
    {
        snprintf(statline, sizeof(statline), " %.77s", ed->status);
    }
    else
    {
        snprintf(statline, sizeof(statline),
                 " Line %u/%u  Col %u  %s",
                 (unsigned)(ed->cy + 1U),
                 (unsigned)ed->line_count,
                 (unsigned)(cur_col + 1U),
                 ed->modified ? "Modified" : "Unmodified");
    }
    print_clipped(statline, strlen(statline), text_cols(ed));
    printf("\033[0m");

    term_move(ed->rows - 1U, 1);
    term_clear_line();
    {
        static const char help[] = "^G Help  ^O Write Out  ^W Where Is  ^K Cut  ^U Paste";
        print_clipped(help, sizeof(help) - 1U, text_cols(ed));
    }
    term_move(ed->rows, 1);
    term_clear_line();
    {
        static const char help[] = "^X Exit  ^C Cur Pos    ^L Refresh   Home/End PgUp/PgDn";
        print_clipped(help, sizeof(help) - 1U, text_cols(ed));
    }

    unsigned crow = 2U + (unsigned)(ed->cy - ed->top);
    unsigned ccol = 1U + (unsigned)(cur_col - ed->left);
    if (crow > ed->rows - 3U)
        crow = ed->rows - 3U;
    if (ccol > text_cols(ed))
        ccol = text_cols(ed);

    term_move(crow, ccol);
    printf("\033[?25h");
    fflush(stdout);

    /* Status messages are one-shot, just like nano's bottom message area. */
    ed->status[0] = '\0';
}

static int read_byte(void)
{
    int c = fgetc(stdin);
    if (c == EOF)
    {
        clearerr(stdin);
        return -1;
    }
    return c & 0xFF;
}

/* The terminal's size: put the cursor as far down and right as it goes and
 * ask where it is (every VT terminal answers ESC[6n with ESC[row;colR).
 * Without an answer nano keeps 80x24, and a key that arrives instead is
 * given back. Columns beyond 80 are not used. */
static void editor_query_size(nano_editor_t *ed)
{
    ed->rows = NANO_DEFAULT_ROWS;
    ed->cols = NANO_SCREEN_COLS;
    printf("\033[999;999H\033[6n");
    fflush(stdout);

    int c = read_byte();
    if (c != 0x1B)
    {
        if (c >= 0)
            ungetc(c, stdin);
        return;
    }
    if (read_byte() != '[')
        return;
    unsigned v[2] = {0U, 0U};
    int field = 0;
    for (int n = 0; n < 12; ++n)
    {
        int x = read_byte();
        if (x >= '0' && x <= '9')
        {
            if (v[field] < 10000U)
                v[field] = v[field] * 10U + (unsigned)(x - '0');
        }
        else if (x == ';' && field == 0)
        {
            field = 1;
        }
        else if (x == 'R' && field == 1)
        {
            if (v[0] >= NANO_MIN_ROWS)
                ed->rows = v[0] > NANO_MAX_ROWS ? NANO_MAX_ROWS : v[0];
            if (v[1] >= 20U)
                ed->cols = v[1] > NANO_SCREEN_COLS ? NANO_SCREEN_COLS : v[1];
            return;
        }
        else
        {
            return;
        }
    }
}

static int editor_read_key(void)
{
    int c = read_byte();
    if (c < 0)
        return -1;

    if (c != 0x1B)
        return c;

    int c2 = read_byte();
    if (c2 < 0)
        return 0x1B;
    if (c2 != '[' && c2 != 'O')
        return 0x1B;

    int param = 0;
    bool have_param = false;

    for (;;)
    {
        int x = read_byte();
        if (x < 0)
            return -1;

        if (x >= '0' && x <= '9')
        {
            have_param = true;
            param = param * 10 + (x - '0');
            continue;
        }
        if (x == ';')
            continue;

        switch (x)
        {
        case 'A':
            return NKEY_UP;
        case 'B':
            return NKEY_DOWN;
        case 'C':
            return NKEY_RIGHT;
        case 'D':
            return NKEY_LEFT;
        case 'H':
            return NKEY_HOME;
        case 'F':
            return NKEY_END;
        case '~':
            if (!have_param)
                return NKEY_NONE;
            if (param == 1 || param == 7)
                return NKEY_HOME;
            if (param == 3)
                return NKEY_DELETE;
            if (param == 4 || param == 8)
                return NKEY_END;
            if (param == 5)
                return NKEY_PGUP;
            if (param == 6)
                return NKEY_PGDN;
            return NKEY_NONE;
        default:
            return NKEY_NONE;
        }
    }
}

/* Insert one character: n bytes (a whole UTF-8 sequence) at the cursor. */
static int editor_insert_bytes(nano_editor_t *ed, const unsigned char *bytes, size_t n)
{
    nano_line_t *line = &ed->lines[ed->cy];
    if ((size_t)line->len + n > NANO_MAX_LINE_BYTES)
        return -E2BIG;

    int rc = line_reserve(line, (size_t)line->len + n + 1U);
    if (rc != 0)
        return rc;

    memmove(line->data + ed->cx + n,
            line->data + ed->cx,
            (size_t)line->len - ed->cx + 1U);
    memcpy(line->data + ed->cx, bytes, n);
    line->len = (uint16_t)((size_t)line->len + n);
    ed->cx += n;
    ed->modified = true;
    return 0;
}

static int editor_insert_char(nano_editor_t *ed, unsigned char ch)
{
    return editor_insert_bytes(ed, &ch, 1U);
}

/* A typed character: the lead byte, then its UTF-8 continuation bytes, so a
 * character is never stored or drawn in halves. */
static int editor_insert_typed(nano_editor_t *ed, unsigned char lead)
{
    unsigned char seq[4] = {lead};
    size_t n = 1U;
    size_t want = utf8_seq_len(lead);
    while (n < want)
    {
        int c = read_byte();
        if (c < 0)
            break;
        if (!utf8_cont((unsigned char)c))
        {
            ungetc(c, stdin);
            break;
        }
        seq[n++] = (unsigned char)c;
    }
    return editor_insert_bytes(ed, seq, n);
}

static int editor_insert_spaces(nano_editor_t *ed, unsigned count)
{
    for (unsigned i = 0; i < count; ++i)
    {
        int rc = editor_insert_char(ed, ' ');
        if (rc != 0)
            return rc;
    }
    return 0;
}

static int editor_enter(nano_editor_t *ed)
{
    nano_line_t *line = &ed->lines[ed->cy];
    size_t tail_len = (size_t)line->len - ed->cx;

    char *tail = NULL;
    if (tail_len)
    {
        tail = malloc(tail_len);
        if (!tail)
            return -ENOMEM;
        memcpy(tail, line->data + ed->cx, tail_len);
    }

    int rc = editor_insert_line(ed, ed->cy + 1U,
                                tail ? tail : "", tail_len);
    free(tail);
    if (rc != 0)
        return rc;

    line = &ed->lines[ed->cy];
    line->len = (uint16_t)ed->cx;
    line->data[line->len] = '\0';

    ed->cy++;
    ed->cx = 0;
    ed->modified = true;
    return 0;
}

static int editor_backspace(nano_editor_t *ed)
{
    nano_line_t *line = &ed->lines[ed->cy];

    if (ed->cx > 0)
    {
        size_t from = utf8_prev(line->data, ed->cx);
        memmove(line->data + from,
                line->data + ed->cx,
                (size_t)line->len - ed->cx + 1U);
        line->len = (uint16_t)(line->len - (ed->cx - from));
        ed->cx = from;
        ed->modified = true;
        return 0;
    }

    if (ed->cy == 0)
        return 0;

    nano_line_t *prev = &ed->lines[ed->cy - 1U];
    if ((size_t)prev->len + line->len > NANO_MAX_LINE_BYTES)
        return -E2BIG;

    size_t old_prev_len = prev->len;
    int rc = line_reserve(prev, (size_t)prev->len + line->len + 1U);
    if (rc != 0)
        return rc;

    if (line->len)
        memcpy(prev->data + prev->len, line->data, line->len);
    prev->len = (uint16_t)((size_t)prev->len + line->len);
    prev->data[prev->len] = '\0';

    editor_delete_line(ed, ed->cy);
    ed->cy--;
    ed->cx = old_prev_len;
    ed->modified = true;
    return 0;
}

static int editor_delete(nano_editor_t *ed)
{
    nano_line_t *line = &ed->lines[ed->cy];

    if (ed->cx < line->len)
    {
        size_t to = utf8_next(line->data, line->len, ed->cx);
        memmove(line->data + ed->cx,
                line->data + to,
                (size_t)line->len - to + 1U);
        line->len = (uint16_t)(line->len - (to - ed->cx));
        ed->modified = true;
        return 0;
    }

    if (ed->cy + 1U >= ed->line_count)
        return 0;

    nano_line_t *next = &ed->lines[ed->cy + 1U];
    if ((size_t)line->len + next->len > NANO_MAX_LINE_BYTES)
        return -E2BIG;

    int rc = line_reserve(line, (size_t)line->len + next->len + 1U);
    if (rc != 0)
        return rc;

    if (next->len)
        memcpy(line->data + line->len, next->data, next->len);
    line->len = (uint16_t)((size_t)line->len + next->len);
    line->data[line->len] = '\0';
    editor_delete_line(ed, ed->cy + 1U);
    ed->modified = true;
    return 0;
}

static int editor_cut_line(nano_editor_t *ed)
{
    nano_line_t *line = &ed->lines[ed->cy];

    char *copy = malloc((size_t)line->len + 1U);
    if (!copy)
        return -ENOMEM;
    if (line->len)
        memcpy(copy, line->data, line->len);
    copy[line->len] = '\0';

    free(ed->kill_line);
    ed->kill_line = copy;
    ed->kill_len = line->len;

    if (ed->line_count == 1U)
    {
        line->len = 0;
        if (line->data)
            line->data[0] = '\0';
        ed->cx = 0;
    }
    else
    {
        editor_delete_line(ed, ed->cy);
        if (ed->cy >= ed->line_count)
            ed->cy = ed->line_count - 1U;
        if (ed->cx > ed->lines[ed->cy].len)
            ed->cx = ed->lines[ed->cy].len;
    }

    ed->modified = true;
    status_set(ed, "Cut current line");
    return 0;
}

static int editor_paste_line(nano_editor_t *ed)
{
    if (!ed->kill_line)
    {
        status_set(ed, "Cutbuffer is empty");
        return 0;
    }

    int rc = editor_insert_line(ed, ed->cy,
                                ed->kill_line, ed->kill_len);
    if (rc != 0)
        return rc;

    ed->cx = ed->kill_len;
    ed->modified = true;
    status_set(ed, "Pasted cut line");
    return 0;
}

static void editor_move(nano_editor_t *ed, int key)
{
    nano_line_t *line = &ed->lines[ed->cy];
    size_t col = utf8_column(line->data, ed->cx); /* kept by Up/Down and PgUp/PgDn */

    switch (key)
    {
    case NKEY_UP:
        if (ed->cy > 0)
            ed->cy--;
        break;
    case NKEY_DOWN:
        if (ed->cy + 1U < ed->line_count)
            ed->cy++;
        break;
    case NKEY_LEFT:
        if (ed->cx > 0)
        {
            ed->cx = utf8_prev(line->data, ed->cx);
        }
        else if (ed->cy > 0)
        {
            ed->cy--;
            ed->cx = ed->lines[ed->cy].len;
        }
        return;
    case NKEY_RIGHT:
        if (ed->cx < line->len)
        {
            ed->cx = utf8_next(line->data, line->len, ed->cx);
        }
        else if (ed->cy + 1U < ed->line_count)
        {
            ed->cy++;
            ed->cx = 0;
        }
        return;
    case NKEY_HOME:
        ed->cx = 0;
        return;
    case NKEY_END:
        ed->cx = line->len;
        return;
    case NKEY_PGUP:
        if (ed->cy > text_rows(ed))
            ed->cy -= text_rows(ed);
        else
            ed->cy = 0;
        break;
    case NKEY_PGDN:
        ed->cy += text_rows(ed);
        if (ed->cy >= ed->line_count)
            ed->cy = ed->line_count - 1U;
        break;
    default:
        return;
    }

    /* Another line: the same character column, or its end. */
    line = &ed->lines[ed->cy];
    ed->cx = utf8_offset(line->data, line->len, col);
}

static int editor_prompt(nano_editor_t *ed, const char *prompt,
                         char *out, size_t out_size)
{
    if (!ed || !out || out_size < 2U)
        return -EINVAL;
    size_t len = 0;
    out[0] = '\0';

    for (;;)
    {
        term_move(status_row(ed), 1);
        term_clear_line();
        printf("\033[7m %.24s%s\033[0m", prompt ? prompt : "", out);
        fflush(stdout);

        int key = editor_read_key();
        if (key < 0)
            return -EIO;

        if (key == '\r' || key == '\n')
            return 0;
        if (key == 3 || key == 0x1B)
            return -ECANCELED;

        if (key == 8 || key == 127)
        {
            len = utf8_prev(out, len); /* a whole character */
            out[len] = '\0';
            continue;
        }

        if (key >= 0x20 && key <= 0xFF && key != 0x7F)
        {
            /* A character with its UTF-8 continuation bytes, if it fits whole. */
            char seq[4] = {(char)key};
            size_t n = 1U;
            size_t want = utf8_seq_len((unsigned char)key);
            while (n < want)
            {
                int c = read_byte();
                if (c < 0)
                    break;
                if (!utf8_cont((unsigned char)c))
                {
                    ungetc(c, stdin);
                    break;
                }
                seq[n++] = (char)c;
            }
            if (len + n < out_size)
            {
                memcpy(out + len, seq, n);
                len += n;
                out[len] = '\0';
            }
        }
    }
}

static void editor_search(nano_editor_t *ed)
{
    char needle[64];
    int rc = editor_prompt(ed, "Search: ", needle, sizeof(needle));
    if (rc != 0)
    {
        status_set(ed, "Search cancelled");
        return;
    }
    if (!needle[0])
    {
        status_set(ed, "Empty search");
        return;
    }

    size_t start_line = ed->cy;
    size_t start_col = ed->cx + 1U;

    for (int pass = 0; pass < 2; ++pass)
    {
        size_t first = pass == 0 ? start_line : 0;
        size_t last = pass == 0 ? ed->line_count : start_line + 1U;

        for (size_t li = first; li < last; ++li)
        {
            nano_line_t *line = &ed->lines[li];
            size_t from = 0;
            if (pass == 0 && li == start_line)
                from = start_col;
            if (pass == 1 && li == start_line)
            {
                if (start_col == 0)
                    continue;
            }

            if (from > line->len)
                from = line->len;
            const char *hit = strstr(line->data + from, needle);
            if (hit)
            {
                size_t col = (size_t)(hit - line->data);
                if (pass == 1 && li == start_line && col >= start_col)
                    continue;
                ed->cy = li;
                ed->cx = col;
                status_setf(ed, "Found: %s", needle);
                return;
            }
        }
    }

    status_setf(ed, "Not found: %s", needle);
}

static bool editor_exit_prompt(nano_editor_t *ed)
{
    if (!ed->modified)
        return true;

    for (;;)
    {
        term_move(status_row(ed), 1);
        term_clear_line();
        printf("\033[7m Save modified buffer?  Y Yes   N No   ^C Cancel \033[0m");
        fflush(stdout);

        int key = editor_read_key();
        if (key < 0)
            return true;

        if (key == 'y' || key == 'Y')
        {
            int rc = editor_save(ed);
            if (rc == 0)
                return true;

            char msg[NANO_SCREEN_COLS + 1];
            snprintf(msg, sizeof(msg), "Save failed: %s", strerror(-rc));
            status_set(ed, msg);
            editor_draw(ed);
            return false;
        }

        if (key == 'n' || key == 'N')
            return true;
        if (key == 3 || key == 0x1B)
        {
            status_set(ed, "Exit cancelled");
            return false;
        }
    }
}

static void editor_leave_screen(void)
{
    printf("\033[?25h\033[0m\033[2J\033[H");
    fflush(stdout);
}

int tdsh_cmd_nano(tdsh_session_t *session, int argc, char **argv)
{
    if (!session)
        return 1;

    if (argc != 2)
    {
        printf("usage: nano <file>\n");
        return 2;
    }

    if (!session->interactive)
    {
        printf("nano: interactive terminal required\n");
        return 1;
    }

    nano_editor_t ed;
    memset(&ed, 0, sizeof(ed));

    int rc = tdsh_path_to_real(session,
                               argv[1],
                               ed.real, sizeof(ed.real),
                               ed.logical, sizeof(ed.logical));
    if (rc != 0)
    {
        printf("nano: invalid path\n");
        return 1;
    }

    rc = editor_load(&ed);
    if (rc != 0)
    {
        printf("nano: %s: %s\n", ed.logical, strerror(-rc));
        editor_free(&ed);
        return 1;
    }

    status_set(&ed,
               ed.loaded_existing
                   ? "File loaded"
                   : "New File");

    editor_query_size(&ed);
    printf("\033[2J\033[H");
    editor_draw(&ed);

    bool running = true;
    while (running)
    {
        int key = editor_read_key();
        if (key < 0)
        {
            status_set(&ed, "Terminal input ended");
            break;
        }

        rc = 0;

        switch (key)
        {
        case 24: /* Ctrl+X */
            if (editor_exit_prompt(&ed))
                running = false;
            break;

        case 15: /* Ctrl+O */
            rc = editor_save(&ed);
            if (rc != 0)
            {
                char msg[NANO_SCREEN_COLS + 1];
                snprintf(msg, sizeof(msg), "Write failed: %s", strerror(-rc));
                status_set(&ed, msg);
            }
            break;

        case 11: /* Ctrl+K */
            rc = editor_cut_line(&ed);
            break;

        case 21: /* Ctrl+U */
            rc = editor_paste_line(&ed);
            break;

        case 23: /* Ctrl+W */
            editor_search(&ed);
            break;

        case 3:
        { /* Ctrl+C */
            char msg[NANO_SCREEN_COLS + 1];
            snprintf(msg, sizeof(msg),
                     "line %u/%u, column %u",
                     (unsigned)(ed.cy + 1U),
                     (unsigned)ed.line_count,
                     (unsigned)(utf8_column(ed.lines[ed.cy].data, ed.cx) + 1U));
            status_set(&ed, msg);
            break;
        }

        case 12: /* Ctrl+L */
            status_set(&ed, "Screen refreshed");
            break;

        case 7: /* Ctrl+G */
            status_set(&ed,
                       "^O save | ^X exit | ^W search | ^K cut | ^U paste");
            break;

        case NKEY_UP:
        case NKEY_DOWN:
        case NKEY_LEFT:
        case NKEY_RIGHT:
        case NKEY_HOME:
        case NKEY_END:
        case NKEY_PGUP:
        case NKEY_PGDN:
            editor_move(&ed, key);
            break;

        case NKEY_DELETE:
            rc = editor_delete(&ed);
            break;

        case 8:
        case 127:
            rc = editor_backspace(&ed);
            break;

        case '\r':
        case '\n':
            rc = editor_enter(&ed);
            break;

        case '\t':
            rc = editor_insert_spaces(&ed, 4);
            break;

        default:
            if (key >= 0x20 && key <= 0xFF)
            {
                rc = editor_insert_typed(&ed, (unsigned char)key);
            }
            break;
        }

        if (rc != 0)
        {
            char msg[NANO_SCREEN_COLS + 1];
            snprintf(msg, sizeof(msg), "Editor limit/error: %s", strerror(-rc));
            status_set(&ed, msg);
        }

        if (running)
            editor_draw(&ed);
    }

    editor_leave_screen();
    editor_free(&ed);
    return 0;
}

/*
 * tdsh_win_console.c - the Windows console as TinyDesk Shell's terminal, for
 * the standalone tdsh.exe (examples/windows/main.c).
 *
 * Output: UTF-8 with virtual-terminal processing, so the line editor's and
 * the commands' escape sequences work as in any VT terminal (Windows
 * Terminal, and the classic console on Windows 10 or later).
 * Input: while a line is edited, the console is in raw VT input mode: no
 * line buffering or echo, every key (arrows, Home, Delete, Ctrl+C) arrives
 * as VT bytes. While a command runs, the original mode is back, so Ctrl+C
 * ends a runaway command as it does on Linux; a command that handles Ctrl+C
 * itself (py) switches to raw input with tdsh_console_raw_mode() and checks
 * with tdsh_break_requested().
 *
 * Built with tdsh_win_compat.h force-included like the rest of the port.
 */
#include "tdsh_platform_win.h"
#include "tdsh_terminal.h"

#include <windows.h>

static HANDLE s_in, s_out;
static bool s_in_console;
static DWORD s_in_mode, s_out_mode;
static bool s_color;
static uint8_t s_queue[64];      /* UTF-8 bytes of keys already read */
static int s_q_head, s_q_count;
static WCHAR s_high_surrogate;

static void queue_byte(uint8_t b)
{
    if (s_q_count == (int)sizeof(s_queue))
        return;
    s_queue[(s_q_head + s_q_count) % (int)sizeof(s_queue)] = b;
    s_q_count++;
}

static void queue_char(WCHAR wc)
{
    uint32_t cp = wc;
    if (wc >= 0xD800 && wc <= 0xDBFF)
    {
        s_high_surrogate = wc;
        return;
    }
    if (wc >= 0xDC00 && wc <= 0xDFFF)
    {
        if (!s_high_surrogate)
            return;
        cp = 0x10000u + (((uint32_t)s_high_surrogate - 0xD800u) << 10) + (wc - 0xDC00u);
        s_high_surrogate = 0;
    }
    if (cp < 0x80)
    {
        queue_byte((uint8_t)cp);
    }
    else if (cp < 0x800)
    {
        queue_byte((uint8_t)(0xC0 | (cp >> 6)));
        queue_byte((uint8_t)(0x80 | (cp & 0x3F)));
    }
    else if (cp < 0x10000)
    {
        queue_byte((uint8_t)(0xE0 | (cp >> 12)));
        queue_byte((uint8_t)(0x80 | ((cp >> 6) & 0x3F)));
        queue_byte((uint8_t)(0x80 | (cp & 0x3F)));
    }
    else
    {
        queue_byte((uint8_t)(0xF0 | (cp >> 18)));
        queue_byte((uint8_t)(0x80 | ((cp >> 12) & 0x3F)));
        queue_byte((uint8_t)(0x80 | ((cp >> 6) & 0x3F)));
        queue_byte((uint8_t)(0x80 | (cp & 0x3F)));
    }
}

/* Move console key presses into the queue: with wait, one batch (waiting
 * for it); without, every one already waiting. False on a console error. */
static bool take_waiting_keys(bool wait)
{
    for (;;)
    {
        DWORD waiting = 0;
        if (!wait && (!GetNumberOfConsoleInputEvents(s_in, &waiting) || waiting == 0))
            return true;
        if (wait && WaitForSingleObject(s_in, INFINITE) != WAIT_OBJECT_0)
            return false;
        INPUT_RECORD rec[16];
        DWORD got = 0;
        if (!ReadConsoleInputW(s_in, rec, 16, &got))
            return false;
        for (DWORD i = 0; i < got; i++)
        {
            if (rec[i].EventType != KEY_EVENT)
                continue;
            const KEY_EVENT_RECORD *k = &rec[i].Event.KeyEvent;
            if (!k->bKeyDown || k->uChar.UnicodeChar == 0)
                continue;
            for (WORD r = 0; r < (k->wRepeatCount ? k->wRepeatCount : 1); r++)
                queue_char(k->uChar.UnicodeChar);
        }
        if (wait)
            return true;
    }
}

static int console_read_byte(void *context, uint8_t *byte_out)
{
    (void)context;
    if (!byte_out)
        return -EINVAL;
    if (!s_in_console)
    {                 /* piped input: plain bytes */
        static bool after_cr;
        for (;;)
        {
            DWORD got = 0;
            if (!ReadFile(s_in, byte_out, 1, &got, NULL) || got != 1)
                return -EIO;
            /* Windows text ends lines with CR LF: one Enter, not two. */
            bool skip = after_cr && *byte_out == '\n';
            after_cr = *byte_out == '\r';
            if (!skip)
                return 0;
        }
    }
    while (s_q_count == 0)
        if (!take_waiting_keys(true))
            return -EIO;
    *byte_out = s_queue[s_q_head];
    s_q_head = (s_q_head + 1) % (int)sizeof(s_queue);
    s_q_count--;
    return 0;
}

static int console_write_bytes(void *context, const void *data, size_t length)
{
    (void)context;
    if (length && fwrite(data, 1, length, stdout) != length)
        return -EIO;
    fflush(stdout);
    return 0;
}

/* Lines wrap at the screen buffer's width (in Windows Terminal, the window's). */
static int console_columns(void *context)
{
    (void)context;
    CONSOLE_SCREEN_BUFFER_INFO info;
    if (!s_out || !GetConsoleScreenBufferInfo(s_out, &info))
        return 0;
    return info.dwSize.X;
}

static void raw_input(bool on)
{
    if (!s_in_console)
        return;
    SetConsoleMode(s_in, on ? (ENABLE_VIRTUAL_TERMINAL_INPUT | ENABLE_EXTENDED_FLAGS) : s_in_mode);
    if (on)
        FlushConsoleInputBuffer(s_in);
}

void tdsh_console_raw_mode(bool on)
{
    raw_input(on);
}

bool tdsh_break_requested(void)
{
    if (!s_in_console)
        return false;
    take_waiting_keys(false);
    for (int i = s_q_count - 1; i >= 0; i--)
        if (s_queue[(s_q_head + i) % (int)sizeof(s_queue)] == 0x03)
        {
            /* Drop the keys up to and including it, like a terminal. */
            s_q_head = (s_q_head + i + 1) % (int)sizeof(s_queue);
            s_q_count -= i + 1;
            return true;
        }
    return false;
}

int tdsh_getchar(void)
{
    uint8_t b;
    return console_read_byte(NULL, &b) == 0 ? b : EOF;
}

static void restore_console(void)
{
    if (s_in_console)
        SetConsoleMode(s_in, s_in_mode);
    if (s_out)
        SetConsoleMode(s_out, s_out_mode);
}

static void build_prompt(const tdsh_session_t *s, char *out, size_t cap)
{
    const char marker = strcmp(s->username, "root") == 0 ? '#' : '$';
    char display[TDSH_MAX_PATH];
    size_t hl = strlen(s->home);
    if (strcmp(s->cwd, s->home) == 0)
        snprintf(display, sizeof(display), "~");
    else if (strncmp(s->cwd, s->home, hl) == 0 && s->cwd[hl] == '/')
        snprintf(display, sizeof(display), "~%s", s->cwd + hl);
    else
        snprintf(display, sizeof(display), "%s", s->cwd);
    if (s_color)
        snprintf(out, cap, "\033[1;32m%s@%s\033[0m:\033[1;34m%s\033[0m%c ", s->username, s->hostname, display, marker);
    else
        snprintf(out, cap, "%s@%s:%s%c ", s->username, s->hostname, display, marker);
}

int tdsh_win_run_interactive(tdsh_session_t *session)
{
    if (!session)
        return -EINVAL;
    s_in = GetStdHandle(STD_INPUT_HANDLE);
    s_out = GetStdHandle(STD_OUTPUT_HANDLE);
    s_in_console = GetConsoleMode(s_in, &s_in_mode) != 0;
    bool out_console = GetConsoleMode(s_out, &s_out_mode) != 0;
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    if (out_console)
    {
        SetConsoleMode(s_out, s_out_mode | ENABLE_PROCESSED_OUTPUT | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    }
    else
    {
        s_out = NULL;
    }
    s_color = out_console && getenv("NO_COLOR") == NULL;
    session->terminal_caps = TDSH_TERM_CAP_ANSI | (s_color ? TDSH_TERM_CAP_COLOR : 0);

    const tdsh_terminal_io_t io = {
        .context = NULL,
        .read_byte = console_read_byte,
        .write_bytes = console_write_bytes,
        .columns = console_columns,
    };
    char line[TDSH_MAX_LINE + 2];
    char prompt[TDSH_MAX_PATH + TDSH_HOSTNAME_MAX + TDSH_USERNAME_MAX + 64];
    for (;;)
    {
        build_prompt(session, prompt, sizeof(prompt));
        raw_input(true);
        int n = tdsh_terminal_readline(session, &io, prompt, line, sizeof(line));
        raw_input(false);
        if (n < 0)
            break;
        if (strcmp(line, "exit") == 0)
            break;
        if (line[0])
            (void)tdsh_execute_line(session, line);
        fflush(stdout);
        if (session->logout_requested)
            break;
    }
    restore_console();
    return 0;
}

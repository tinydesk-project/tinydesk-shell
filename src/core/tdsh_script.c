#include "tdsh.h"

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define USCRIPT_MAX_LINES          1024U
#define USCRIPT_MAX_FUNCTIONS      24U
#define USCRIPT_MAX_FUNCTION_DEPTH 8U
#define USCRIPT_MAX_BRANCHES       16U

typedef struct
{
    char *text;
    unsigned long source_line;
} uscript_line_t;

typedef struct
{
    char name[TDSH_VAR_NAME_MAX];
    size_t body_start;
    size_t body_end; /* exclusive; points at the 'end' line */
} uscript_function_t;

typedef struct uscript_frame
{
    int argc;
    char **argv;
    struct uscript_frame *previous;
} uscript_frame_t;

typedef enum
{
    FLOW_NONE = 0,
    FLOW_BREAK,
    FLOW_CONTINUE,
    FLOW_RETURN,
} flow_kind_t;

typedef struct
{
    int status;
    flow_kind_t flow;
} exec_result_t;

typedef struct
{
    tdsh_session_t *session;
    char logical_path[TDSH_MAX_PATH];

    uscript_line_t *lines;
    size_t line_count;
    size_t line_cap;

    uscript_function_t functions[USCRIPT_MAX_FUNCTIONS];
    size_t function_count;

    uscript_frame_t *frame;
    unsigned function_depth;
} uscript_runtime_t;

static exec_result_t execute_range(uscript_runtime_t *rt,
                                   size_t begin, size_t end);

static exec_result_t result_make(int status, flow_kind_t flow)
{
    exec_result_t r = {.status = status, .flow = flow};
    return r;
}

static void trim_inplace(char *text)
{
    if (!text)
        return;
    char *start = text;
    while (*start && isspace((unsigned char)*start))
        start++;
    if (start != text)
        memmove(text, start, strlen(start) + 1U);

    size_t len = strlen(text);
    while (len > 0 && isspace((unsigned char)text[len - 1U]))
    {
        text[--len] = '\0';
    }
}

static bool keyword_line(const char *line, const char *keyword)
{
    if (!line || !keyword)
        return false;
    while (*line && isspace((unsigned char)*line))
        line++;
    size_t n = strlen(keyword);
    if (strncmp(line, keyword, n) != 0)
        return false;
    char c = line[n];
    return c == '\0' || isspace((unsigned char)c);
}

static const char *after_keyword(const char *line, const char *keyword)
{
    while (*line && isspace((unsigned char)*line))
        line++;
    line += strlen(keyword);
    while (*line && isspace((unsigned char)*line))
        line++;
    return line;
}

static void script_error(uscript_runtime_t *rt, size_t index,
                         const char *message)
{
    unsigned long line_no = index < rt->line_count
                                ? rt->lines[index].source_line
                                : 0;
    printf("uscript: %s:%lu: %s\n",
           rt->logical_path, line_no, message);
}

static int script_path(tdsh_session_t *session, const char *input,
                       char *real, size_t real_size,
                       char *logical, size_t logical_size)
{
    int rc = tdsh_path_to_real(session, input, real, real_size,
                               logical, logical_size);
    if (rc != 0)
        return rc;

    struct stat st;
    if (stat(real, &st) != 0)
        return -errno;
    if (!S_ISDIR(st.st_mode))
        return 0;

    /* A folder runs its main.tdsh. */
    char dir_logical[TDSH_MAX_PATH];
    snprintf(dir_logical, sizeof(dir_logical), "%s", logical);
    char new_input[TDSH_MAX_PATH + 16];
    int written = snprintf(new_input, sizeof(new_input), "%s%s%s",
                           dir_logical,
                           strcmp(dir_logical, "/") == 0 ? "" : "/",
                           "main" TDSH_SCRIPT_EXT);
    if (written < 0 || written >= (int)sizeof(new_input))
        return -ENAMETOOLONG;

    rc = tdsh_path_to_real(session, new_input, real, real_size,
                           logical, logical_size);
    if (rc != 0)
        return rc;

    if (stat(real, &st) != 0)
    {
        FILE *f = fopen(real, "w");
        if (!f)
            return -errno;
        fputs("#!/bin/tdsh\n", f);
        fputs("# main.tdsh created by the TinyDesk shell\n", f);
        fclose(f);
    }
    return 0;
}

static void runtime_free(uscript_runtime_t *rt)
{
    if (!rt)
        return;
    for (size_t i = 0; i < rt->line_count; ++i)
        tdsh_free(rt->lines[i].text);
    tdsh_free(rt->lines);
    rt->lines = NULL;
    rt->line_count = rt->line_cap = 0;
}

static int runtime_add_line(uscript_runtime_t *rt,
                            const char *text,
                            unsigned long source_line)
{
    if (rt->line_count >= USCRIPT_MAX_LINES)
        return -E2BIG;
    if (rt->line_count == rt->line_cap)
    {
        size_t new_cap = rt->line_cap ? rt->line_cap * 2U : 64U;
        if (new_cap > USCRIPT_MAX_LINES)
            new_cap = USCRIPT_MAX_LINES;
        uscript_line_t *p = tdsh_realloc(rt->lines, new_cap * sizeof(*p));
        if (!p)
            return -ENOMEM;
        rt->lines = p;
        rt->line_cap = new_cap;
    }

    char *copy = tdsh_strdup(text ? text : "");
    if (!copy)
        return -ENOMEM;
    rt->lines[rt->line_count].text = copy;
    rt->lines[rt->line_count].source_line = source_line;
    rt->line_count++;
    return 0;
}

static int load_script(uscript_runtime_t *rt, FILE *f)
{
    char line[TDSH_MAX_LINE + 2];
    unsigned long line_no = 0;

    while (fgets(line, sizeof(line), f) != NULL)
    {
        line_no++;
        size_t len = strlen(line);
        if (len == TDSH_MAX_LINE + 1U && line[len - 1U] != '\n')
        {
            printf("uscript: %s:%lu: line too long\n",
                   rt->logical_path, line_no);
            return -E2BIG;
        }

        while (len > 0 && (line[len - 1U] == '\n' || line[len - 1U] == '\r'))
        {
            line[--len] = '\0';
        }

        int rc = runtime_add_line(rt, line, line_no);
        if (rc == -ENOMEM)
            printf("uscript: %s:%lu: not enough memory to load the script\n", rt->logical_path, line_no);
        else if (rc == -E2BIG)
            printf("uscript: %s: more than %u lines\n", rt->logical_path, (unsigned)USCRIPT_MAX_LINES);
        if (rc != 0)
            return rc;
    }

    if (ferror(f))
    {
        printf("uscript: %s: read error\n", rt->logical_path);
        return -EIO;
    }
    return 0;
}

static int parse_function_name(const char *line,
                               char *name, size_t name_size)
{
    const char *p = after_keyword(line, "function");
    if (!*p || (!isalpha((unsigned char)*p) && *p != '_'))
        return -EINVAL;

    size_t n = 0;
    while (*p && (isalnum((unsigned char)*p) || *p == '_'))
    {
        if (n + 1U >= name_size)
            return -ENOSPC;
        name[n++] = *p++;
    }
    name[n] = '\0';

    while (*p && isspace((unsigned char)*p))
        p++;
    if (p[0] == '(' && p[1] == ')')
        p += 2;
    while (*p && isspace((unsigned char)*p))
        p++;
    return *p == '\0' ? 0 : -EINVAL;
}

static int find_function_end(uscript_runtime_t *rt, size_t start,
                             size_t *end_out)
{
    unsigned depth = 1;
    for (size_t i = start + 1U; i < rt->line_count; ++i)
    {
        char temp[TDSH_MAX_LINE + 1];
        snprintf(temp, sizeof(temp), "%s", rt->lines[i].text);
        trim_inplace(temp);
        if (!temp[0] || temp[0] == '#')
            continue;

        if (keyword_line(temp, "function"))
            depth++;
        else if (strcmp(temp, "end") == 0)
        {
            if (--depth == 0)
            {
                *end_out = i;
                return 0;
            }
        }
    }
    return -EINVAL;
}

static int discover_functions(uscript_runtime_t *rt)
{
    for (size_t i = 0; i < rt->line_count; ++i)
    {
        char temp[TDSH_MAX_LINE + 1];
        snprintf(temp, sizeof(temp), "%s", rt->lines[i].text);
        trim_inplace(temp);
        if (!keyword_line(temp, "function"))
            continue;

        char name[TDSH_VAR_NAME_MAX];
        if (parse_function_name(temp, name, sizeof(name)) != 0)
        {
            script_error(rt, i, "invalid function declaration");
            return -EINVAL;
        }

        size_t end = 0;
        if (find_function_end(rt, i, &end) != 0)
        {
            script_error(rt, i, "function without matching 'end'");
            return -EINVAL;
        }

        if (rt->function_count >= USCRIPT_MAX_FUNCTIONS)
        {
            script_error(rt, i, "too many functions");
            return -E2BIG;
        }

        for (size_t j = 0; j < rt->function_count; ++j)
        {
            if (strcmp(rt->functions[j].name, name) == 0)
            {
                script_error(rt, i, "duplicate function name");
                return -EEXIST;
            }
        }

        uscript_function_t *fn = &rt->functions[rt->function_count++];
        snprintf(fn->name, sizeof(fn->name), "%s", name);
        fn->body_start = i + 1U;
        fn->body_end = end;
        i = end;
    }
    return 0;
}

static uscript_function_t *find_function(uscript_runtime_t *rt,
                                         const char *name)
{
    if (!rt || !name)
        return NULL;
    for (size_t i = 0; i < rt->function_count; ++i)
    {
        if (strcmp(rt->functions[i].name, name) == 0)
            return &rt->functions[i];
    }
    return NULL;
}

bool tdsh_script_special_var(tdsh_session_t *session,
                             const char *name,
                             char *out, size_t out_size)
{
    if (!session || !name || !out || out_size == 0)
        return false;
    uscript_runtime_t *rt = (uscript_runtime_t *)session->script_runtime;
    if (!rt)
        return false;

    if (strcmp(name, "0") == 0)
    {
        snprintf(out, out_size, "%s", rt->logical_path);
        return true;
    }

    if (strcmp(name, "#") == 0)
    {
        snprintf(out, out_size, "%d", rt->frame ? rt->frame->argc : 0);
        return true;
    }

    if (!isdigit((unsigned char)name[0]))
        return false;
    if (!rt->frame)
    {
        out[0] = '\0';
        return true;
    }
    char *end = NULL;
    long index = strtol(name, &end, 10);
    if (!end || *end != '\0' || index < 0)
        return false;

    if (index > rt->frame->argc)
    {
        out[0] = '\0';
        return true;
    }

    snprintf(out, out_size, "%s", rt->frame->argv[index - 1]);
    return true;
}

bool tdsh_script_try_function(tdsh_session_t *session,
                              int argc, char **argv,
                              int *status_out)
{
    if (!session || argc <= 0 || !argv || !status_out)
        return false;
    uscript_runtime_t *rt = (uscript_runtime_t *)session->script_runtime;
    if (!rt)
        return false;

    uscript_function_t *fn = find_function(rt, argv[0]);
    if (!fn)
        return false;

    if (rt->function_depth >= USCRIPT_MAX_FUNCTION_DEPTH)
    {
        printf("uscript: maximum function recursion depth reached\n");
        *status_out = 2;
        return true;
    }

    uscript_frame_t frame = {
        .argc = argc - 1,
        .argv = argc > 1 ? &argv[1] : NULL,
        .previous = rt->frame,
    };

    rt->frame = &frame;
    rt->function_depth++;
    exec_result_t r = execute_range(rt, fn->body_start, fn->body_end);
    rt->function_depth--;
    rt->frame = frame.previous;

    if (r.flow == FLOW_BREAK || r.flow == FLOW_CONTINUE)
    {
        printf("uscript: break/continue escaped function '%s'\n", fn->name);
        *status_out = 2;
    }
    else
    {
        *status_out = r.status;
    }
    return true;
}

static int find_matching_block(uscript_runtime_t *rt, size_t start,
                               const char *open_kw, const char *close_kw,
                               size_t *end_out)
{
    unsigned depth = 1;
    for (size_t i = start + 1U; i < rt->line_count; ++i)
    {
        char temp[TDSH_MAX_LINE + 1];
        snprintf(temp, sizeof(temp), "%s", rt->lines[i].text);
        trim_inplace(temp);
        if (!temp[0] || temp[0] == '#')
            continue;

        if (keyword_line(temp, open_kw))
            depth++;
        else if (strcmp(temp, close_kw) == 0)
        {
            if (--depth == 0)
            {
                *end_out = i;
                return 0;
            }
        }
    }
    return -EINVAL;
}

static bool numeric_string(const char *s, int64_t *value)
{
    if (!s || !*s)
        return false;
    char *end = NULL;
    errno = 0;
    long long v = strtoll(s, &end, 0);
    if (errno != 0 || end == s || *end != '\0')
        return false;
    if (value)
        *value = (int64_t)v;
    return true;
}

static int eval_condition(uscript_runtime_t *rt, const char *condition,
                          bool *truth_out)
{
    if (!condition || !truth_out)
        return -EINVAL;

    char cond[TDSH_MAX_LINE + 1];
    snprintf(cond, sizeof(cond), "%s", condition);
    trim_inplace(cond);
    if (!cond[0])
        return -EINVAL;

    size_t len = strlen(cond);
    if (len >= 4U && cond[0] == '(' && cond[1] == '(' &&
        cond[len - 2U] == ')' && cond[len - 1U] == ')')
    {
        cond[len - 2U] = '\0';
        int64_t value = 0;
        int rc = tdsh_eval_int_expr(rt->session, cond + 2, &value);
        if (rc != 0)
            return rc;
        *truth_out = value != 0;
        return 0;
    }

    char storage[TDSH_MAX_LINE + 1];
    char *argv[TDSH_MAX_ARGS];
    int argc = 0;
    int rc = tdsh_parse_words(rt->session, cond, storage, sizeof(storage),
                              argv, &argc);
    if (rc != 0 || argc == 0)
        return -EINVAL;

    /* Convenient string/numeric 3-token comparisons. */
    if (argc == 3 &&
        (strcmp(argv[1], "==") == 0 || strcmp(argv[1], "!=") == 0 ||
         strcmp(argv[1], "<") == 0 || strcmp(argv[1], ">") == 0 ||
         strcmp(argv[1], "<=") == 0 || strcmp(argv[1], ">=") == 0))
    {
        int64_t a = 0, b = 0;
        bool na = numeric_string(argv[0], &a);
        bool nb = numeric_string(argv[2], &b);

        if (strcmp(argv[1], "==") == 0)
        {
            *truth_out = (na && nb) ? (a == b) : (strcmp(argv[0], argv[2]) == 0);
        }
        else if (strcmp(argv[1], "!=") == 0)
        {
            *truth_out = (na && nb) ? (a != b) : (strcmp(argv[0], argv[2]) != 0);
        }
        else
        {
            if (!na || !nb)
                return -EINVAL;
            if (strcmp(argv[1], "<") == 0)
                *truth_out = a < b;
            else if (strcmp(argv[1], ">") == 0)
                *truth_out = a > b;
            else if (strcmp(argv[1], "<=") == 0)
                *truth_out = a <= b;
            else
                *truth_out = a >= b;
        }
        return 0;
    }

    /* If it names a shell command or uScript function, status 0 means true. */
    if (tdsh_command_find(argv[0]) || find_function(rt, argv[0]))
    {
        int status = tdsh_execute_line(rt->session, cond);
        *truth_out = status == 0;
        return 0;
    }

    if (strcmp(argv[0], "true") == 0 && argc == 1)
    {
        *truth_out = true;
        return 0;
    }
    if (strcmp(argv[0], "false") == 0 && argc == 1)
    {
        *truth_out = false;
        return 0;
    }

    /* Otherwise treat it as an integer/logical expression. */
    int64_t value = 0;
    rc = tdsh_eval_int_expr(rt->session, cond, &value);
    if (rc != 0)
        return rc;
    *truth_out = value != 0;
    return 0;
}

static exec_result_t execute_if(uscript_runtime_t *rt, size_t start,
                                size_t range_end, size_t *next_out)
{
    size_t endif = 0;
    if (find_matching_block(rt, start, "if", "endif", &endif) != 0 ||
        endif >= range_end)
    {
        script_error(rt, start, "if without matching endif");
        *next_out = range_end;
        return result_make(2, FLOW_NONE);
    }

    size_t boundary[USCRIPT_MAX_BRANCHES];
    const char *conditions[USCRIPT_MAX_BRANCHES];
    bool is_else[USCRIPT_MAX_BRANCHES];
    size_t count = 0;

    boundary[count] = start;
    conditions[count] = after_keyword(rt->lines[start].text, "if");
    is_else[count] = false;
    count++;

    unsigned depth = 0;
    for (size_t i = start + 1U; i < endif; ++i)
    {
        char temp[TDSH_MAX_LINE + 1];
        snprintf(temp, sizeof(temp), "%s", rt->lines[i].text);
        trim_inplace(temp);
        if (!temp[0] || temp[0] == '#')
            continue;

        if (keyword_line(temp, "if"))
        {
            depth++;
            continue;
        }
        if (strcmp(temp, "endif") == 0)
        {
            if (depth > 0)
                depth--;
            continue;
        }

        if (depth == 0 && (keyword_line(temp, "elseif") || strcmp(temp, "else") == 0))
        {
            if (count >= USCRIPT_MAX_BRANCHES)
            {
                script_error(rt, i, "too many if/elseif branches");
                *next_out = endif + 1U;
                return result_make(2, FLOW_NONE);
            }
            boundary[count] = i;
            if (keyword_line(temp, "elseif"))
            {
                conditions[count] = after_keyword(rt->lines[i].text, "elseif");
                is_else[count] = false;
            }
            else
            {
                conditions[count] = NULL;
                is_else[count] = true;
            }
            count++;
        }
    }

    for (size_t b = 0; b < count; ++b)
    {
        bool run = is_else[b];
        if (!run)
        {
            int rc = eval_condition(rt, conditions[b], &run);
            if (rc != 0)
            {
                script_error(rt, boundary[b], "invalid if/elseif condition");
                *next_out = endif + 1U;
                return result_make(2, FLOW_NONE);
            }
        }

        if (run)
        {
            size_t body_begin = boundary[b] + 1U;
            size_t body_end = (b + 1U < count) ? boundary[b + 1U] : endif;
            exec_result_t r = execute_range(rt, body_begin, body_end);
            *next_out = endif + 1U;
            return r;
        }
    }

    *next_out = endif + 1U;
    return result_make(0, FLOW_NONE);
}

static exec_result_t execute_while(uscript_runtime_t *rt, size_t start,
                                   size_t range_end, size_t *next_out)
{
    size_t endwhile = 0;
    if (find_matching_block(rt, start, "while", "endwhile", &endwhile) != 0 ||
        endwhile >= range_end)
    {
        script_error(rt, start, "while without matching endwhile");
        *next_out = range_end;
        return result_make(2, FLOW_NONE);
    }

    const char *condition = after_keyword(rt->lines[start].text, "while");
    int last_status = 0;
    unsigned long iteration = 0;

    for (;;)
    {
        bool truth = false;
        int rc = eval_condition(rt, condition, &truth);
        if (rc != 0)
        {
            script_error(rt, start, "invalid while condition");
            *next_out = endwhile + 1U;
            return result_make(2, FLOW_NONE);
        }
        if (!truth)
            break;

        exec_result_t body = execute_range(rt, start + 1U, endwhile);
        last_status = body.status;

        if (body.flow == FLOW_RETURN)
        {
            *next_out = endwhile + 1U;
            return body;
        }
        if (body.flow == FLOW_BREAK)
            break;
        if (body.flow != FLOW_NONE && body.flow != FLOW_CONTINUE)
        {
            *next_out = endwhile + 1U;
            return body;
        }

        iteration++;
        if ((iteration & 0x3FU) == 0U)
            tdsh_yield();
    }

    *next_out = endwhile + 1U;
    return result_make(last_status, FLOW_NONE);
}

static exec_result_t execute_for(uscript_runtime_t *rt, size_t start,
                                 size_t range_end, size_t *next_out)
{
    size_t endfor = 0;
    if (find_matching_block(rt, start, "for", "endfor", &endfor) != 0 ||
        endfor >= range_end)
    {
        script_error(rt, start, "for without matching endfor");
        *next_out = range_end;
        return result_make(2, FLOW_NONE);
    }

    char storage[TDSH_MAX_LINE + 1];
    char *argv[TDSH_MAX_ARGS];
    int argc = 0;
    int rc = tdsh_parse_words(rt->session, rt->lines[start].text,
                              storage, sizeof(storage), argv, &argc);
    if (rc != 0 || argc < 4 || strcmp(argv[0], "for") != 0 ||
        strcmp(argv[2], "in") != 0)
    {
        script_error(rt, start, "usage: for <variable> in <item ...>");
        *next_out = endfor + 1U;
        return result_make(2, FLOW_NONE);
    }

    const char *var = argv[1];
    if (!isalpha((unsigned char)var[0]) && var[0] != '_')
    {
        script_error(rt, start, "invalid for-loop variable");
        *next_out = endfor + 1U;
        return result_make(2, FLOW_NONE);
    }
    for (const char *p = var + 1; *p; ++p)
    {
        if (!isalnum((unsigned char)*p) && *p != '_')
        {
            script_error(rt, start, "invalid for-loop variable");
            *next_out = endfor + 1U;
            return result_make(2, FLOW_NONE);
        }
    }

    int last_status = 0;
    for (int item = 3; item < argc; ++item)
    {
        rc = tdsh_var_set(rt->session, var, argv[item]);
        if (rc != 0)
        {
            script_error(rt, start, "unable to set for-loop variable");
            *next_out = endfor + 1U;
            return result_make(1, FLOW_NONE);
        }

        exec_result_t body = execute_range(rt, start + 1U, endfor);
        last_status = body.status;
        if (body.flow == FLOW_RETURN)
        {
            *next_out = endfor + 1U;
            return body;
        }
        if (body.flow == FLOW_BREAK)
            break;
        if (body.flow != FLOW_NONE && body.flow != FLOW_CONTINUE)
        {
            *next_out = endfor + 1U;
            return body;
        }
    }

    *next_out = endfor + 1U;
    return result_make(last_status, FLOW_NONE);
}

static exec_result_t execute_range(uscript_runtime_t *rt,
                                   size_t begin, size_t end)
{
    int status = 0;

    for (size_t i = begin; i < end;)
    {
        char line[TDSH_MAX_LINE + 1];
        snprintf(line, sizeof(line), "%s", rt->lines[i].text);
        trim_inplace(line);

        if (!line[0] || line[0] == '#')
        {
            i++;
            continue;
        }

        /* Function definitions are declarations; skip their body at runtime. */
        if (keyword_line(line, "function"))
        {
            size_t fn_end = 0;
            if (find_function_end(rt, i, &fn_end) != 0)
            {
                script_error(rt, i, "function without matching end");
                return result_make(2, FLOW_NONE);
            }
            i = fn_end + 1U;
            continue;
        }

        if (keyword_line(line, "if"))
        {
            size_t next = i + 1U;
            exec_result_t r = execute_if(rt, i, end, &next);
            status = r.status;
            rt->session->last_status = status;
            if (r.flow != FLOW_NONE)
                return r;
            i = next;
            continue;
        }

        if (keyword_line(line, "while"))
        {
            size_t next = i + 1U;
            exec_result_t r = execute_while(rt, i, end, &next);
            status = r.status;
            rt->session->last_status = status;
            if (r.flow != FLOW_NONE)
                return r;
            i = next;
            continue;
        }

        if (keyword_line(line, "for"))
        {
            size_t next = i + 1U;
            exec_result_t r = execute_for(rt, i, end, &next);
            status = r.status;
            rt->session->last_status = status;
            if (r.flow != FLOW_NONE)
                return r;
            i = next;
            continue;
        }

        if (strcmp(line, "break") == 0)
        {
            return result_make(status, FLOW_BREAK);
        }
        if (strcmp(line, "continue") == 0)
        {
            return result_make(status, FLOW_CONTINUE);
        }

        if (keyword_line(line, "return"))
        {
            const char *arg = after_keyword(line, "return");
            int return_status = rt->session->last_status;
            if (*arg)
            {
                int64_t value = 0;
                if (tdsh_eval_int_expr(rt->session, arg, &value) != 0)
                {
                    script_error(rt, i, "return requires an integer expression");
                    return result_make(2, FLOW_RETURN);
                }
                return_status = (int)value;
            }
            rt->session->last_status = return_status;
            return result_make(return_status, FLOW_RETURN);
        }

        /* Stray block terminators are syntax errors in the current range. */
        if (strcmp(line, "endif") == 0 || strcmp(line, "endwhile") == 0 ||
            strcmp(line, "endfor") == 0 || strcmp(line, "end") == 0 ||
            strcmp(line, "else") == 0 || keyword_line(line, "elseif"))
        {
            script_error(rt, i, "unexpected block terminator");
            return result_make(2, FLOW_NONE);
        }

        status = tdsh_execute_line(rt->session, line);
        rt->session->last_status = status;
        if (rt->session->logout_requested)
            return result_make(status, FLOW_NONE);
        i++;
    }

    return result_make(status, FLOW_NONE);
}

int tdsh_run_script_in_session(tdsh_session_t *session, const char *path)
{
    char real[TDSH_MAX_REAL_PATH];
    char logical[TDSH_MAX_PATH];
    int rc = script_path(session, path, real, sizeof(real),
                         logical, sizeof(logical));
    if (rc != 0)
    {
        printf("tdsh: cannot open script '%s': %s\n", path, strerror(-rc));
        return 1;
    }

    FILE *f = fopen(real, "r");
    if (!f)
    {
        printf("tdsh: cannot open script '%s': %s\n", logical, strerror(errno));
        return 1;
    }

    /*
     * Keep the complete runtime on heap rather than the FreeRTOS task stack.
     * The function table and path bookkeeping are persistent for the whole
     * script and do not need to consume stack while nested execution frames
     * are active.
     */
    uscript_runtime_t *rt = tdsh_calloc(1, sizeof(*rt));
    if (!rt)
    {
        fclose(f);
        printf("uscript: out of memory creating runtime\n");
        return 1;
    }

    rt->session = session;
    snprintf(rt->logical_path, sizeof(rt->logical_path), "%s", logical);

    rc = load_script(rt, f);
    fclose(f);
    if (rc != 0)
    {
        runtime_free(rt);
        tdsh_free(rt);
        return 2;
    }

    rc = discover_functions(rt);
    if (rc != 0)
    {
        runtime_free(rt);
        tdsh_free(rt);
        return 2;
    }

    void *previous_runtime = session->script_runtime;
    session->script_runtime = rt;

    exec_result_t r = execute_range(rt, 0, rt->line_count);
    if (r.flow == FLOW_BREAK || r.flow == FLOW_CONTINUE)
    {
        printf("uscript: break/continue used outside a loop\n");
        r.status = 2;
    }
    /* A top-level return simply terminates the script with that status. */

    session->last_status = r.status;
    session->script_runtime = previous_runtime;
    runtime_free(rt);
    tdsh_free(rt);
    return r.status;
}

typedef struct
{
    tdsh_session_t session;
    char path[TDSH_MAX_PATH];
} tdsh_script_job_t;

static int script_job_worker(void *arg)
{
    tdsh_script_job_t *job = (tdsh_script_job_t *)arg;
    return tdsh_run_script_in_session(&job->session, job->path);
}

static void script_job_cleanup(void *arg)
{
    tdsh_script_job_t *job = (tdsh_script_job_t *)arg;
    if (!job)
        return;
    memset(&job->session, 0, sizeof(job->session));
    tdsh_free(job);
}

int tdsh_run_script(tdsh_session_t *session, const char *path, bool background)
{
    if (!session || !path || !path[0])
        return 1;

    tdsh_script_job_t *job = tdsh_calloc(1, sizeof(*job));
    if (!job)
    {
        printf("tdsh: not enough memory for isolated script session\n");
        return 1;
    }
    if (snprintf(job->path, sizeof(job->path), "%s", path) >= (int)sizeof(job->path))
    {
        script_job_cleanup(job);
        printf("tdsh: script path too long\n");
        return 1;
    }
    if (tdsh_session_clone(&job->session, session, false) != 0)
    {
        script_job_cleanup(job);
        return 1;
    }

    const tdsh_core_config_t *cfg = tdsh_core_config();
    const tdsh_platform_api_t *platform = cfg ? cfg->platform : NULL;

    if (platform && platform->worker_run)
    {
        int result = 0;
        int rc = platform->worker_run(platform->context,
                                      background ? "tdsh_bg" : "tdsh_script",
                                      TDSH_SCRIPT_TASK_STACK,
                                      TDSH_SCRIPT_TASK_PRIORITY,
                                      background,
                                      script_job_worker,
                                      job,
                                      script_job_cleanup,
                                      &result);
        if (rc != 0)
        {
            /* worker_run contract: caller retains ownership on start failure. */
            script_job_cleanup(job);
            printf("tdsh: failed to start script worker (%d)\n", rc);
            return 1;
        }
        if (background)
        {
            printf("[tdsh-bg] started %s\n", path);
            return 0;
        }
        return result;
    }

    if (background)
    {
        script_job_cleanup(job);
        printf("tdsh: background scripts are not supported by this platform port\n");
        return 1;
    }

    int result = script_job_worker(job);
    script_job_cleanup(job);
    return result;
}

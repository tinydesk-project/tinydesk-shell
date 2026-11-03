#include "tdsh.h"

#include <errno.h>
#include <stdio.h>
#include <string.h>

static int append_part(char *path, size_t size, const char *part)
{
    size_t len = strlen(path);
    size_t plen = strlen(part);
    if (len == 0)
    {
        if (size < 2)
            return -ENAMETOOLONG;
        path[0] = '/';
        path[1] = '\0';
        len = 1;
    }
    if (len > 1)
    {
        if (len + 1 >= size)
            return -ENAMETOOLONG;
        path[len++] = '/';
        path[len] = '\0';
    }
    if (len + plen >= size)
        return -ENAMETOOLONG;
    memcpy(path + len, part, plen + 1);
    return 0;
}

static int split_normalized(const char *combined,
                            char *logical_out,
                            size_t out_size,
                            size_t minimum_depth)
{
    char work[TDSH_MAX_PATH * 2];
    if (snprintf(work, sizeof(work), "%s", combined) >= (int)sizeof(work))
    {
        return -ENAMETOOLONG;
    }
    char *parts[64];
    size_t depth = 0;
    char *save = NULL;
    char *token = strtok_r(work, "/", &save);
    while (token)
    {
        if (token[0] == '\0' || strcmp(token, ".") == 0)
        {
        }
        else if (strcmp(token, "..") == 0)
        {
            if (depth > minimum_depth)
                depth--;
        }
        else
        {
            if (depth >= sizeof(parts) / sizeof(parts[0]))
                return -ENAMETOOLONG;
            parts[depth++] = token;
        }
        token = strtok_r(NULL, "/", &save);
    }
    if (out_size < 2)
        return -ENAMETOOLONG;
    logical_out[0] = '/';
    logical_out[1] = '\0';
    for (size_t i = 0; i < depth; ++i)
    {
        int rc = append_part(logical_out, out_size, parts[i]);
        if (rc)
            return rc;
    }
    return 0;
}

static bool path_is_home_or_child(const char *path, const char *home)
{
    size_t n = strlen(home);
    return strcmp(path, home) == 0 ||
           (strncmp(path, home, n) == 0 && path[n] == '/');
}

static bool targets_forbidden_tree(const tdsh_session_t *session,
                                   const char *input)
{
    if (!input || input[0] != '/')
        return false;
    if (strcmp(input, "/root") == 0 || strncmp(input, "/root/", 6) == 0)
        return true;
    if (strcmp(input, "/home") == 0)
        return true;
    if (strncmp(input, "/home/", 6) == 0 &&
        !path_is_home_or_child(input, session->home))
        return true;
    return false;
}

int tdsh_path_normalize(tdsh_session_t *session,
                        const char *input,
                        char *logical_out,
                        size_t logical_out_size)
{
    if (!session || !input || !logical_out || logical_out_size < 2)
        return -EINVAL;
    if(!tdsh_session_valid(session))return -EACCES;
    const bool is_root = strcmp(session->username, "root") == 0;
    if(!is_root&&(strchr(input,'\\')||strchr(input,':')))return -EINVAL;
    char combined[TDSH_MAX_PATH * 2];

    if (is_root)
    {
        if (input[0] == '\0')
        {
            if (snprintf(combined, sizeof(combined), "%s", session->cwd) >= (int)sizeof(combined))
                return -ENAMETOOLONG;
        }
        else if (input[0] == '~')
        {
            if (input[1] != '\0' && input[1] != '/')
                return -EINVAL;
            if (snprintf(combined, sizeof(combined), "%s%s", session->home, input + 1) >= (int)sizeof(combined))
                return -ENAMETOOLONG;
        }
        else if (input[0] == '/')
        {
            if (snprintf(combined, sizeof(combined), "%s", input) >= (int)sizeof(combined))
                return -ENAMETOOLONG;
        }
        else if (strcmp(session->cwd, "/") == 0)
        {
            if (snprintf(combined, sizeof(combined), "/%s", input) >= (int)sizeof(combined))
                return -ENAMETOOLONG;
        }
        else
        {
            if (snprintf(combined, sizeof(combined), "%s/%s", session->cwd, input) >= (int)sizeof(combined))
                return -ENAMETOOLONG;
        }
        return split_normalized(combined, logical_out, logical_out_size, 0);
    }

    bool shared=tdsh_session_has_right(session,TDSH_RIGHT_SHARED);
    bool from_shared=shared&&path_is_home_or_child(session->cwd,"/shared");
    bool to_shared=path_is_home_or_child(input,"/shared");
    if(to_shared&&!shared)return -EACCES;
    const char *jail=to_shared||(from_shared&&input[0]!='/'&&input[0]!='~')?"/shared":session->home;
    if (!path_is_home_or_child(session->cwd, session->home)&&!from_shared)
        return -EACCES;

    if (input[0] == '\0')
    {
        if (snprintf(combined, sizeof(combined), "%s", session->cwd) >= (int)sizeof(combined))
            return -ENAMETOOLONG;
    }
    else if (input[0] == '~')
    {
        if (input[1] != '\0' && input[1] != '/')
            return -EINVAL;
        if (snprintf(combined, sizeof(combined), "%s%s", session->home, input + 1) >= (int)sizeof(combined))
            return -ENAMETOOLONG;
    }
    else if (input[0] == '/')
    {
        if (targets_forbidden_tree(session, input))
            return -EACCES;
        if (path_is_home_or_child(input, session->home)||to_shared)
        {
            if (snprintf(combined, sizeof(combined), "%s", input) >= (int)sizeof(combined))
                return -ENAMETOOLONG;
        }
        else if (strcmp(input, "/") == 0)
        {
            if (snprintf(combined, sizeof(combined), "%s", session->home) >= (int)sizeof(combined))
                return -ENAMETOOLONG;
        }
        else
        {
            if (snprintf(combined, sizeof(combined), "%s%s", session->home, input) >= (int)sizeof(combined))
                return -ENAMETOOLONG;
        }
    }
    else
    {
        if (snprintf(combined, sizeof(combined), "%s/%s", session->cwd, input) >= (int)sizeof(combined))
            return -ENAMETOOLONG;
    }

    size_t home_depth = 0;
    for (const char *p = jail; *p; ++p)
        if (*p == '/')
            home_depth++;
    int rc = split_normalized(combined, logical_out, logical_out_size, home_depth);
    if (rc)
        return rc;
    return path_is_home_or_child(logical_out, jail) ? 0 : -EACCES;
}

int tdsh_path_to_real(tdsh_session_t *session,
                      const char *input,
                      char *real_out,
                      size_t real_out_size,
                      char *logical_out,
                      size_t logical_out_size)
{
    if (!real_out || real_out_size == 0)
        return -EINVAL;
    const tdsh_core_config_t *cfg = tdsh_core_config();
    if (!cfg || !cfg->fs_root)
        return -EINVAL;

    char logical_tmp[TDSH_MAX_PATH];
    char *logical = logical_out ? logical_out : logical_tmp;
    size_t logical_size = logical_out ? logical_out_size : sizeof(logical_tmp);
    int rc = tdsh_path_normalize(session, input, logical, logical_size);
    if (rc)
        return rc;

    if (cfg->path_translate &&
        cfg->path_translate(cfg->path_translate_context, logical,
                            real_out, real_out_size))
    {
        return 0;
    }

    size_t root_len = strlen(cfg->fs_root);
    bool root_has_slash = root_len > 0 && cfg->fs_root[root_len - 1] == '/';
    int n;
    if (strcmp(logical, "/") == 0)
    {
        n = snprintf(real_out, real_out_size, "%s", cfg->fs_root);
    }
    else if (root_has_slash)
    {
        n = snprintf(real_out, real_out_size, "%s%s", cfg->fs_root, logical + 1);
    }
    else
    {
        n = snprintf(real_out, real_out_size, "%s%s", cfg->fs_root, logical);
    }
    return (n < 0 || (size_t)n >= real_out_size) ? -ENAMETOOLONG : 0;
}

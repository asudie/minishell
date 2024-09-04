#include "../../incl/minishell.h"

char *get_env_var(char **envr, const char *name) {
    size_t len = strlen(name);
    for (int i = 0; envr[i] != NULL; i++) {
        if (ft_strncmp(envr[i], name, len) == 0 && envr[i][len] == '=') {
            return envr[i] + len + 1;
        }
    }
    return NULL;
}

void set_env_var(char **envr, const char *name, const char *value) {
    size_t len = ft_strlen(name);
    size_t size = ft_strlen(name) + ft_strlen(value) + 1;

    for (int i = 0; envr[i] != NULL; i++) {
        if (ft_strncmp(envr[i], name, len) == 0 && envr[i][len] == '=') { 
            ft_strcpy(envr[i], (char*)name);

            // Append the '=' character
            ft_strlcat(envr[i], "=", size);

            // Append the value
            ft_strlcat(envr[i], value, size);
            return;
        }
    }
    int i = 0;
    while (1) {
        if (envr[i] == NULL) {
            envr[i] = ft_malloc(sizeof(char *));
            snprintf(envr[i], ft_strlen(name) + ft_strlen(value) + 2, "%s=%s", name, value);
            envr[i + 1] = ft_malloc(sizeof(char *));
            envr[i + 1] = NULL;
            return;
        }
        i++;
    }
}
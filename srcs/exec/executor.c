#include "../../incl/minishell.h"
#include <signal.h>
#include <unistd.h>
#include "../../libft/libft.h"
#include <stdio.h> // DELETE
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h> //delete
#include <fcntl.h>

#define PATH_MAX 4096

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

int builtin_cd(t_cmd *cmd) {
    char *home_dir;
    char *oldpwd;
    char cwd[1024];

    if (cmd->args[1] == NULL) {
        home_dir = get_env_var(cmd->envp, "HOME");
        if (home_dir == NULL) {
            ft_printf("cd: HOME not set\n");
            return 1;
        }
        if (chdir(home_dir) != 0) {
            perror("cd");
            return 1;
        }
    } else if (ft_strcmp(cmd->args[1], "-") == 0) {
        oldpwd = get_env_var(cmd->envp, "OLDPWD");
        if (oldpwd == NULL) {
            ft_printf("cd: OLDPWD not set\n");
            return 1;
        }
        if (chdir(oldpwd) != 0) {
            perror("cd");
            return 1;
        }
        ft_printf("%s\n", oldpwd);
    } else {
        if (chdir(cmd->args[1]) != 0) {
            perror("cd");
            return 1;
        }
        
    }
    oldpwd = get_env_var(cmd->envp, "PWD");
    if (oldpwd != NULL) {
        set_env_var(cmd->envp, "OLDPWD", oldpwd);
    }

    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        set_env_var(cmd->envp, "PWD", cwd);
    } else {
        perror("getcwd");
        return 1;
    }

    return 0;
}

int builtin_echo(t_cmd *cmd) {
    int newline = 1;
    int i = 1;

    if (ft_strncmp(cmd->args[1], "-n", 3) == 0) {
        newline = 0;
        i = 2;
    }

    for (; cmd->args[i]; i++) {
        ft_printf("%s", cmd->args[i]);
        if (cmd->args[i + 1] != NULL) { 
            ft_printf(" ");
        }
    }

    if (newline) {
        ft_printf("\n");
    }

    return 1;
}

void builtin_exit() {
    exit(1);
}

int builtin_pwd() {
    char cwd[PATH_MAX];

    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        ft_printf("%s\n", cwd);
    } else {
        perror("getcwd() error");
        return 0;
    }

    return 1;
}

int builtin_env(t_cmd *cmd) {
    for (int i = 0; cmd->envp[i] != NULL; i++) {
        ft_printf("%s\n", cmd->envp[i]);
    }
	return (1);
}

int builtin_export(t_cmd *cmd) {
    int i = 1;

    while (cmd->args[i]) {
        char *name = strdup(cmd->args[i]);
        char *value = ft_strchr(name, '=');

        if (value) {
            *value = '\0';
            value++;
            set_env_var(cmd->envp, name, value);
               
        } else {
            if (getenv(name)) {
            } else {
                ft_printf("export: %s: not found\n", name);
                return 1; 
            }
        }
        i++;
    }

    return 0; 
}

int builtin_unset(t_cmd *cmd) {
    
     if (cmd->args[0] == NULL || *(cmd->args[0]) == '\0' || strchr(cmd->args[0], '=') != NULL) {
        ft_printf("unsetenv: invalid variable name\n");
        return -1;
    }

    size_t len = strlen(cmd->args[1]);
    char **env = cmd->envp;
    char **next_env = cmd->envp;

    while (*env) {
        if (ft_strncmp(*env, cmd->args[1], len) == 0 && (*env)[len] == '=') {
            env++;
            continue;
        }
        *next_env++ = *env++;
    }
    *next_env = NULL;
    return 0;
}

int resolve_full_path(t_cmd *cmd, char **full_path) {
    char	*tmp;
    
    if (access(cmd->args[0], X_OK) == 0)
    {
        *full_path = cmd->args[0];
        return 0;
    } 
            
    char *path = getenv("PATH");
    if (!path) {
        return -1;
    }
    char	**paths = ft_split(path + 5, ':');
    int		i = 0;
    while (paths[i] != NULL)
	{
		tmp = ft_strjoin(paths[i], "/");
		*full_path = ft_strjoin(tmp, cmd->args[0]);
		free(tmp);
		if (access(*full_path, X_OK) == 0) {
           
            ft_free_array(paths);
            return 0;
        }
		free(*full_path);
		i++;
	}
	ft_free_array(paths);
	return (-1);
}


int custom(t_cmd *cmd)
{
    char *full_path;
    
        if (resolve_full_path(cmd, &full_path) == -1) {
            
            ft_printf("Command not found: %s\n", cmd->args[0]);
            return 1;
        }
        if (execve(full_path, cmd->args, cmd->envp) == -1) {
            
            free(full_path);
            perror("execve");
            return 1;
        }
        free(full_path);
    
    return(0);
}

int in_rd(t_cmd *cmd)
{
    int fd = open(cmd->in_rd, O_RDONLY);
    if (fd == -1) {
        perror("open");
        return (1);
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return (1);
    }

    if (pid == 0) {
        if (dup2(fd, STDIN_FILENO) == -1) {
            perror("dup2");
            close(fd);
            return (1);
        }
        close(fd);
        if (execute_builtin(cmd)) {
            
            perror("builtin");
            return (1);
        }
        
        return 0;
    } else { 
        close(fd);
        wait(NULL); 
    }
    return (0);
}

int	execute_builtin(t_cmd *cmd)
{
	if (ft_strncmp(cmd->args[0], "echo", 4) == 0)
	{
        return (builtin_echo(cmd));
	}
    else if (ft_strncmp(cmd->args[0], "pwd", 3) == 0)
	{
		return (builtin_pwd());
	}
    else if (ft_strncmp(cmd->args[0], "env", 3) == 0)
	{
		return (builtin_env(cmd));
	}
    else
    {
        return (custom(cmd)); 
    }
	return (0);
}

int print_file_by_fd(int fd) {
    char buffer[1024];
    ssize_t bytes_read;

    while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
        if (write(STDOUT_FILENO, buffer, bytes_read) != bytes_read) {
            perror("write");
            return (1);
        }
    }

    if (bytes_read == -1) {
        perror("read");
        return (1);
    }
    return (0);
}

int start_exec(t_cmd *cmd)
{
    if(cmd->out_rd)
        return(out_rd(cmd));
    if(cmd->in_rd)
        return(in_rd(cmd));
    return (execute_builtin(cmd));
}


int count_commands(t_cmd *cmd)
{
    t_cmd *it = cmd;
    int num_cmds = 0;

    while (it != NULL) 
    {
        num_cmds++;
        it = it->next;
    }
    return num_cmds;
}

int env_builtins(t_cmd *cmd)
{
    if (ft_strncmp(cmd->args[0], "cd", 2) == 0)
        return (builtin_cd(cmd));
    else if (ft_strncmp(cmd->args[0], "export", 6) == 0)
		return (builtin_export(cmd));
    else if (ft_strncmp(cmd->args[0], "unset", 5) == 0)
		return (builtin_unset(cmd));
    return (1);
}

int	execute_cmd(t_cmd *cmd)
{
	pid_t	pid;
    int     status;
	t_cmd *it = cmd;
    int num_cmds = count_commands(cmd);
    int pipefd[2 * (num_cmds - 1)];
    int i, j;

    for (i = 0; i < (num_cmds - 1); i++) {
        if (pipe(pipefd + i * 2) == -1) {
            perror("pipe");
            return (1);
        }
    }

    i = 0; 

	while (it)
	{
        if (ft_strncmp(it->args[0], "cd", 2) == 0 || ft_strncmp(cmd->args[0], "export", 6) == 0 || ft_strncmp(cmd->args[0], "unset", 5) == 0)
	{
        return(env_builtins(it));
		
	}
        pid = fork();
        if (pid == -1) {
            perror("fork");
            return (1);
        } else if (pid == 0) 
        {
            if (i > 0) {
                dup2(pipefd[(i - 1) * 2], STDIN_FILENO);
            }
            if (i < num_cmds - 1) {
                dup2(pipefd[i * 2 + 1], STDOUT_FILENO);
            }
            for (j = 0; j < 2 * (num_cmds - 1); j++) {
                close(pipefd[j]);
            }
            exit(start_exec(it));  
        }
        it = it->next;
        i++;
    }
    for (j = 0; j < 2 * (num_cmds - 1); j++) {
        close(pipefd[j]);
    }
    for (i = 0; i < num_cmds; i++) {
        waitpid(pid, &status, 0);
    }
    if (WIFEXITED(status)) 
            return(WEXITSTATUS(status));
    return (0);
}



int out_rd(t_cmd *cmd)
{
    int fd;
    int res;
    if(cmd->append)
        fd = open(cmd->out_rd, O_WRONLY | O_APPEND | O_CREAT, 0644);
    else
        fd = open(cmd->out_rd, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        return (1);
    }

    int saved_stdout = dup(STDOUT_FILENO);
    if (saved_stdout == -1) {
        perror("dup");
        close(fd);
        return (1);
    }

    if (dup2(fd, STDOUT_FILENO) == -1) {
        perror("dup2");
        close(fd);
        close(saved_stdout);
        return (1);
    }
    close(fd);
    if(cmd->in_rd)
        res = in_rd(cmd);
    else
        res = execute_builtin(cmd); 
    if (dup2(saved_stdout, STDOUT_FILENO) == -1) {
        perror("dup2");
        close(saved_stdout);
        return (1);
    }
    close(saved_stdout);

    return res;
}

void sigint_handler(int signum) {
    (void)signum;
    write(STDOUT_FILENO, "\n", 1);

    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

void sigquit_handler(int signum) {
    (void)signum;  
}


// LEFT TO IMPLEMENT
// • HEREDOC

// gcc executor.c ../../libft/*.c ../../42_pipex/ft_printf/*.c ../../ft_destructor/*.c -g

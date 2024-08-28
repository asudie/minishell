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

int exit_status = 0;

char *get_env_var(char **envr, const char *name) {
    size_t len = strlen(name);
    for (int i = 0; envr[i] != NULL; i++) {
        if (strncmp(envr[i], name, len) == 0 && envr[i][len] == '=') {
            return envr[i] + len + 1;
        }
    }
    return NULL;
}

// Helper function to set an environment variable
void set_env_var(char **envr, const char *name, const char *value) {
    size_t len = strlen(name);
    for (int i = 0; envr[i] != NULL; i++) {
        if (strncmp(envr[i], name, len) == 0 && envr[i][len] == '=') {
            snprintf(envr[i], strlen(name) + strlen(value) + 2, "%s=%s", name, value);
            return;
        }
    }
    // If not found, add new environment variable
    int i = 0;
    while (1) {
        if (envr[i] == NULL) {
            envr[i] = ft_malloc(sizeof(char *));
            snprintf(envr[i], strlen(name) + strlen(value) + 2, "%s=%s", name, value); // SEGA
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

    

    // If no arguments are provided, change to the home directory
    if (cmd->args[1] == NULL) {
        home_dir = get_env_var(cmd->envp, "HOME");
        if (home_dir == NULL) {
            fprintf(stderr, "cd: HOME not set\n"); // change forbidden
            return 1;
        }
        if (chdir(home_dir) != 0) {
            perror("cd");
            return 1;
        }
    } else if (strcmp(cmd->args[1], "-") == 0) {
        // Handle 'cd -' to change to the previous directory
        oldpwd = get_env_var(cmd->envp, "OLDPWD");
        if (oldpwd == NULL) {
            fprintf(stderr, "cd: OLDPWD not set\n");
            return 1;
        }
        if (chdir(oldpwd) != 0) {
            perror("cd");
            return 1;
        }
        printf("%s\n", oldpwd);
    } else {
        
        // Change to the directory provided in args[1]
        if (chdir(cmd->args[1]) != 0) {
            perror("cd");
            return 1;
        }
        
    }

    // Update the PWD and OLDPWD environment variables
    oldpwd = get_env_var(cmd->envp, "PWD");
    if (oldpwd != NULL) {
        set_env_var(cmd->envp, "OLDPWD", oldpwd);
    }

    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Here %s\n", cwd);
        set_env_var(cmd->envp, "PWD", cwd);
    } else {
        perror("getcwd");
        return 1;
    }

    return 0;
}

int builtin_echo(t_cmd *cmd) {
    int newline = 1; // Flag to determine if we should print a newline
    int i = 1; // Start with the first argument after the program name

    // Check for the -n option
    if (ft_strncmp(cmd->args[1], "-n", 3) == 0) {
        newline = 0;
        i = 2; // Skip the -n argument
    }

    // Print the arguments
    for (; cmd->args[i]; i++) {
        ft_printf("%s", cmd->args[i]);
        if (cmd->args[i + 1] != NULL) { 
            ft_printf(" "); // Print a space between arguments
        }
    }

    // Print the newline if the -n option was not provided
    if (newline) {
        printf("\n");
    }

    return 1;
}

// int builtin_cat(t_cmd *cmd) {
//     char *envp[] = { NULL }; // environment variables (none in this example)
    
//     // Path to the executable
//     char *path = "/bin/cat";
    
//     // Arguments for the executable, including the command itself as the first argument
//     if (execve(path, cmd->args, cmd->envp) == -1) {
//         perror("execve failed");
// 		return 0;
//     }
// 	return (1);
// }

void builtin_exit() {
    exit(1);
}

int builtin_pwd() {
    char cwd[PATH_MAX]; // Buffer to store the current working directory

    // Get the current working directory
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        // Print the current working directory
        ft_printf("%s\n", cwd);
    } else {
        // Handle the error
        perror("getcwd() error");
        return 0;
    }

    return 1;
}

int builtin_env(t_cmd *cmd) {
    for (int i = 0; cmd->envp[i] != NULL; i++) {
        // Print each environment variable
        ft_printf("%s\n", cmd->envp[i]);
    }
	return (1);
}

int builtin_export(t_cmd *cmd) {
    int i = 1; // args[0] is "export", so start with args[1]

    // Loop through all provided arguments
    while (cmd->args[i]) {
        char *name = strdup(cmd->args[i]);
        char *value = ft_strchr(name, '=');

        if (value) {
            // Separate name and value
            *value = '\0';
            value++;

            // Set the environment variable
            set_env_var(cmd->envp, name, value);
               
        } else {
            // Just export the existing variable
            if (getenv(name)) {
                // Do nothing, it's already in the environment
            } else {
                fprintf(stderr, "export: %s: not found\n", name);
                return 1; // Return error status if the variable is not found
            }
        }
        i++;
    }

    return 0; // Return success status
}

int builtin_unset(t_cmd *cmd) {
    
     if (cmd->args[0] == NULL || *(cmd->args[0]) == '\0' || strchr(cmd->args[0], '=') != NULL) {
        fprintf(stderr, "unsetenv: invalid variable name\n");
        return -1;  // Invalid variable name
    }

    size_t len = strlen(cmd->args[1]);
    char **env = cmd->envp;
    char **next_env = cmd->envp;

    // Iterate over the environ array
    while (*env) {
        // Compare the variable name with the current environment variable
        if (strncmp(*env, cmd->args[1], len) == 0 && (*env)[len] == '=') {
            // Found the environment variable to remove
            env++;
            continue;
        }
        // Move the next_env pointer
        *next_env++ = *env++;
    }

    // Null-terminate the new environment array
    *next_env = NULL;
    

    return 0;  // Success
}

int resolve_full_path(t_cmd *cmd, char **full_path) {
    // Check for absolute
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
            
            fprintf(stderr, "Command not found: %s\n", cmd->args[0]);
            return 1;
        }
        
        // Replace the current process image with a new process image
        if (execve(full_path, cmd->args, cmd->envp) == -1) {
            
            free(full_path);
            perror("execve");
            return 1;
        }
        free(full_path);
    
    return(0);
}

int in_rd(t_cmd *cmd) // check if it's working!
{
    int fd = open(cmd->in_rd, O_RDONLY);
    if (fd == -1) {
        perror("open");
        return (1);
    }

       // Fork a child process
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return (1);
    }

    if (pid == 0) { // Child process
        // Redirect stdin to the file descriptor
        if (dup2(fd, STDIN_FILENO) == -1) {
            perror("dup2");
            close(fd);
            return (1);
        }
        close(fd);

        // Execute the command
        if (execute_builtin(cmd)) {
            
            perror("builtin");
            return (1);
        }
        
        return 0;
    } else { // Parent process
        close(fd);
        wait(NULL); // Wait for the child process to finish
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
        // printf("exec_buildin: %d\n", custom(cmd));
        return (custom(cmd)); 
        // return 1;
    }
	return (0);
}

int print_file_by_fd(int fd) {
    char buffer[1024];
    ssize_t bytes_read;

    // Read from the file descriptor in a loop until the end of the file
    while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
        // Write the buffer content to the standard output
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
    // printf("start_execres = %d\n", execute_builtin(cmd));
    return (execute_builtin(cmd));
    // return 0;
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

    // Create pipes
    for (i = 0; i < (num_cmds - 1); i++) {
        if (pipe(pipefd + i * 2) == -1) {
            perror("pipe");
            return (1);
        }
    }

    i = 0; // Initialize i to 0 before loop

	// Iterate through each command
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
            // Child process

            // Redirect input from previous pipe if not the first command
            if (i > 0) {
                dup2(pipefd[(i - 1) * 2], STDIN_FILENO);
            }

            // Redirect output to next pipe if not the last command
            if (i < num_cmds - 1) {
                dup2(pipefd[i * 2 + 1], STDOUT_FILENO);
            }

            // Close all pipe file descriptors
            for (j = 0; j < 2 * (num_cmds - 1); j++) {
                close(pipefd[j]);
            }
            // Execute the command
            return(start_exec(it)); 
        }
        
        // Parent process, move to the next command
        it = it->next;
        i++;
    }

    // Close all pipe file descriptors in the parent
    for (j = 0; j < 2 * (num_cmds - 1); j++) {
        close(pipefd[j]);
    }

    // Wait for all child processes to finish
    for (i = 0; i < num_cmds; i++) {
        waitpid(pid, &status, 0);
    }
    // printf("Exit status: %d\n", exit_status);
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

    // Duplicate the file descriptor to stdout
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

    // Close the target file descriptor as it's no longer needed
    close(fd);

    if(cmd->in_rd)
        res = in_rd(cmd);
    else
        res = execute_builtin(cmd); // here execute
    // print_file_by_fd(saved_stdout);
    // Restore the original stdout
    if (dup2(saved_stdout, STDOUT_FILENO) == -1) {
        perror("dup2");
        close(saved_stdout);
        return (1);
    }

    // Close the saved stdout file descriptor
    close(saved_stdout);

    return res;
}

// void sigint_handler(int signum) {
//     (void)signum;  // Avoid unused parameter warning
//     // Print a newline and a new prompt
//     write(STDOUT_FILENO, "\n", 1);
//     // write(STDOUT_FILENO, "minishell$ ", 11); NEW PROMPT!!!
// }

// void sigquit_handler(int signum) {
//     (void)signum;  // Ignore the signal
// }


// LEFT TO IMPLEMENT

// ◦ ctrl-C displays a new prompt on a new line.
// ◦ ctrl-D exits the shell.
// ◦ ctrl-\ does nothing.
// • Handle $? which should expand to the exit status of the most recently executed
// • HEREDOC
// cd . and ..

// • remove global var for exit code $?-> do when merging with severyn

// gcc executor.c ../../libft/*.c ../../42_pipex/ft_printf/*.c ../../ft_destructor/*.c -g

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

// void	handle_signal(int sig)
// {
// 	if (sig == SIGINT)
// 	{
// 		write(1, "\n", 1);
// 		display_prompt();
// 	}
// }

// void	setup_signal_handling(void)
// {
// 	signal(SIGINT, handle_signal);
// 	signal(SIGQUIT, SIG_IGN);
// }

// void	handle_redirections(t_command *cmd)
// {
// 	int	fd;
// 	int	fd;

// 	if (cmd->in_redirect)
// 	{
// 		fd = open(cmd->in_file, O_RDONLY);
// 		dup2(fd, STDIN_FILENO);
// 		close(fd);
// 	}
// 	if (cmd->out_redirect)
// 	{
// 		fd = open(cmd->out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 		dup2(fd, STDOUT_FILENO);
// 		close(fd);
// 	}
// }



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
            envr[i] = malloc(sizeof(char *));
            snprintf(envr[i], strlen(name) + strlen(value) + 2, "%s=%s", name, value); // SEGA
            envr[i + 1] = malloc(sizeof(char *));
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
            fprintf(stderr, "cd: HOME not set\n");
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
        set_env_var(cmd->envp, "PWD", cwd);
    } else {
        perror("getcwd");
        return 1;
    }

    return 0;
}

int builtin_echo(t_cmd *cmd) {
    char *envp[] = { NULL }; // environment variables (none in this example)
    
    // Path to the executable
    char *path = "/bin/echo";
    
    // Arguments for the executable, including the command itself as the first argument
    if (execve(path, cmd->args, cmd->envp) == -1) {
        perror("execve failed");
		return 0;
    }
	return (1);
}

int builtin_cat(t_cmd *cmd) {
    char *envp[] = { NULL }; // environment variables (none in this example)
    
    // Path to the executable
    char *path = "/bin/cat";
    
    // Arguments for the executable, including the command itself as the first argument
    if (execve(path, cmd->args, cmd->envp) == -1) {
        perror("execve failed");
		return 0;
    }
	return (1);
}

int builtin_exit(t_cmd *cmd) {
    exit;
}

int builtin_pwd(t_cmd *cmd) {
    char *envp[] = { NULL }; // environment variables (none in this example)
    
    // Path to the executable
    char *path = "/bin/pwd";
    
    // Arguments for the executable, including the command itself as the first argument
    if (execve(path, cmd->args, cmd->envp) == -1) {
        perror("execve failed");
		return 0;
    }
	return (1);
}

int builtin_env(t_cmd *cmd) {
    // char *envp[] = { NULL }; // environment variables (none in this example)
    
    // Path to the executable
    char *path = "/bin/env";
    
    // Arguments for the executable, including the command itself as the first argument
    if (execve(path, cmd->args, cmd->envp) == -1) {
        perror("execve failed");
		return 0;
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

int resolve_full_path(char *command, char *full_path) {
    char *path = getenv("PATH");
    
    if (!path) {
        return -1;
    }
    
    char *dir = strtok(path, ":");
    while (dir != NULL) {
        snprintf(full_path, PATH_MAX, "%s/%s", dir, command);
        if (access(full_path, X_OK) == 0) {
            return 0;
        }
        dir = strtok(NULL, ":");
    }
    return -1;
}


int custom(t_cmd *cmd)
{
    
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return -1;
    }
    
    if (pid == 0) { // Child process
        char full_path[PATH_MAX];
        
        if (resolve_full_path(cmd->args[0], full_path) == -1) {
            
            fprintf(stderr, "Command not found: %s\n", cmd->args[0]);
            exit(EXIT_FAILURE);
        }
        
        // doesn't go here!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        // Replace the current process image with a new process image
        if (execve(full_path, cmd->args, cmd->envp) == -1) {
            
            printf("%s\n", full_path);
            perror("execve");
            exit(EXIT_FAILURE);
        }
        
    } else { // Parent process
        // Wait for the child process to complete
        if (wait(NULL) == -1) {
            perror("wait");
            exit(EXIT_FAILURE);
        }
    }
    
    return(0);
}

int in_rd(t_cmd *cmd) // check if it's working!
{
    int fd = open(cmd->in_rd, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

       // Fork a child process
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Child process
        // Redirect stdin to the file descriptor
        if (dup2(fd, STDIN_FILENO) == -1) {
            perror("dup2");
            close(fd);
            exit(EXIT_FAILURE);
        }
        close(fd);

        // Execute the command
        if (execute_builtin(cmd)) {
            
            perror("builtin");
            exit(EXIT_FAILURE);
        }
        
        return 0;
    } else { // Parent process
        close(fd);
        wait(NULL); // Wait for the child process to finish
    }
}

int	execute_builtin(t_cmd *cmd)
{
	if (ft_strncmp(cmd->args[0], "cd", 2) == 0)
	{
		return (builtin_cd(cmd));
	}
	else if (ft_strncmp(cmd->args[0], "echo", 4) == 0)
	{
		return (builtin_echo(cmd));
	}
    else if (ft_strncmp(cmd->args[0], "cat", 4) == 0)
	{
		return (builtin_cat(cmd));
	}
	else if (ft_strncmp(cmd->args[0], "exit", 4) == 0)
	{
		return (1);
	}
    else if (ft_strncmp(cmd->args[0], "pwd", 3) == 0)
	{
		return (builtin_pwd(cmd));
	}
    else if (ft_strncmp(cmd->args[0], "export", 6) == 0)
	{
		return (builtin_export(cmd));
	}
    else if (ft_strncmp(cmd->args[0], "unset", 5) == 0)
	{
		return (builtin_unset(cmd));
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

void print_file_by_fd(int fd) {
    char buffer[1024];
    ssize_t bytes_read;

    // Read from the file descriptor in a loop until the end of the file
    while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
        // Write the buffer content to the standard output
        if (write(STDOUT_FILENO, buffer, bytes_read) != bytes_read) {
            perror("write");
            exit(EXIT_FAILURE);
        }
    }

    if (bytes_read == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }
}

int start_exec(t_cmd *cmd)
{
    if(cmd->out_rd)
        return(out_rd(cmd));
    if(cmd->in_rd)
        return(in_rd(cmd));
    return (execute_builtin(cmd));
}

int	execute_cmd(t_cmd *cmd)
{
	pid_t	pid;
	t_cmd *it = cmd;
    int		input;
	int		output;
	int		fd[2];

    int input = open("input", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    int output = open("output", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (input == -1 || output == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

	// Iterate through each command
    // in pipex  ft_input_process FIX <----------------------------------------------------HERE
	while (it)
	{
        if (pipe(fd) == -1)
		ft_error_output(NULL, "Pipe\n", 1);
        pid = fork();
        if (pid == 0)
            ft_input_process(it, input, fd);
        close(fd[1]);
        waitpid(pid, NULL, 0);
        it = it->next;
        ft_output_process(it, output, fd);
        close(fd[0]);
			if (pid == 0)
			{
				if(start_exec(cmd)) 
                    return (1);
			}
			else if (pid > 0)
			{
				// Parent process
				wait(NULL);
			}
			else
			{
				perror("fork");
			}
			
			// it = it->next;
            // IN FILE = OUT FILE
	}

    // Close the file
    // close(file_fd);
    return (0);
}

void display_prompt(t_cmd *cmd) {
    char *cwd;

    // Get the current working directory
	cwd = get_env_var(cmd->envp, "PWD");
    if (cwd != NULL) {
        // Print the prompt
        printf("\nminishel:[%s]$ ", cwd);
    } else {
        perror("get_env_var");
    }
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
        exit(EXIT_FAILURE);
    }

    // Duplicate the file descriptor to stdout
    int saved_stdout = dup(STDOUT_FILENO);
    if (saved_stdout == -1) {
        perror("dup");
        close(fd);
        exit(EXIT_FAILURE);
    }

    if (dup2(fd, STDOUT_FILENO) == -1) {
        perror("dup2");
        close(fd);
        close(saved_stdout);
        exit(EXIT_FAILURE);
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
        exit(EXIT_FAILURE);
    }

    // Close the saved stdout file descriptor
    close(saved_stdout);

    return res;
}



int	main(int argc, char **argv, char **envp)
{
	t_cmd	cmd;

	// Initialize environment variables
	// init_environment(envp);
	// while (1)
	// {
		// Display prompt
		// display_prompt();
		// // Read input
		// char *input = read_input();
		// // Parse input
		// t_cmd *cmd = parse_input(input); 
		// 
		// cmd = malloc(sizeof(t_cmd));
        // EXAMPLE: ls -l > output.txt
		// cmd.cmd = "ls";
		// cmd.args = (char *[]){"ls", "-l", NULL};
		// cmd.in_rd = NULL;
		// cmd.out_rd = "output.txt";
		// cmd.append = 0;
		// cmd.next = NULL;

		// cmd.cmd = "echo";
		// cmd.args = (char *[]){"echo", "Hello!", NULL};
		// cmd.cmd = "cd";
		// cmd.args = (char *[]){"cd", "/bin"};
		// cmd.cmd = "pwd";
		// cmd.args = (char *[]){"pwd", NULL};
		// cmd.cmd = "env";
		// cmd.args = (char *[]){"env", NULL};
        
		cmd.in_rd = "/home/asmolnya/Projects/minishell/srcs/exec/input.txt";
		cmd.out_rd = NULL;
		cmd.append = 0;
		cmd.next = NULL;
		cmd.envp = envp;
		// display_prompt(&cmd); 
		// Execute cmd
		// execute_cmd(&cmd);
        // cmd.cmd = "unset";
		// cmd.args = (char *[]){"unset", "USER", NULL};
        // cmd.cmd = "export";
        // cmd.args = (char *[]){"export", "MYVAR=3", NULL};
        // if(execute_cmd(&cmd))
        //    return 0;
        // cmd.cmd = "exit";
        // cmd.args = (char *[]){"exit", NULL};
        // if(execute_cmd(&cmd))
        //     return 0;
		cmd.args = (char *[]){"copy", "/home/asmolnya/Projects/minishell/srcs/exec/input.txt", NULL};  // if doesn't work add the PATH
        if(execute_cmd(&cmd))
            return 0; 
        // cmd.append = 1;
        // if(execute_cmd(&cmd))
        //     return 0;
		// display_prompt(&cmd);
		// Free allocated memory
		// free_input(input);
		// free_cmd(cmd);
	// }
	return (0);
}


// LEFT TO IMPLEMENT

// ◦ ctrl-C displays a new prompt on a new line.
// ◦ ctrl-D exits the shell.
// ◦ ctrl-\ does nothing.
// • Handle $? which should expand to the exit status of the most recently executed
// foreground pipeline
// • Implement pipes (| character). The output of each command in the pipeline is
// connected to the input of the next command via a pipe <--------------------------------------------DO THIS


// gcc executor.c ../../libft/*.c ../../42_pipex/*.c -g

#include "incl/minishell.h"
#include "signal.h"
#include <unistd.h>

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

int	execute_builtin(t_cmd *cmd)
{
	if (strcmp(cmd->cmd, "cd") == 0)
	{
		return (builtin_cd(cmd));
	}
	else if (strcmp(cmd->cmd, "echo") == 0)
	{
		return (builtin_echo(cmd));
	}
	else if (strcmp(cmd->cmd, "exit") == 0)
	{
		return (builtin_exit(cmd));
	}
    else if (strcmp(cmd->cmd, "pwd") == 0)
	{
		return (builtin_pwd(cmd));
	}
    else if (strcmp(cmd->cmd, "export") == 0)
	{
		return (builtin_export(cmd));
	}
    else if (strcmp(cmd->cmd, "unset") == 0)
	{
		return (builtin_unset(cmd));
	}
    else if (strcmp(cmd->cmd, "env") == 0)
	{
		return (builtin_env(cmd));
	}
	return (-1);
}

void	execute_cmd(t_cmd *cmd)
{
	pid_t	pid;

	// Iterate through each command
	for (int i = 0; cmd != NULL; i++)
	{
		if (is_builtin(cmd))
		{
			execute_builtin(cmd);
		}
		else
		{
			pid = fork();
			if (pid == 0)
			{
				// Child process
				execve(cmd[i].path, cmd[i].args, environ);
				exit(EXIT_FAILURE);
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
		}
	}
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
		// -------------------------------------------------------------------
		// cmd = malloc(sizeof(t_cmd));
        // EXAMPLE: ls -l > output.txt
		cmd.cmd = "ls";
		cmd.args = (char *[]){"ls", "-l", NULL};
		cmd.in_rd = NULL;
		cmd.out_rd = "output.txt";
		cmd.append = 0;
		cmd.next = NULL;
		// Execute cmd
		execute_cmd(&cmd);
		// Free allocated memory
		// free_input(input);
		// free_cmd(cmd);
	// }
	return (0);
}

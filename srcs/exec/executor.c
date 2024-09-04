#include "../../incl/minishell.h"

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

// int print_file_by_fd(int fd) {
//     char buffer[1024];
//     ssize_t bytes_read;

//     while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
//         if (write(STDOUT_FILENO, buffer, bytes_read) != bytes_read) {
//             perror("write");
//             return (1);
//         }
//     }

//     if (bytes_read == -1) {
//         perror("read");
//         return (1);
//     }
//     return (0);
// }

int	start_exec(t_cmd *cmd)
{
	if (cmd->out_rd)
		return (out_rd(cmd));
	if (cmd->in_rd)
		return (in_rd(cmd));
	return (execute_builtin(cmd));
}

int	count_commands(t_cmd *cmd)
{
	t_cmd	*it;
	int		num_cmds;

	it = cmd;
	num_cmds = 0;
	while (it != NULL)
	{
		num_cmds++;
		it = it->next;
	}
	return (num_cmds);
}

int	env_builtins(t_cmd *cmd)
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
	int		status;
	t_cmd	*it;
	int		num_cmds;
	

	it = cmd;
	num_cmds = count_commands(cmd);
    int		pipefd[2 * (num_cmds - 1)];
	int i, j;
	for (i = 0; i < (num_cmds - 1); i++)
	{
		if (pipe(pipefd + i * 2) == -1)
		{
			perror("pipe");
			return (1);
		}
	}
	i = 0;
	while (it)
	{
		if (ft_strncmp(it->args[0], "cd", 2) == 0 || ft_strncmp(cmd->args[0],
				"export", 6) == 0 || ft_strncmp(cmd->args[0], "unset", 5) == 0)
		{
			return (env_builtins(it));
		}
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			return (1);
		}
		else if (pid == 0)
		{
			if (i > 0)
			{
				dup2(pipefd[(i - 1) * 2], STDIN_FILENO);
			}
			if (i < num_cmds - 1)
			{
				dup2(pipefd[i * 2 + 1], STDOUT_FILENO);
			}
			for (j = 0; j < 2 * (num_cmds - 1); j++)
			{
				close(pipefd[j]);
			}
			exit(start_exec(it));
		}
		it = it->next;
		i++;
	}
	for (j = 0; j < 2 * (num_cmds - 1); j++)
	{
		close(pipefd[j]);
	}
	for (i = 0; i < num_cmds; i++)
	{
		waitpid(pid, &status, 0);
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}

void	sigint_handler(int signum)
{
	(void)signum;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigquit_handler(int signum)
{
	(void)signum;
}

// LEFT TO IMPLEMENT
// • HEREDOC


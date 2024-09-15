#include "../../incl/minishell.h"

int	out_rd(t_cmd *cmd)
{
	int	fd;
	int	res;
	int	saved_stdout;

	if (open_for_fd(&fd, cmd, &saved_stdout))
		return (1);
	if (cmd->in_rd)
		res = in_rd(cmd);
	else
		res = execute_builtin(cmd);
	if (dup2(saved_stdout, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(saved_stdout);
		return (1);
	}
	close(saved_stdout);
	return (res);
}

int	open_for_fd(int *fd, t_cmd *cmd, int *saved_stdout)
{
	if (cmd->append)
		*fd = open(cmd->out_rd, O_WRONLY | O_APPEND | O_CREAT, 0644);
	else
		*fd = open(cmd->out_rd, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*fd == -1)
	{
		perror("open");
		return (1);
	}
	*saved_stdout = dup(STDOUT_FILENO);
	if (*saved_stdout == -1)
	{
		perror("dup");
		close(*fd);
		return (1);
	}
	if (dup2(*fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(*fd);
		close(*saved_stdout);
		return (1);
	}
	close(*fd);
	return (0);
}

void	ft_heredoc(t_cmd *cmd)
{
	char	*line;
	char	*limiter;
	int		tmp_fd;

	limiter = cmd->in_rd;
	tmp_fd = open("/tmp/heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		line = readline("heredoc> ");
		if (!line || ft_strcmp(line, limiter) == 0)
		{
			free(line);
			break ;
		}
		write(tmp_fd, line, ft_strlen(line));
		write(tmp_fd, "\n", 1);
		free(line);
	}
	close(tmp_fd);
}

int	open_file_ro_and_pid(int *fd, t_cmd *cmd, pid_t *pid)
{
	if (cmd->heredoc)
	{
		ft_heredoc(cmd);
		*fd = open("/tmp/heredoc_tmp", O_RDONLY, 0644);
		if (cmd->out_rd)
		{
			cmd->in_rd = "/tmp/heredoc_tmp";
			cmd->heredoc = 0;
			return (out_rd(cmd));
		}
	}
	else
		*fd = open(cmd->in_rd, O_RDONLY, 0644);
	if (*fd == -1)
	{
		perror("open");
		return (1);
	}
	*pid = fork();
	if (*pid == -1)
	{
		perror("fork");
		return (1);
	}
	return (0);
}

int	in_rd(t_cmd *cmd)
{
	pid_t	pid;
	int		fd;

	if (open_file_ro_and_pid(&fd, cmd, &pid))
		return (1);
	if (pid == 0)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			perror("dup2");
			close(fd);
			return (1);
		}
		close(fd);
		if (execute_builtin(cmd))
		{
			perror("builtin");
			return (1);
		}
		return (0);
	}
	close(fd);
	wait(NULL);
	return (0);
}

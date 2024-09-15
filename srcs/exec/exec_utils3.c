/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 21:30:55 by asmolnya          #+#    #+#             */
/*   Updated: 2024/09/15 22:04:28 by svalchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	start_exec(t_cmd *cmd)
{
	if (cmd->out_rd && !cmd->heredoc)
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
	if (ft_strcmp(cmd->args[0], "cd") == 0)
		return (builtin_cd(cmd));
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		return (builtin_export(cmd));
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		return (builtin_unset(cmd));
	return (1);
}

int	fork_and_execute(t_cmd *it, int *pipefd, int i, int num_cmds)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	else if (pid == 0)
	{
		if (setup_child_pipes(pipefd, i, num_cmds))
			exit(1);
		close_all_pipes(pipefd, num_cmds);
		exit(start_exec(it));
	}
	return (0);
}

int	wait_for_children(int num_cmds)
{
	int	status;
	int	exit;
	int	i;

	i = 0;
	exit = 0;
	while (i < num_cmds)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
			exit = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			exit = 128 + WTERMSIG(status);
		i++;
	}
	return (exit);
}

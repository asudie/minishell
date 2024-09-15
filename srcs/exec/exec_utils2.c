/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 21:27:31 by asmolnya          #+#    #+#             */
/*   Updated: 2024/09/15 21:45:27 by svalchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	setup_env(t_cmd *cmd)
{
	t_cmd	*it;

	it = cmd;
	while (it->next)
	{
		it->next->envp = it->envp;
		it = it->next;
	}
}

int	create_pipes(int **pipefd, int num_cmds)
{
	int	i;

	*pipefd = (int *)ft_malloc(2 * (num_cmds - 1) * sizeof(int));
	if (!*pipefd)
	{
		perror("malloc");
		return (1);
	}
	i = 0;
	while (i < (num_cmds - 1))
	{
		if (pipe(*pipefd + i * 2) == -1)
		{
			perror("pipe");
			return (1);
		}
		i++;
	}
	return (0);
}

int	handle_builtin_commands(t_cmd *cmd)
{
	if (cmd->args[0])
	{
		if (ft_strcmp(cmd->args[0], "cd") == 0 || ft_strcmp(cmd->args[0],
				"export") == 0 || ft_strcmp(cmd->args[0], "unset") == 0)
			return (1);
	}
	return (0);
}

void	close_all_pipes(int *pipefd, int num_cmds)
{
	int	j;

	j = 0;
	while (j < 2 * (num_cmds - 1))
	{
		close(pipefd[j]);
		j++;
	}
	ft_free(pipefd);
}

int	setup_child_pipes(int *pipefd, int i, int num_cmds)
{
	if (i > 0)
	{
		if (dup2(pipefd[(i - 1) * 2], STDIN_FILENO) == -1)
		{
			perror("dup2");
			return (1);
		}
	}
	if (i < num_cmds - 1)
	{
		if (dup2(pipefd[i * 2 + 1], STDOUT_FILENO) == -1)
		{
			perror("dup2");
			return (1);
		}
	}
	return (0);
}

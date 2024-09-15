/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 21:22:00 by asmolnya          #+#    #+#             */
/*   Updated: 2024/09/15 22:05:03 by svalchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int			g_sig;

int	execute_builtin(t_cmd *cmd)
{
	if (cmd->args[0])
	{
		if (ft_strcmp(cmd->args[0], "echo") == 0)
			return (builtin_echo(cmd));
		else if (ft_strcmp(cmd->args[0], "pwd") == 0)
			return (builtin_pwd());
		else if (ft_strcmp(cmd->args[0], "env") == 0)
			return (builtin_env(cmd));
		else
			return (custom(cmd));
	}
	return (0);
}

int	execute_cmd(t_cmd *cmd)
{
	t_cmd	*it;
	int		num_cmds;
	int		*pipefd;
	int		exit;
	int		i;

	it = cmd;
	exit = 0;
	num_cmds = count_commands(cmd);
	setup_env(cmd);
	if (create_pipes(&pipefd, num_cmds))
		return (1);
	i = 0;
	while (it)
	{
		if (handle_builtin_commands(it))
			return (env_builtins(it));
		if (fork_and_execute(it, pipefd, i, num_cmds))
			return (1);
		it = it->next;
		i++;
	}
	close_all_pipes(pipefd, num_cmds);
	exit = wait_for_children(num_cmds);
	return (exit);
}

void	sigint_handler(int signum)
{
	if (signum == SIGCHLD)
		g_sig = SIGCHLD;
	else if (signum == SIGINT)
	{
		write(1, "\n", 1);
		wait(NULL);
		if (g_sig == SIGCHLD)
		{
			g_sig = 0;
			return ;
		}
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_sig = 0;
	}
}

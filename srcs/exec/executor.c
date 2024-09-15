/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmolnya <asmolnya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 21:22:00 by asmolnya          #+#    #+#             */
/*   Updated: 2024/09/15 21:37:47 by asmolnya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int			g_sig;

int	execute_builtin(t_cmd *cmd)
{
	if (cmd->args[0])
	{
		if (ft_strncmp(cmd->args[0], "echo", 4) == 0)
			return (builtin_echo(cmd));
		else if (ft_strncmp(cmd->args[0], "pwd", 3) == 0)
			return (builtin_pwd());
		else if (ft_strncmp(cmd->args[0], "env", 3) == 0)
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
	int		i;

	it = cmd;
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
	wait_for_children(num_cmds);
	return (0);
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

void	sigquit_handler(int signum)
{
	(void)signum;
}

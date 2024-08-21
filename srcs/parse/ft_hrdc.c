/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hrdc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 14:51:49 by svalchuk          #+#    #+#             */
/*   Updated: 2024/08/21 20:10:59 by svalchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	ft_handle_heredocs(t_mhell *mhell)
{
	int	status;

	status = __success;
	if (!ft_create_heredoc_files(mhell))
		return (__system_call_error);
	if (mhell->hrdc)
		status = ft_read_heredocs(mhell);
	if (status != __success)
		mhell->exit_code = 1;
	return (status);
}

static int	ft_read_heredocs(t_mhell *mhell)
{
	pid_t	pid;
	int		stat;
	int		exit_code;
	
	stat = 0;
	exit_code = 0;
	pid = fork();
	if (pid == -1)
		return (printf(ER ER_HRDC_FK), false);
	if (pid == 0)
		ft_process_heredoc_reading(mhell);
	signal(SIGINT, ft_sigint);
	waitpid(pid, &stat, 0);
	ft_get_exit_code(&exit_code, stat, true, true);
	ft_set_mhell_signals();
	if (exit_code == 1)
		return (__system_call_error);
	else if (exit_code > 1)
		return (_stop_exec);
	return (__success);
}

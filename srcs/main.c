/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c		                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ****** <******@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 22:22:44 by ******           #+#    #+#              */
/*   Updated: 2024/07/22 00:43:38 by ******           ###   ########.fr       */
/*                                                                           */
/* ************************************************************************** */

#include "../incl/minishell.h"

static int		ft_minihell(t_mhell *mhell);
static t_mhell	*ft_init_minihell(t_mhell *mhell, char **envp);

int	main(int argc, char **argv, char **envp)
{
	t_mhell	mhell;

	if (argv && argc > 1)
		return (printf(ER ER_ARG), EXIT_FAILURE);
	ft_alloc_init();
	return (ft_minihell(ft_init_minihell(&mhell, envp)));
}

static int	ft_minihell(t_mhell *mhell)
{
	while (1)
	{
		mhell->cmd_line = ft_input_prompt(mhell);
		if (ft_input_parse(mhell))
		{
			// mhell->exit_code = execute_cmd(mhell->cmd, envp);
		}
		// ft_clean_cmd_data(mhell);
		ft_free(mhell->cmd_line);
	}
	ft_destructor();
	return (mhell->exit_code);
}

static t_mhell	*ft_init_minihell(t_mhell *mhell, char **envp)
{
	mhell->cmd_line = NULL;
	mhell->exit_code = EXIT_SUCCESS;
	mhell->envp = envp;
	mhell->env = NULL;
	mhell->tkn_l = 0;
	mhell->tkn = NULL;
	mhell->cmd_l = 0;
	mhell->cmd = NULL;
	ft_init_env(mhell, envp);
	return (mhell);
}

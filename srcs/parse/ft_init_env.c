/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:33:41 by svalchuk          #+#    #+#             */
/*   Updated: 2024/07/13 15:21:46 by svalchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static char	**ft_get_env(char **envp);

void	ft_init_env(t_mhell *mhell, char **envp)
{
	char	**env;
	int		i;

	i = 0;
	env = ft_get_env(envp);
	while (env[i])
	{
		(void)mhell;
		i++;
	}
}

static char	**ft_get_env(char **envp)
{
	char	**env;

	if (!envp || !*envp)
	{
		env = ft_malloc(sizeof(char *) * 9);
		env[0] = ft_strdup("PATH=/usr/bin:/bin:/usr/sbin:/sbin");
		env[1] = ft_strdup("PWD=/");
		env[2] = ft_strdup("SHLVL=1");
		env[3] = ft_strdup("HOME=/");
		env[4] = ft_strdup("LOGNAME=user");
		env[5] = ft_strdup("USER=user");
		env[6] = ft_strdup("LANG=C");
		env[7] = ft_strdup("TERM=xterm-256color");
		env = NULL;
		return (env);
	}
	else
		return (envp);
}

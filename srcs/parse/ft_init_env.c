/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:33:41 by svalchuk          #+#    #+#             */
/*   Updated: 2024/07/19 15:02:27 by svalchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static char	**ft_get_env(char **envp);
static int	ft_fill(t_env **env, char *str);
static void	ft_set_lvl(t_mhell *mhell);

void	ft_init_env(t_mhell *mhell, char **envp)
{
	char	**env;
	int		i;

	i = 0;
	env = ft_get_env(envp);
	while (env[i])
	{
		if (ft_fill(&mhell->env, env[i]))
		{
			ft_envclean(&mhell->env);
			printf(ER ER_ALLOC);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	ft_set_lvl(mhell);
}

static char	**ft_get_env(char **envp)
{
	char	**env;

	if (envp && *envp)
		return (envp);
	else
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
		env[8] = NULL;
		return (env);
	}
}

static int	ft_fill(t_env **env, char *str)
{
	char	*var;
	char	*val;
	int		code;
	int		div;

	code = EXIT_SUCCESS;
	div = ft_chrpos(str, '=');
	if (div >= 0)
	{
		var = ft_substr(str, 0, div - 1);
		val = ft_strdup(&(str[div]));
		if (!var || !val)
			code = EXIT_FAILURE;
	}
	else
	{
		var = ft_strdup((char *)str);
		val = NULL;
		if (!var)
			code = EXIT_FAILURE;
	}
	if (code != EXIT_FAILURE)
		ft_envadd(env, var, val);
	return (code);
}

static void	ft_set_lvl(t_mhell *mhell)
{
	t_env	*shlvl;
	int		lvl;

	shlvl = ft_find_env(mhell->env, "SHLVL");
	lvl = ft_atoi(shlvl->val);
	if (lvl == 999)
	{
		printf(YELLOW"minishell: "RESET CYAN);
		printf("warning: shell level (1000) too high, resetting to 1\n"RESET);
		lvl = 0;
	}
	ft_free(shlvl->val);
	shlvl->val = ft_itoa(lvl + 1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_ext.c		                           	    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ****** <******@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 22:22:44 by ******           #+#    #+#              */
/*   Updated: 2024/07/22 00:43:38 by ******           ###   ########.fr       */
/*                                                                           */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int		is_valid_n_flag(char *arg);
void	print_arguments(char **args, int start);

int	builtin_echo(t_cmd *cmd)
{
	int	newline;
	int	i;

	i = 1;
	newline = 1;
	while (cmd->args[i] && is_valid_n_flag(cmd->args[i]))
	{
		newline = 0;
		i++;
	}
	print_arguments(cmd->args, i);
	if (newline)
		ft_printf("\n");
	return (0);
}

int	builtin_pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		ft_printf("%s\n", cwd);
	}
	else
	{
		perror("getcwd() error");
		return (1);
	}
	return (0);
}

int	builtin_env(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->envp[i] != NULL)
	{
		ft_printf("%s\n", cmd->envp[i]);
		i++;
	}
	return (0);
}

int	builtin_export(t_cmd *cmd)
{
	char	*value;
	char	*name;
	int		i;

	i = 0;
	while (cmd->args[++i])
	{
		name = ft_strdup(cmd->args[i]);
		value = ft_strchr(name, '=');
		if (value)
		{
			*value = '\0';
			value++;
			set_env_var(cmd->envp, name, value);
		}
		else
		{
			if (getenv(name))
			{
			}
			else
				return (printf("export: %s: not found\n", name), 1);
		}
	}
	return (0);
}

int	builtin_unset(t_cmd *cmd)
{
	size_t	len;
	char	**env;
	char	**next_env;

	if (cmd->args[0] == NULL || *(cmd->args[0]) == '\0'
		|| ft_strchr(cmd->args[0], '=') != NULL)
	{
		ft_printf("unsetenv: invalid variable name\n");
		return (-1);
	}
	len = ft_strlen(cmd->args[1]);
	env = cmd->envp;
	next_env = cmd->envp;
	while (*env)
	{
		if (ft_strncmp(*env, cmd->args[1], len) == 0 && (*env)[len] == '=')
		{
			env++;
			continue ;
		}
		*next_env++ = *env++;
	}
	*next_env = NULL;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_func.c		                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ****** <******@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 22:22:44 by ******           #+#    #+#              */
/*   Updated: 2024/07/22 00:43:38 by ******           ###   ########.fr       */
/*                                                                           */
/* ************************************************************************** */

#include "../../incl/minishell.h"

char	*get_env_var(char **envr, const char *name)
{
	size_t	len;
	int		i;

	i = 0;
	len = ft_strlen(name);
	while (envr[i] != NULL)
	{
		if (ft_strncmp(envr[i], name, len) == 0 && envr[i][len] == '=')
			return (envr[i] + len + 1);
		i++;
	}
	return (NULL);
}

void	add_new_env_var(char **envr, const char *name,
				const char *value, size_t size)
{
	int	i;

	i = 0;
	while (1)
	{
		if (envr[i] == NULL)
		{
			envr[i] = ft_malloc(sizeof(char *));
			snprintf(envr[i], size, "%s=%s", name, value);
			envr[i + 1] = ft_malloc(sizeof(char *));
			envr[i + 1] = NULL;
			return ;
		}
		i++;
	}
}

void	set_env_var(char **envr, const char *name, const char *value)
{
	size_t	len;
	size_t	size;
	int		i;

	i = 0;
	len = ft_strlen(name);
	size = ft_strlen(name) + ft_strlen(value) + 2;
	while (envr[i] != NULL)
	{
		if (ft_strncmp(envr[i], name, len) == 0 && envr[i][len] == '=')
		{
			ft_strcpy(envr[i], (char *)name);
			ft_strlcat(envr[i], "=", size);
			ft_strlcat(envr[i], value, size);
			return ;
		}
		i++;
	}
	add_new_env_var(envr, name, value, size);
}

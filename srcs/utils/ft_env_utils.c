/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:39:12 by svalchuk          #+#    #+#             */
/*   Updated: 2024/07/15 15:49:53 by svalchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

t_env	*ft_find_env(t_env *env, char *var)
{
	size_t	len;

	len = ft_strlen(var);
	while (env)
	{
		if (len == ft_strlen(env->var) && !ft_strncmp(var, env->var, len))
			return (env);
		env = env->next;
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:39:12 by svalchuk          #+#    #+#             */
/*   Updated: 2024/08/09 19:15:56 by svalchuk         ###   ########.fr       */
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

void	ft_envadd(t_env **env, char *var, char *val)
{
	t_env	*head;
	t_env	*node;

	head = *env;
	node = ft_malloc(sizeof(t_env));
	if (!head)
		*env = node;
	else
	{
		while (head->next)
			head = head->next;
		head->next = node;
	}
	node->var = var;
	node->val = val;
	node->next = NULL;
}

void	ft_envclean(t_env **env)
{
	t_env	*tmp;

	while ((*env))
	{
		tmp = (*env)->next;
		ft_free((*env)->var);
		if ((*env)->val)
			ft_free((*env)->val);
		ft_free(*env);
		*env = tmp;
	}
}

char	*ft_envcut(char *str)
{
	char	*name;
	int		i;

	i = 0;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	name = ft_substr(str, 0, i);
	if (!name)
		exit(printf(ER ER_ALLOC));
	return (name);
}

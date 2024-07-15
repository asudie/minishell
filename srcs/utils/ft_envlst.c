/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envlst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:22:36 by svalchuk          #+#    #+#             */
/*   Updated: 2024/07/15 15:43:30 by svalchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dollar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 17:52:28 by svalchuk          #+#    #+#             */
/*   Updated: 2024/08/09 19:14:11 by svalchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static int	ft_not_replace(char *str, int state);
static char	*ft_replace(t_mhell *mhell, char *str);
static int	ft_question_mark(char *str);
static char	*ft_replace_var(char *str, int *i, t_env *env);

void	ft_substr_dollar(t_mhell *mhell, char **str, int state)
{
	char	*new;
	int		i;

	i = ft_not_replace(*str, state);
	if (i >= 0)
		new = ft_strdup(&(*str)[i]);
	else
		new = ft_replace(mhell, *str);
	if (!new)
		exit(printf(ER ER_ALLOC));
	i = 0;
	while ((*str)[i])
	{
		ft_quote_state((*str)[i], &state);
		i++;
	}
	ft_free(*str);
	*str = new;
}

static int	ft_not_replace(char *str, int state)
{
	if (str[0] != '$')
		return (0);
	else if (ft_is_space(str[1]) || !str[1] || state == 1
		|| (state && (ft_is_spec(&str[1]) || ft_is_quote(str[1]))))
		return (0);
	else if (!ft_isalnum(str[1]) && !ft_is_quote(str[1])
		&& !ft_is_spec(str) && (str[1] != '?'))
		return (0);
	else if (state == 0 && (ft_is_spec(str) || ft_is_quote(str[1])))
		return (1);
	return (-1);
}

static char	*ft_replace(t_mhell *mhell, char *str)
{
	char	*substr;
	int		i;

	substr = NULL;
	if (str[1] == '?')
	{
		i = ft_question_mark(str);
		substr = ft_itoa(mhell->exit_code);
	}
	else
	{
		i = 1;
		substr = ft_replace_var(str, &i, mhell->env);
	}
	return (ft_strjoin(substr, &str[i]));
}

static int	ft_question_mark(char *str)
{
	if (str[2])
		return (2);
	else
		return (ft_strlen(str));
}

static char	*ft_replace_var(char *str, int *i, t_env *env)
{
	t_env	*target;
	char	*find;

	find = ft_envcut(&str[*i]);
	target = ft_find_env(env, find);
	*i += ft_strlen(find);
	ft_free(find);
	if (!target || !target->val)
		find = ft_calloc(sizeof(char), 1);
	else
		find = ft_strdup(target->val);
	return (find);
}

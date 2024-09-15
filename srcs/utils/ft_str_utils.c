/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 20:38:01 by svalchuk          #+#    #+#             */
/*   Updated: 2024/08/09 19:15:01 by svalchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

bool	ft_is_empty(char *str)
{
	if (!str)
		return (true);
	while (*str && ft_is_space(*str))
		str++;
	if (*str)
		return (false);
	return (true);
}

bool	ft_is_space(char c)
{
	return (c == '\t' || c == ' ');
}

void	ft_skip_spaces(char **str)
{
	while (ft_is_space(**str))
		*str += 1;
}

bool	ft_is_quote(char c)
{
	return (c == '\'' || c == '"');
}

int	ft_is_spec(char *str)
{
	if (*str == '|')
		return (1);
	else if (*str == '<')
	{
		if (*(str + 1) && ((*(str + 1) == '<') || *(str + 1) == '>'))
			return (2);
		return (1);
	}
	else if (*str == '>')
	{
		if (*(str + 1) && *(str + 1) == '>')
			return (2);
		return (1);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:22:44 by svalchuk          #+#    #+#             */
/*   Updated: 2024/09/15 17:23:48 by svalchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	ft_quote_state(int c, int *state)
{
	if (c == '\'')
	{
		if (*state == 1)
			*state = 0;
		else if (*state == 0)
			*state = 1;
	}
	if (c == '\"')
	{
		if (*state == 2)
			*state = 0;
		else if (*state == 0)
			*state = 2;
	}
}

int	ft_conc_space(char curr, char next)
{
	if (ft_is_space(curr) && ft_is_space(next))
		return (1);
	else
		return (0);
}

int	ft_strchr_pos(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != (unsigned char)c && s[i])
		i++;
	if (s[i] == (unsigned char)c)
		return (++i);
	return (-1);
}

int	ft_isdigit_loop(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

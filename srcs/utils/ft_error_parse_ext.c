/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_parse_ext.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 15:14:37 by svalchuk          #+#    #+#             */
/*   Updated: 2024/07/19 16:20:55 by svalchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static bool	ft_in_red(const char *str, int i);
static bool	ft_out_red(const char *str, int i);

bool	ft_check_oper(const char *str)
{
	int	state;
	int nb;
	int	i;

	i = 0;
	state = 0;
	nb = 0;
	while (str[i])
	{
		ft_quote_state(str[i], &state);
		if (state == 0 && (str[i] == '<' || str[i] == '>'))
		{
			if (str[i] == '<')
				return (ft_in_red(str, i));
			else if (str[i] == '>')
				return (ft_out_red(str, i));
		}
		else if (state == 0 && str[i] == '|')
		{
			if (nb > 1)
			{
				printf(ER_MHELL ER_SX_CHR, '|');
				return (false);
			}
			nb++;
		}
		i++;
	}
	return (true);
}

static bool	ft_in_red(const char *str, int i)
{
	int nb;

	nb = 0;
	while (str[i] && str[i] == '<')
	{
		nb++;
		i++;
	}
	if (nb >= 3)
	{
		if (nb >= 3 && nb <= 4)
			printf(ER_MHELL ER_SX_CHR, '<');
		else if (nb == 5)
			printf(ER_MHELL ER_SX_STR, "<<");
		else if (nb >= 6)
			printf(ER_MHELL ER_SX_STR, "<<<");
		return (false);
	}
	return (true);
}

static bool	ft_out_red(const char *str, int i)
{
	int nb;

	nb = 0;
	while (str[i] && str[i] == '>')
	{
		nb++;
		i++;
	}
	if (nb >= 3)
	{
		if (nb == 3)
			printf(ER_MHELL ER_SX_CHR, '>');
		else if (nb >= 4)
			printf(ER_MHELL ER_SX_STR, ">>");
		return (false);
	}
	return (true);
	return (true);
}

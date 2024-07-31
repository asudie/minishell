/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_parse_ext.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 15:14:37 by svalchuk          #+#    #+#             */
/*   Updated: 2024/07/31 12:00:23 by svalchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static bool	ft_pipe_nb(const char *str);
static bool	ft_redirects(const char *str);
static bool	ft_rdin(const char *str);
static bool	ft_rdout(const char *str);

bool	ft_check_oper(const char *str)
{
	int	state;
	int	i;

	i = 0;
	state = 0;
	if (!ft_pipe_nb(str))
		return (printf(ER_MHELL ER_SX_CHR, '|'), false);
	if (!ft_redirects(str))
		return (false);
	return (true);
}

static bool	ft_pipe_nb(const char *str)
{
	int	state;
	int	i;

	i = -1;
	state = 0;
	while (str[++i])
	{
		ft_quote_state(str[i], &state);
		if (state == 0 && str[i] == '|')
		{
			i++;
			while (ft_is_space(str[i]))
				i++;
			if (str[i] == '|')
				return (false);
		}
	}
	return (true);
}

static bool	ft_redirects(const char *str)
{
	int	state;
	int	i;

	i = -1;
	state = 0;
	while(str[++i])
	{
		ft_quote_state(str[i], &state);
		if (state == 0 && str[i] == '<' && !ft_rdin(str))
			return (false);
		if (state == 0 && str[i] == '>' && !ft_rdout(str))
			return (false);
	}
	return (true);
}

static bool	ft_rdin(const char *str)
{
	(void)str;
	return (true);
}

static bool	ft_rdout(const char *str)
{
	(void)str;
	return (true);
}

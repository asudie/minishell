/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 21:38:22 by svalchuk          #+#    #+#             */
/*   Updated: 2024/09/10 17:32:13 by svalchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static bool	ft_check_pipe(char *input);
static bool	ft_unclosed_quotes(char *str);
static bool	ft_invalid_chars(char *str);
static bool	ft_pipe_nb(char *str);

bool	ft_input_error(t_mhell *mhell, char	*input)
{
	if (!input || ft_is_empty(input))
		return (false);
	if (!ft_check_pipe(input) || !ft_unclosed_quotes(input)
		|| !ft_invalid_chars(input) || !ft_pipe_nb(input))
		return (mhell->exit_code = 2, false);
	return (true);
}

static bool	ft_check_pipe(char *input)
{
	if (input[0] == '|')
		return (printf(ER_MHELL ER_SX_CHR, '|'), false);
	return (true);
}

static bool	ft_unclosed_quotes(char *str)
{
	int	state;
	int	i;

	i = -1;
	state = 0;
	while (str[++i])
		ft_quote_state(str[i], &state);
	if (state == 1)
		return (printf(ER_MHELL ER_QUOTE_S), false);
	else if (state == 2)
		return (printf(ER_MHELL ER_QUOTE_D), false);
	return (true);
}

static bool	ft_invalid_chars(char *str)
{
	char	*chars;
	int		state;
	int		i;
	int		j;

	i = 0;
	state = 0;
	chars = ";\\&";
	while (str[i])
	{
		ft_quote_state(str[i], &state);
		j = 0;
		while (state == 0 && chars[j])
		{
			if (str[i] == chars[j])
				return (printf(ER_MHELL ER_SX_CHR, chars[j]), false);
			j++;
		}
		i++;
	}
	return (true);
}

static bool	ft_pipe_nb(char *str)
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
				return (printf(ER_MHELL ER_SX_CHR, '|'), false);
		}
	}
	return (true);
}

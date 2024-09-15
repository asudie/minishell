/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_parse_ext.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 17:07:43 by svalchuk          #+#    #+#             */
/*   Updated: 2024/09/14 17:57:53 by svalchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static bool	ft_invalid_redir(char *input);
static bool	ft_unexpected_redir(char *input);

bool	ft_redir(char *input)
{
	if (!ft_invalid_redir(input) || !ft_unexpected_redir(input))
		return (false);
	return (true);
}

static bool	ft_invalid_redir(char *input)
{
	(void)input;
	return (true);
}

static bool	ft_unexpected_redir(char *input)
{
	int	state;
	int	i;

	i = 0;
	state = 0;
	while (input[i])
	{
		ft_quote_state(input[i], &state);
		if ((state == 0 && input[i] == '>') || (state == 0 && input[i] == '<'))
		{
			if ((input[i] == '>' && input[i + 1] == '<') || \
				(input[i] == '<' && input[i + 1] == '>'))
				return (printf(ER_MHELL ER_SX_CHR, input[i + 1]), false);
		}
		i++;
	}
	return (true);
}

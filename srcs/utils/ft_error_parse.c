/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 21:38:22 by svalchuk          #+#    #+#             */
/*   Updated: 2024/07/17 21:55:45 by svalchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static int	ft_unclosed_quotes(char *str);

bool	ft_input_error(t_mhell *mhell, char	*input)
{
	bool	res;

	res = false;
	if (ft_is_empty(input))
		res = true;
	else if (ft_unclosed_quotes(input))
	{
		printf("unclosed quotes\n");
		mhell->exit_code = 2;
		res = true;
	}
	else if (ft_invalid_syntax(input))
	{
		mhell->exit_code = 2;
		res = true;
	}
	if (res == true)
		ft_free(input);
	return (input);
}

static int	ft_unclosed_quotes(char *str)
{
	int	i;
	int	s;
	int	d;

	i = -1;
	s = 0;
	d = 0;
	while (str[++i])
	{
		if (str[i] == '\'' && !d)
			s = (s + 1) % 2;
		if (str[i] == '"' && !s)
			d = (d + 1) % 2;
	}
	return (s || d);
}

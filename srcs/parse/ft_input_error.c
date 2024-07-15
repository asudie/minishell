/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:11:16 by svalchuk          #+#    #+#             */
/*   Updated: 2024/07/15 16:37:23 by svalchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static int	ft_quotess_check(char *str);
static int	ft_symbol_check(char *str);
static int	ft_empty_str(char *str);

int	ft_input_error(t_mhell *mhell, char *input)
{
	int quote;
	int	symbol;

	quote = 0;
	symbol = 0;
	quote = ft_quotess_check(input);
	symbol = ft_symbol_check(input);
	if (quote || symbol)
	{
		mhell->exit_code = 2;
		if (quote)
			printf("syntax error unable to locate closing quotation\n");
		else if (symbol)
			printf("syntax error near unexpected token `%s'\n", (char *)&symbol);
	}
	else if (ft_empty_str(input))
		mhell->exit_code = 0;
	else
		return (0);
	return (1);
}

static int	ft_quotess_check(char *str)
{
	int	sngl;
	int	dbl;
	int	i;

	i = 0;
	dbl = 0;
	sngl = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !dbl)
			sngl = (sngl + 1) % 2;
		if (str[i] == '\"' && !sngl)
			dbl = (dbl + 1) % 2;
		i++;
	}
	return (sngl || dbl);
}

static int	ft_symbol_check(char *str)
{
	char	q;
	int		i;

	i = 0;
	q = '\0';
	while (str[i])
	{
		ft_quote_type(str[i], &q);
		if ((str[i] == '&' || str[i] == ';' || str[i] == '\\') && !q)
			return (str[i]);
		i++;
	}
	return (0);
}

static int	ft_empty_str(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while (str[i] && ft_space(str[i]))
		i++;
	if (str[i])
		return (0);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_symb_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:27:32 by svalchuk          #+#    #+#             */
/*   Updated: 2024/07/15 16:37:08 by svalchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int ft_space(char c)
{
	return (c == ' ' || c == '\t');
}

int ft_quote(char c)
{
	if (c == '\"')
		return ('\"');
	if (c == '\'')
		return ('\'');
	return (0);
}

void	ft_quote_type(char c, char *q)
{
	if ((ft_quote(c)) && !*q)
		*q = c;
	else if ((ft_quote(c)) && *q == c)
		*q = '\0';
}

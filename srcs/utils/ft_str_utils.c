/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 20:38:01 by svalchuk          #+#    #+#             */
/*   Updated: 2024/07/17 20:42:02 by svalchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	ft_is_empty(char *str)
{
	if (!str)
		return (1);
	while (*str)
	{
		if (*str != ' ' || *str != '\t')
			return (0);
		str++;
	}
	return (1);
}

int	ft_is_quote(char c)
{
	return (c == '\'' || c == '"');
}

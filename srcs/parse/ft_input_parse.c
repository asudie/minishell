/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:39:55 by svalchuk          #+#    #+#             */
/*   Updated: 2024/07/15 17:30:03 by svalchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	ft_input_parse(t_mhell *mhell, char *input)
{
	char	*res;
	char	err;

	if (ft_input_error(mhell, input))
		return (0);
	res = ft_input_trim(input);
	return (ft_free(res), 1);
}

static char	*ft_input_trim(char *str)
{
	char	*res;
	char	q;
	int		d;
	int		i;
	
	i = 0;
	d = 0;
	q = '\0';
	res = NULL;
	ft_init_res(&res, str);
	while (str[i])
	{
		ft_quote_type(str[i], &q);
		if (!(((ft_space(str[i]) && ft_space(str[i + 1])) || (ft_space(str[i]) && (!d || !str[i + 1]))) && !q))
		{
			res[d++] = str[i];
		}
		i++;
	}
	return (res);
}

static void ft_init_res(char **dst, char *src)
{
	char	q;
	int		d;
	int		i;
}

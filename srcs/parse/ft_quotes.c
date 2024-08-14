/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 18:14:17 by svalchuk          #+#    #+#             */
/*   Updated: 2024/08/14 19:04:42 by svalchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static void	ft_tkn_quotes(t_tkn *tkn);
static char	*ft_alloc_new_tkn(t_tkn tkn);

void	ft_open_quotes(t_mhell *mhell)
{
	int	i;

	i = -1;
	while (++i < mhell->tkn_l)
		ft_tkn_quotes(&mhell->tkn[i]);
}

static void	ft_tkn_quotes(t_tkn *tkn)
{
	int		state;
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	state = 0;
	if (tkn->type > _text)
		return ;
	str = ft_alloc_new_tkn(*tkn);
	while (tkn->token[i])
	{
		ft_quote_state(tkn->token[i], &state);
		if (((state == 1 && tkn->token[i] != '\'') || (state == 2 && tkn->token[i] != '"')) || (state == 0 && ft_is_spec(&tkn->token[i]) == 0))
		{
			str[j] = tkn->token[i];
			j++;
		}
		ft_quote_state(tkn->token[i], &state);
		i++;
	}
	ft_free(tkn->token);
	tkn->token = str;
}

static char	*ft_alloc_new_tkn(t_tkn tkn)
{
	char	*str;
	int		state;
	int		len;

	len = 0;
	state = 0;
	while (*tkn.token && tkn.type == _text)
	{
		if (((state == 1 && *tkn.token != '\'') || (state == 2 && *tkn.token != '"')) || (state == 0 && ft_is_spec(&*tkn.token) == 0))
			len++;
		ft_quote_state(*tkn.token, &state);
		tkn.token++;
	}
	str = ft_calloc(sizeof(char), len + 1);
	if (!str)
		exit(printf(ER ER_ALLOC));
	return (str);
}

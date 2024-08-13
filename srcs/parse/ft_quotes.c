/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 18:14:17 by svalchuk          #+#    #+#             */
/*   Updated: 2024/08/13 19:01:18 by svalchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static void	ft_tkn_quotes(t_tkn *tkn);
static char	*ft_alloc_new_tkn(t_tkn tkn);

void	ft_open_quotes(t_mhell *mhell)
{
	int	i;

	i = 0;
	while (i++ < mhell->tkn_l)
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
	if (tkn->type > text)
		return ;
	str = ft_alloc_new_tkn(*tkn);
	while (tkn->token[i++])
	{
		if (!(((state == 1 && tkn->token[i] == '\'') || (state == 2 && tkn->token[i] == '"')) || (state == 0 && tkn->token[i] == ft_is_quote(tkn->token[i]))))
		{
			str[j] = tkn->token[i];
			j++;
		}
		ft_quote_state(tkn->token[i], &state);
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
	while (*tkn.token && tkn.type == text)
	{
		if (!(((state == 1 && *tkn.token == '\'') || (state == 2 && *tkn.token == '"')) || (state == 0 && *tkn.token == ft_is_quote(*tkn.token))))
			len++;
		ft_quote_state(*tkn.token, &state);
		tkn.token++;
	}
	str = ft_calloc(sizeof(char), len + 1);
	if (!str)
		exit(printf(ER ER_ALLOC));
	return (str);
}

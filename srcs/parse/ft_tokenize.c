/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 15:22:12 by svalchuk          #+#    #+#             */
/*   Updated: 2024/08/11 14:37:29 by svalchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static void		ft_prep_token_arr(t_mhell *mhell, char *str);
static int		ft_strskip(char *str);
static t_type	ft_token_type(char *str);

void	ft_tokenize(t_mhell *mhell, char *str)
{
	int	i;
	int	len;
	int	index;

	i = -1;
	index = 0;
	ft_prep_token_arr(mhell, str);
	while (str[++i])
	{
		if (ft_is_space(str[i]))
			continue ;
		mhell->tkn[index].type = ft_token_type(&str[i]);
		len = ft_is_spec(&str[i]);
		if (!len)
			len = ft_strskip(&str[i]);
		mhell->tkn[index].token = ft_substr(str, i, len--);
		i += len;
		index++;
	}
}

static void	ft_prep_token_arr(t_mhell *mhell, char *str)
{
	int	len;
	int	i;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (ft_is_space(str[i]))
			continue ;
		if (ft_is_spec(&str[i]))
		{
			if (ft_is_spec(&str[i]) == 2)
				i++;
		}
		else
			i += ft_strskip(&str[i]) - 1;
		len++;
		i++;
	}
	mhell->tkn = ft_malloc(sizeof(t_tkn) * len);
	mhell->tkn_l = len;
}

static int	ft_strskip(char *str)
{
	int	state;
	int	i;

	i = 0;
	state = 0;
	while (str[i] && !ft_is_space(str[i]) && !ft_is_space(str[i]))
	{
		ft_quote_state(str[i], &state);
		if (state != 0)
		{
			i++;
			while (str[i] && state != 0)
				i++;
			ft_quote_state(str[i], &state);
		}
		i++;
	}
	return (i);
}

static t_type	ft_token_type(char *str)
{
	if (*str == '|')
		return (pipe);
	else if (*str == *(str + 1) && *str == '<')
		return (hrdc);
	else if (*str == '<')
		return (rdin);
	else if (*str == *(str + 1) && *str == '>')
		return (append);
	else if (*str == '>')
		return (rdout);
	else
		return (text);
}

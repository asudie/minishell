/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 22:22:44 by svalchuk          #+#    #+#             */
/*   Updated: 2024/08/13 18:13:18 by svalchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static char	*ft_trim_input(char *str);
static void	ft_prep_input(char **input, char *str);
static void	ft_replace_dollar(t_mhell *mhell, char **str);
static int	ft_token_order(t_mhell *mhell);

bool	ft_input_parse(t_mhell *mhell)
{
	char	*input;
	int		order;

	if (ft_input_error(mhell, mhell->cmd_line))
		return (false);
	input = ft_trim_input(mhell->cmd_line);
	ft_replace_dollar(mhell, &input);
	if (!*input)
		return (mhell->exit_code = 0, ft_free(input), false);
	ft_tokenize(mhell, input);
	order = ft_token_order(mhell);
	if (order >= 0)
	{
		if (ft_hrdc(mhell, order))
			return (false);
	}
	ft_open_quotes(mhell);
	if (order < 0)
		ft_create_cmd(mhell);
	mhell->exit_code = 0;
	return (ft_free(input), true);
}

static char	*ft_trim_input(char *str)
{
	char	*input;
	int		state;
	int		len;
	int		i;

	i = 0;
	len = 0;
	state = 0;
	input = NULL;
	ft_prep_input(&input, str);
	while (str[i])
	{
		ft_quote_state(str[i], &state);
		if (!(state == 0 && (ft_conc_space(str[i], str[i + 1])
					|| (ft_is_space(str[i]) && (!len || !str[i + 1])))))
			input[len++] = str[i];
		i++;
	}
	return (str);
}

static void	ft_prep_input(char **input, char *str)
{
	int	state;
	int	len;
	int	i;

	i = 0;
	len = 0;
	state = 0;
	if (!str)
		return ;
	while (str[i])
	{
		ft_quote_state(str[i], &state);
		if (!(state == 0 && (ft_conc_space(str[i], str[i + 1])
					|| (ft_is_space(str[i]) && (!len || !str[i + 1])))))
			len++;
		i++;
	}
	*input = (char *)ft_calloc(sizeof(char), len + 1);
	if (!*input)
		exit(printf(ER ER_ALLOC));
}

static void	ft_replace_dollar(t_mhell *mhell, char **str)
{
	char	**arr;
	int		state;
	int		i;

	arr = ft_split_savediv(*str, '$');
	i = 0;
	state = 0;
	while (arr[i])
	{
		ft_substr_dollar(mhell, &arr[i], state);
		i++;
	}
	ft_free(*str);
	*str = ft_arrjoin(arr);
	ft_free_array(arr);
}

static int	ft_token_order(t_mhell *mhell)
{
	t_tkn	*tkn;
	int		i;

	i = 0;
	tkn = mhell->tkn;
	while (i < mhell->tkn_l)
	{
		if (tkn[i].type == pipe && ((i - 1) < 0 || (i + 1) >= mhell->tkn_l))
			return (printf(ER_MHELL ER_SX_STR, tkn[i].token), mhell->exit_code = 2);
		else if (tkn[i].type > pipe && (i + 1) >= mhell->tkn_l)
			return (printf(ER_MHELL ER_SX_STR, "newline"), mhell->exit_code = 2);
		else if (tkn[i].type > pipe && mhell->tkn[i + 1].type > 1)
			return (printf(ER_MHELL ER_SX_STR, tkn[i + 1].token), mhell->exit_code = 2);
		i++;
	}
	return (-1);
}

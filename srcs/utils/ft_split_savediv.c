/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_savediv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 17:51:13 by svalchuk          #+#    #+#             */
/*   Updated: 2024/08/09 19:15:37 by svalchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static int	ft_prep_savediv(char ***input, char *str, char c);

char	**ft_split_savediv(char *str, char c)
{
	char	**arr;
	int		index;
	int		len;
	int		nb;
	int		i;

	nb = ft_prep_savediv(&arr, str, c);
	i = 0;
	index = 0;
	while (nb)
	{
		if (!i && str[i] != c)
			len = ft_strchr_pos(&str[i], c) - 1;
		else
			len = ft_strchr_pos(&str[i + 1], c);
		arr[index] = ft_substr(str, i, len);
		if (!arr[index])
			exit(printf(ER ER_ALLOC));
		i += len;
		index++;
		nb--;
	}
	return (arr);
}

static int	ft_prep_savediv(char ***input, char *str, char c)
{
	int	len;
	int	i;

	i = 0;
	len = 1;
	if (str && str[0] == c)
		i++;
	while (str[i])
	{
		if (str[i] == c)
			len++;
		i++;
	}
	*input = (char **)ft_calloc(sizeof(char *), len + 1);
	if (!*input)
		exit(printf(ER ER_ALLOC));
	return (len);
}

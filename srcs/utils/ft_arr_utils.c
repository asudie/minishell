/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arr_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 15:17:57 by svalchuk          #+#    #+#             */
/*   Updated: 2024/08/08 18:17:38 by svalchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

char	*ft_arrjoin(char **arr)
{
	char	*str;
	int		i;

	i = 0;
	while (arr[i])
	{
		if (!i)
			str = ft_strdup(arr[i]);
		if (arr[i + 1])
			str = ft_strjoin(str, arr[i + 1]);
		if (!str)
			exit(printf(ER ER_ALLOC));
		i++;
	}
	return (str);
}

void	ft_free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		ft_free(arr[i]);
		i++;
	}
	ft_free(arr);
}

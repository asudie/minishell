/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:22:26 by svalchuk          #+#    #+#             */
/*   Updated: 2023/11/18 14:18:14 by svalchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

// #include <string.h>
// #include <stdio.h>
// int	main(void)
// {
// 	char i[] = "one two three";
// 	int orig = strlen(i);
// 	int my = ft_strlen(i);
// 	printf("%i\n", orig);
// 	printf("%i\n", my);
// 	return (0);
// }

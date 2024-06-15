/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:57:32 by svalchuk          #+#    #+#             */
/*   Updated: 2024/02/28 18:46:06 by svalchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
		return (c -= 32);
	else
		return (c);
}

// #include <ctype.h>
// #include <stdio.h>
// int	main(void)
// {
// 	int i = 97;
// 	printf("%c\n", i);
// 	printf("%c\n", i);
// 	int orig = toupper(i);
// 	int my = ft_toupper(i);
// 	printf("%c\n", orig);
// 	printf("%c\n", my);
// 	return (0);
// }

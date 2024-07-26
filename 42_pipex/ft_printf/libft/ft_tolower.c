/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:57:32 by svalchuk          #+#    #+#             */
/*   Updated: 2023/11/13 18:28:49 by svalchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		return (c += 32);
	else
		return (c);
}

// #include <ctype.h>
// #include <stdio.h>
// int	main(void)
// {
// 	int i = 66;
// 	printf("%c\n", i);
// 	printf("%c\n", i);
// 	int orig = tolower(i);
// 	int my = ft_tolower(i);
// 	printf("%c\n", orig);
// 	printf("%c\n", my);
// 	return (0);
// }

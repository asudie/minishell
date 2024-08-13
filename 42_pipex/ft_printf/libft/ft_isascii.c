/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 10:56:47 by svalchuk          #+#    #+#             */
/*   Updated: 2023/11/13 11:42:54 by svalchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	else
		return (0);
}

// #include <ctype.h>
// #include <stdio.h>
// int	main(void)
// {
// 	int i = 66;
// 	int orig = isascii(i);
// 	int my = ft_isascii(i);
// 	printf("%i\n", orig);
// 	printf("%i\n", my);
// 	return (0);
// }

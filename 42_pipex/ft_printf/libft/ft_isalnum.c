/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 10:53:46 by svalchuk          #+#    #+#             */
/*   Updated: 2023/11/13 12:34:05 by svalchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c >= 48 && c <= 57))
		return (1);
	else
		return (0);
}

// #include <ctype.h>
// #include <stdio.h>
// int	main(void)
// {
// 	int i = 100;
// 	int orig = isalnum(i);
// 	int my = ft_isalnum(i);
// 	printf("%i\n", orig);
// 	printf("%i\n", my);
// 	return (0);
// }

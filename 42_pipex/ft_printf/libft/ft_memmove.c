/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:56:35 by svalchuk          #+#    #+#             */
/*   Updated: 2023/12/01 16:58:44 by svalchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	if (dst == NULL && src == NULL)
		return (0);
	i = 0;
	if (src < dst)
	{
		i = len;
		while (i > 0)
		{
			i--;
			((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		}
	}
	else
	{
		i = 0;
		while (i < len)
		{
			((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	return (dst);
}

// #include <stdio.h>
// #include <string.h>
// int main() {
//     char source[] = "Hello, World!";
//     char destination[20];
// 	char source_orig[] = "Hello, World!";
//     char destination_orig[20];

// 	printf("Orig Func:\n");
//     printf("Source: %s\n", source_orig);
//     memmove(destination_orig, source_orig, 13);
//     printf("Destination: %s\n", destination_orig);

// 	printf("My Func:\n");
//     printf("Source: %s\n", source);
//     ft_memmove(destination, source, 13);
//     printf("Destination: %s\n", destination);

//     return 0;
// }

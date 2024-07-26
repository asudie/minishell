/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:57:06 by svalchuk          #+#    #+#             */
/*   Updated: 2023/11/22 13:36:43 by svalchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// size_t	ft_strlen(const char *str)
// {
// 	size_t	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		i++;
// 	}
// 	return (i);
// }

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize != 0)
	{
		while (src[i] && i < (dstsize - 1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}

// #include <stdio.h>
// #include <string.h>
// int main() {
//     char source[] = "lorem ipsum dolor sit amet";
//     char dest_ft[20];
//     char dest_std[20];

//     // Using your custom ft_strlcpy function
//     size_t copied_ft = ft_strlcpy(dest_ft, "lorem ipsum dolor sit amet", 0);

//     // Using the standard library's strlcpy function
//     size_t copied_std = strlcpy(dest_std, "lorem ipsum dolor sit amet", 0);

//     printf("Custom ft_strlcpy - Copied: %zu\n", copied_ft);
//     printf("Custom ft_strlcpy - Destination: %s\n", dest_ft);

//     printf("Standard strlcpy - Copied: %zu\n", copied_std);
//     printf("Standard strlcpy - Destination: %s\n", dest_std);

//     return 0;
// }

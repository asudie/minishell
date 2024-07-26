/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:57:05 by svalchuk          #+#    #+#             */
/*   Updated: 2023/11/22 13:36:50 by svalchuk         ###   ########.fr       */
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

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	n;
	char	*temp;

	temp = (char *)src;
	i = 0;
	n = 0;
	while (i < dstsize && dst[i])
		i++;
	while ((i + n + 1) < dstsize && src[n])
	{
		dst[i + n] = src[n];
		n++;
	}
	if (i != dstsize)
	{
		dst[i + n] = '\0';
	}
	return (i + ft_strlen(temp));
}

// #include <stdio.h>
// #include <string.h>
// int main() {
//     char dest_ft[20] = "Hello, ";
//     char dest_std[20] = "Hello, ";
//     char source[] = "World!";

//     // Using your custom ft_strlcat function
//     size_t concatenated_ft = ft_strlcat(dest_ft, source, sizeof(dest_ft));

//     // Using the standard library's strlcat function
//     size_t concatenated_std = strlcat(dest_std, source, sizeof(dest_std));

//     printf("Custom ft_strlcat - Concatenated: %zu\n", concatenated_ft);
//     printf("Custom ft_strlcat - Destination: %s\n", dest_ft);

//     printf("Standard strlcat - Concatenated: %zu\n", concatenated_std);
//     printf("Standard strlcat - Destination: %s\n", dest_std);

//     return 0;
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:08:37 by svalchuk          #+#    #+#             */
/*   Updated: 2023/11/16 19:31:07 by svalchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s)[i] == (unsigned char)c)
			return ((unsigned char *)s + i);
		i++;
	}
	return (NULL);
}

// #include <stdio.h>
// #include <string.h>
// int main() {
//     const char str[] = "Hello, World!";
//     int target_char = 'W';
//     size_t len = strlen(str);

//     // Using your custom ft_memchr function
//     void *result_ft = ft_memchr(str, target_char, len);

//     // Using the standard library's memchr function
//     void *result_std = memchr(str, target_char, len);

//     if (result_ft != NULL) {
//         printf("Custom ft_memchr - Found: %c\n", *((char *)result_ft));
//     } else {
//         printf("Custom ft_memchr - Not found\n");
//     }

//     if (result_std != NULL) {
//         printf("Standard memchr - Found: %c\n", *((char *)result_std));
//     } else {
//         printf("Standard memchr - Not found\n");
//     }

//     return 0;
// }

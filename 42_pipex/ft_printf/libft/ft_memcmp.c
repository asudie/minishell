/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:08:40 by svalchuk          #+#    #+#             */
/*   Updated: 2023/11/16 19:42:56 by svalchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s1)[i] != ((unsigned char *)s2)[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}

// #include <stdio.h>
// #include <string.h>
// int main() {
//     const char str1[] = "Hello, World!";
//     const char str2[] = "Hello, Universe!";
//     size_t len = strlen(str1);

//     // Using your custom ft_memcmp function
//     int result_ft = ft_memcmp(str1, str2, len);

//     // Using the standard library's memcmp function
//     int result_std = memcmp(str1, str2, len);

//     printf("Custom ft_memcmp - Result: %d\n", result_ft);
//     printf("Standard memcmp - Result: %d\n", result_std);

//     return 0;
// }

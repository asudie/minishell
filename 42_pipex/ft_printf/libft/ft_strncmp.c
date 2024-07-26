/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:26:02 by svalchuk          #+#    #+#             */
/*   Updated: 2023/11/16 14:53:01 by svalchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s1[i] == s2[i] && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

// #include <stdio.h>
// #include <string.h>
// int main() {
//     const char str1[] = "Hello, World!";
//     const char str2[] = "Hello, Universe!";
//     size_t n = 6; // Test with different values of n

//     // Using your custom ft_strncmp function
//     int result_ft = ft_strncmp(str1, str2, n);

//     // Using the standard library's strncmp function
//     int result_std = strncmp(str1, str2, n);

//     printf("Custom ft_strncmp - Result: %d\n", result_ft);
//     printf("Standard strncmp - Result: %d\n", result_std);

//     return 0;
// }

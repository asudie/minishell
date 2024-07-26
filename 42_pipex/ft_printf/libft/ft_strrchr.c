/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:04:47 by svalchuk          #+#    #+#             */
/*   Updated: 2023/11/22 13:36:27 by svalchuk         ###   ########.fr       */
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

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return (&((char *)s)[i]);
		i--;
	}
	return (NULL);
}

// #include <stdio.h>
// #include <string.h>
// int main() {
//     const char str[] = "Hello, World!";
//     int target_char = 'o';

//     // Using your custom ft_strrchr function
//     char *result_ft = ft_strrchr(str, target_char);

//     // Using the standard library's strrchr function
//     char *result_std = strrchr(str, target_char);

//     if (result_ft != NULL) {
//         printf("Custom ft_strrchr - Found: %c\n", *result_ft);
//     } else {
//         printf("Custom ft_strrchr - Not found\n");
//     }

//     if (result_std != NULL) {
//         printf("Standard strrchr - Found: %c\n", *result_std);
//     } else {
//         printf("Standard strrchr - Not found\n");
//     }

//     return 0;
// }

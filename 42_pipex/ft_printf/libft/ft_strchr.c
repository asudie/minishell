/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:46:43 by svalchuk          #+#    #+#             */
/*   Updated: 2023/11/16 15:14:48 by svalchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return (&((char *)s)[i]);
		i++;
	}
	if (s[i] == (char)c)
		return (&((char *)s)[i]);
	else
		return (NULL);
}

// #include <stdio.h>
// #include <string.h>
// int main() {
//     const char str[] = "tripouille";
//     int target_char = 't';

//     // Using your custom ft_strchr function
//     char *result_ft = ft_strchr(str, target_char + 256);

//     // Using the standard library's strchr function
//     char *result_std = strchr(str, target_char + 256);

//     if (result_ft != NULL) {
//         printf("Custom ft_strchr - Found: %c\n", *result_ft);
//     } else {
//         printf("Custom ft_strchr - Not found\n");
//     }

//     if (result_std != NULL) {
//         printf("Standard strchr - Found: %c\n", *result_std);
//     } else {
//         printf("Standard strchr - Not found\n");
//     }

//     return 0;
// }

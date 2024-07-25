/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 15:37:45 by svalchuk          #+#    #+#             */
/*   Updated: 2023/11/22 13:36:57 by svalchuk         ###   ########.fr       */
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

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		n;
	char	*str;

	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (str == NULL || s1 == NULL || s2 == NULL)
		return (NULL);
	i = 0;
	n = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[n])
	{
		str[i + n] = s2[n];
		n++;
	}
	str[i + n] = '\0';
	return (str);
}

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// int main() {
//     const char str1[] = "Hello, ";
//     const char str2[] = "World!";

//     // Using your custom ft_strjoin function
//     char *result_ft = ft_strjoin(str1, str2);
//     printf("Custom ft_strjoin - Result: %s\n", result_ft);
//     free(result_ft);

//     // Using the standard library's strcat function
//     char *result_std = malloc(strlen(str1) + strlen(str2) + 1);
//     strcpy(result_std, str1);
//     strcat(result_std, str2);
//     printf("Standard strcat - Result: %s\n", result_std);
//     free(result_std);

//     return 0;
// }

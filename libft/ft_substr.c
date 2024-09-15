/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 14:22:22 by svalchuk          #+#    #+#             */
/*   Updated: 2024/07/17 16:57:55 by svalchuk         ###   ########.fr       */
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

// char	*ft_strdup(const char *s1)
// {
// 	char	*dst;
// 	int		i;

// 	dst = malloc(ft_strlen(s1) + 1 * sizeof(char));
// 	if (dst == NULL)
// 		return (NULL);
// 	i = 0;
// 	while (s1[i])
// 	{
// 		dst[i] = s1[i];
// 		i++;
// 	}
// 	dst[i] = '\0';
// 	return (dst);
// }

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	n;
	char	*str;

	if ((unsigned int)ft_strlen(s) < start)
		return (ft_strdup(""));
	n = ft_strlen(s + start);
	if (n < len)
		len = n;
	str = (char *)ft_malloc((len + 1) * sizeof(char));
	if (str == NULL || s == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_substr_rem(char *str, char *sub)
{
	char	*res;
	char	*found;
	int		sub_len;
	int		str_len;
	int		i;

	res = NULL;
	found = ft_strstr(str, sub);
	if (!str || !sub)
		return (NULL);
	if (found)
	{
		sub_len = ft_strlen(sub);
		str_len = ft_strlen(str) - sub_len;
		res = ft_malloc((str_len + 1) * sizeof(char));
		if (res)
		{
			i = found - str;
			ft_strncpy(res, str, i);
			ft_strncpy(res + i, found + sub_len, str_len - i);
			res[str_len] = '\0';
		}
	}
	return (res);
}

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// int main() {
//     const char str[] = "Hello, World!";
//     unsigned int start = 7;
//     size_t length = 5;

//     // Using your custom ft_substr function
//     char *result_ft = ft_substr(str, start, length);
//     printf("Custom ft_substr - Result: %s\n", result_ft);
//     free(result_ft);

//     // Using the standard library's strndup function
//     char *result_std = strndup(str + start, length);
//     printf("Standard strndup - Result: %s\n", result_std);
//     free(result_std);

//     return 0;
// }

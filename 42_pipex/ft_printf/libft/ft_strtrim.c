/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 16:02:57 by svalchuk          #+#    #+#             */
/*   Updated: 2023/11/22 13:36:11 by svalchuk         ###   ########.fr       */
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

// char	*ft_strchr(const char *s, int c)
// {
// 	int	i;

// 	i = 0;
// 	while (s[i])
// 	{
// 		if (s[i] == (char)c)
// 			return (&((char *)s)[i]);
// 		i++;
// 	}
// 	if (s[i] == (char)c)
// 		return (&((char *)s)[i]);
// 	else
// 		return (NULL);
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

// size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
// {
// 	size_t	i;

// 	i = 0;
// 	if (dstsize != 0)
// 	{
// 		while (src[i] && i < (dstsize - 1))
// 		{
// 			dst[i] = src[i];
// 			i++;
// 		}
// 		dst[i] = '\0';
// 	}
// 	return (ft_strlen(src));
// }

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*str;

	start = 0;
	end = ft_strlen(s1) - 1;
	while (ft_strchr(set, s1[start]) && start <= end)
		start++;
	if (start > end)
		return (ft_strdup(s1 + end + 1));
	while (ft_strchr(set, s1[end]) && end >= 0)
		end--;
	str = malloc(end - start + 2);
	if (str == NULL || s1 == NULL || set == NULL)
		return (NULL);
	ft_strlcpy(str, &s1[start], end - start + 2);
	return (str);
}

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// int main() {
//     const char str[] = "   Hello, World!   ";
//     const char set[] = " ";

//     // Using your custom ft_strtrim function
//     char *result_ft = ft_strtrim(str, set);
//     printf("Custom ft_strtrim - Result: \"%s\"\n", result_ft);
//     free(result_ft);

//     // Using standard library functions to achieve the same result
//     size_t start = 0;
//     size_t end = strlen(str) - 1;

//     while (str[start] && strchr(set, str[start]) != NULL)
//         start++;

//     if (start > end) {
//         char *result_std = strdup(str + end + 1);
//         printf("Standard trim - Result: \"%s\"\n", result_std);
//         free(result_std);
//     } else {
//         while (end > 0 && strchr(set, str[end]) != NULL)
//             end--;

//         char *result_std = malloc(end - start + 2);
//         strncpy(result_std, &str[start], end - start + 1);
//         result_std[end - start + 1] = '\0';

//         printf("Standard trim - Result: \"%s\"\n", result_std);
//         free(result_std);
//     }

//     return 0;
// }

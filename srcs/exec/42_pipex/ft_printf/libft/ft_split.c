/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 16:49:40 by svalchuk          #+#    #+#             */
/*   Updated: 2023/12/04 14:09:05 by svalchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

// char	*ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	size_t	i;
// 	size_t	n;
// 	char	*str;

// 	if ((unsigned int)ft_strlen(s) < start)
// 		return (ft_strdup(""));
// 	n = ft_strlen(s + start);
// 	if (n < len)
// 		len = n;
// 	str = (char *)malloc((len + 1) * sizeof(char));
// 	if (str == NULL || s == NULL)
// 		return (NULL);
// 	i = 0;
// 	while (i < len)
// 	{
// 		str[i] = s[start + i];
// 		i++;
// 	}
// 	str[i] = '\0';
// 	return (str);
// }

static size_t	ft_wordcount(char const *s, char c)
{
	size_t	count;
	size_t	i;

	if (s == NULL)
		return (0);
	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] != c && s[i])
			i++;
	}
	return (count);
}

static char	**ft_freemem(char **list)
{
	int	i;

	i = 0;
	while (list[i])
	{
		free(list[i]);
		i++;
	}
	free(list);
	return (NULL);
}

static char	**ft_split_2(char const *s, char c, char **list)
{
	int		i;
	size_t	len;

	i = 0;
	len = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
		{
			if (!ft_strchr(s, c))
				len = ft_strlen(s);
			else
				len = ft_strchr(s, c) - s;
			list[i] = ft_substr(s, 0, len);
			if (list[i++] == NULL)
				return (ft_freemem(list));
			s += len;
		}
	}
	list[i] = NULL;
	return (list);
}

char	**ft_split(char const *s, char c)
{
	char	**list;

	list = (char **)malloc((ft_wordcount(s, c) + 1) * sizeof(char *));
	if (list == NULL || s == NULL)
		return (NULL);
	list = ft_split_2(s, c, list);
	return (list);
}

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// int main() {
//     const char str[] = "hello!";
//     char separator = ' ';

//     // Using your custom ft_split function
//     char **result_ft = ft_split(str, separator);

//     printf("Custom ft_split - Result:\n");
//     for (int i = 0; result_ft[i] != NULL; i++) {
//         printf("%s\n", result_ft[i]);
//         free(result_ft[i]); // Free each individual string
//     }
//     free(result_ft); // Free the array of strings

//     // Using standard library functions to achieve the same result
//     size_t word_count = ft_wordcount(str, separator);
//     char **result_std = (char **)malloc((word_count + 1) * sizeof(char *));

//     if (result_std == NULL) {
//         return (1); // Return an error code
//     }

//     const char *start = str;
//     size_t index = 0;

//     while (*start && index < word_count) {
//         while (*start == separator) {
//             start++;
//         }

//         const char *end = strchr(start, separator);
//         size_t len = (end != NULL) ? (size_t)(end - start) : strlen(start);

//         result_std[index] = (char *)malloc((len + 1) * sizeof(char));
//         strncpy(result_std[index], start, len);
//         result_std[index][len] = '\0';

//         start += len;
//         index++;
//     }

//     result_std[index] = NULL;

//     printf("Standard split - Result:\n");
//     for (size_t i = 0; result_std[i] != NULL; i++) {
//         printf("%s\n", result_std[i]);
//         free(result_std[i]); // Free each individual string
//     }
//     free(result_std); // Free the array of strings

//     return (0);
// }

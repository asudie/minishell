/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 13:46:24 by svalchuk          #+#    #+#             */
/*   Updated: 2023/11/22 17:09:04 by svalchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_convert(char *str, unsigned int num, long int len)
{
	while (num > 0)
	{
		str[len--] = 48 + (num % 10);
		num /= 10;
	}
	return (str);
}

static	long int	ft_length(int n)
{
	int	i;

	i = 0;
	if (n <= 0)
		i = 1;
	while (n != 0)
	{
		i++;
		n /= 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int				i;
	char			*str;
	long int		len;
	unsigned int	num;

	i = 1;
	len = ft_length(n);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	str[len--] = '\0';
	if (n == 0)
		str[0] = '0';
	if (n < 0)
	{
		i *= -1;
		num = n * -1;
		str[0] = '-';
	}
	else
		num = n;
	str = ft_convert(str, num, len);
	return (str);
}

// #include <stdio.h>
// #include <stdlib.h>
// int main() {
//     int num = -12345;

//     // Using your custom ft_itoa function
//     char *result_ft = ft_itoa(num);
//     printf("Custom ft_itoa - Result: %s\n", result_ft);
//     free(result_ft);

//     // Using the standard library's itoa function
//     char *result_std = malloc(20);
		// Allocate enough memory, size can vary based on the system
//     snprintf(result_std, 20, "%d", num);
//     printf("Standard itoa - Result: %s\n", result_std);
//     free(result_std);

//     return 0;
// }

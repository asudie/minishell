/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:26:00 by svalchuk          #+#    #+#             */
/*   Updated: 2023/11/16 16:05:37 by svalchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int	i;
	int	n;
	int	neg;

	i = 0;
	n = 0;
	neg = 1;
	while ((str[i] > 8 && str[i] < 14) || str[i] == 32)
		i++;
	if (str[i] == 43 || str[i] == 45)
	{
		if (str[i] == 45)
			neg *= -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		n = n * 10 + str[i] - 48;
		i++;
	}
	return (n * neg);
}

// #include <stdio.h>
// #include <stdlib.h>
// int main() {
//     const char str1[] = "12345";
//     const char str2[] = "   -678";
//     const char str3[] = "42 is the answer";

//     // Using the standard library's atoi function
//     int result_std1 = atoi(str1);
//     int result_std2 = atoi(str2);
//     int result_std3 = atoi(str3);

//     // Using the custom ft_atoi function
//     int result_ft1 = ft_atoi(str1);
//     int result_ft2 = ft_atoi(str2);
//     int result_ft3 = ft_atoi(str3);

//     printf("Standard atoi - Result 1: %d\n", result_std1);
//     printf("Standard atoi - Result 2: %d\n", result_std2);
//     printf("Standard atoi - Result 3: %d\n", result_std3);

//     printf("Custom ft_atoi - Result 1: %d\n", result_ft1);
//     printf("Custom ft_atoi - Result 2: %d\n", result_ft2);
//     printf("Custom ft_atoi - Result 3: %d\n", result_ft3);

//     return 0;
// }

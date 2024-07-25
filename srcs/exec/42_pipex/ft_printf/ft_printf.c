/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 18:37:45 by svalchuk          #+#    #+#             */
/*   Updated: 2023/12/14 10:02:56 by svalchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_uns(long unsigned int nbr, int *cnt, char *bs, unsigned int len)
{
	if (nbr >= len)
		ft_uns(nbr / len, cnt, bs, len);
	write(1, &bs[nbr % len], 1);
	*cnt += 1;
}

static void	ft_signed(long int nbr, int *count, char *bs, unsigned int len)
{
	if (nbr < 0)
	{
		write(1, &"-", 1);
		*count += 1;
		nbr *= -1;
	}
	ft_uns(nbr, count, bs, len);
}

static void	ft_print_flags(char *s, int *count, int option)
{
	if (option == 0)
	{
		if (s != NULL)
		{
			ft_putstr_fd(s, 1);
			*count += ft_strlen(s);
		}
		else
		{
			ft_putstr_fd("(null)", 1);
			*count += 6;
		}
	}
	else if (option == 1)
	{
		write(1, &"0x", 2);
		*count += 2;
		ft_uns((long unsigned int)s, count, "0123456789abcdef", 16);
	}
}

static void	ft_flags(va_list list, char c, int *count)
{
	if (c == 'c' || c == '%')
	{
		if (c == '%')
			ft_putchar_fd('%', 1);
		else
			ft_putchar_fd(va_arg(list, int), 1);
		*count += 1;
	}
	else if (c == 's')
		ft_print_flags(va_arg(list, char *), count, 0);
	else if (c == 'p')
		ft_print_flags(va_arg(list, void *), count, 1);
	else if (c == 'd' || c == 'i')
		ft_signed(va_arg(list, int), count, "0123456789", 10);
	else if (c == 'u')
		ft_signed(va_arg(list, unsigned int), count, "0123456789", 10);
	else if (c == 'x')
		ft_signed(va_arg(list, unsigned int), count, "0123456789abcdef", 16);
	else if (c == 'X')
		ft_signed(va_arg(list, unsigned int), count, "0123456789ABCDEF", 16);
}

int	ft_printf(const char *input, ...)
{
	int		i;
	int		count;
	va_list	list;

	i = -1;
	count = 0;
	va_start(list, input);
	while (input[++i])
	{
		if (input[i] == '%')
			ft_flags(list, input[++i], &count);
		else
		{
			ft_putchar_fd(input[i], 1);
			count += 1;
		}
	}
	va_end(list);
	return (count);
}

// #include <stdio.h>

// int main(void) 
// {
//     // Testing with integers
//     int num = 42;

//     printf("Standard printf: %d\n", num);
//     ft_printf("Custom ft_printf: %d\n", num);

//     // Testing with strings
//     const char *str = "Hello, world!";

//     printf("Standard printf: %s\n", str);
//     ft_printf("Custom ft_printf: %s\n", str);

//     // Add more test cases as needed

//     return (0);
// }

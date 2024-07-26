/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:20:07 by svalchuk          #+#    #+#             */
/*   Updated: 2023/12/01 16:59:07 by svalchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char *)b;
	while (i < len)
	{
		ptr[i] = (unsigned char)c;
		i++;
	}
	return (b);
}

// #include <stdio.h>
// #include <string.h>
// int main() {
//     char buffer[10];
//     char buffer_std[10];

//     // Using your custom ft_memset function
//     ft_memset(buffer, 'A', 5);

//     // Using the standard library's memset function
//     memset(buffer_std, 'A', 5);

//     printf("Custom ft_memset: %s\n", buffer);
//     printf("Standard memset: %s\n", buffer_std);

//     return 0;
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:25:52 by svalchuk          #+#    #+#             */
/*   Updated: 2023/11/22 13:37:30 by svalchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// void	*ft_memset(void *b, int c, size_t len)
// {
// 	size_t			i;
// 	unsigned char	*ptr;

// 	i = 0;
// 	ptr = (unsigned char *)b;
// 	while (i < len)
// 	{
// 		ptr[i] = (unsigned char)c;
// 		i++;
// 	}
// 	return (b);
// }

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (count == 0 || size == 0)
		return (malloc(0));
	ptr = malloc(count * size);
	if (ptr == NULL)
		return (NULL);
	ft_memset((unsigned char *)ptr, 0, count * size);
	return (ptr);
}

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// int main() {
//     size_t num_elements = 5;
//     size_t element_size = sizeof(int);

//     // Using the standard library's calloc function
//     int *arr_std = (int *)calloc(num_elements, element_size);

//     // Using your custom ft_calloc function
//     int *arr_ft = (int *)ft_calloc(num_elements, element_size);

//     // Displaying the allocated memory for comparison
//     printf("Standard calloc - Allocated memory: ");
//     for (size_t i = 0; i < num_elements; i++) {
//         printf("%d ", arr_std[i]);
//     }
//     printf("\n");

//     printf("Custom ft_calloc - Allocated memory: ");
//     for (size_t i = 0; i < num_elements; i++) {
//         printf("%d ", arr_ft[i]);
//     }
//     printf("\n");

//     // Freeing the allocated memory
//     free(arr_std);
//     free(arr_ft);

//     return 0;
// }

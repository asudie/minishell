/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 14:02:00 by svalchuk          #+#    #+#             */
/*   Updated: 2023/11/23 14:14:45 by svalchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	write(fd, "\n", 1);
}

// #include <stdio.h>
// #include <unistd.h>
// int main() {
//     char str[] = "Hello, World!";
//     int file_descriptor = 1; // Assuming stdout for testing

//     // Using your custom ft_putendl_fd function
//     printf("Custom ft_putendl_fd - Result:\n");
//     ft_putendl_fd(str, file_descriptor);

//     // Using the standard library's write function
//     printf("\nStandard write - Result:\n");
//     write(file_descriptor, str, sizeof(str) - 1);
//		// sizeof(str) - 1 to exclude the null terminator
//     write(file_descriptor, "\n", 1);

//     return 0;
// }

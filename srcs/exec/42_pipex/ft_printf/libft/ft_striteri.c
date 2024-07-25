/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:20:47 by svalchuk          #+#    #+#             */
/*   Updated: 2023/11/23 13:49:54 by svalchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	if (s && f)
	{
		while (s[i])
		{
			(*f)(i, &s[i]);
			i++;
		}
	}
}

// #include <stdio.h>
// // Example function to print the index and character
// void print_index_char(unsigned int index, char *character) {
//     printf("Index: %u, Character: %c\n", index, *character);
// }

// int main() {
//     char str[] = "Hello, World!";

//     // Using your custom ft_striteri function
//     printf("Custom ft_striteri - Result:\n");
//     ft_striteri(str, print_index_char);

//     return 0;
// }

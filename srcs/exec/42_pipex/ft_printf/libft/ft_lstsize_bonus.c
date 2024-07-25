/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:53:54 by svalchuk          #+#    #+#             */
/*   Updated: 2023/11/29 15:02:10 by svalchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

// #include <stdio.h>
// #include <stdlib.h>
// int main() {
//     // Create a linked list with three nodes
//     t_list *head = malloc(sizeof(t_list));
//     int data1 = 42;
//     head->content = &data1;

//     t_list *node2 = malloc(sizeof(t_list));
//     int data2 = 24;
//     node2->content = &data2;
//     head->next = node2;

//     t_list *node3 = malloc(sizeof(t_list));
//     int data3 = 100;
//     node3->content = &data3;
//     node2->next = node3;
//     node3->next = NULL;

//     // Using your custom ft_lstsize function
//     int size = ft_lstsize(head);

//     // Print the result
//     printf("Custom ft_lstsize - Result: %d\n", size);

//     // Free the memory allocated for the linked list
//     free(head);
//     free(node2);
//     free(node3);

//     return 0;
// }

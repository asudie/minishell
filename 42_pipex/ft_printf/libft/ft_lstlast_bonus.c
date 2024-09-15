/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:57:22 by svalchuk          #+#    #+#             */
/*   Updated: 2023/11/29 15:11:09 by svalchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
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

//     // Using your custom ft_lstlast function
//     t_list *last_node = ft_lstlast(head);

//     // Print the content of the last node
//     printf("Custom ft_lstlast: %d\n", *(int *)(last_node->content));

//     // Free the memory allocated for the linked list
//     free(head);
//     free(node2);
//     free(node3);

//     return 0;
// }

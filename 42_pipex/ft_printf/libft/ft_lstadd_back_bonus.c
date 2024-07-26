/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:35:54 by svalchuk          #+#    #+#             */
/*   Updated: 2023/11/29 15:16:56 by svalchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (lst)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			tmp = ft_lstlast(*lst);
			tmp->next = new;
		}
	}
}

// #include <stdio.h>
// #include <stdlib.h>
// // Helper function to print the contents of a linked list
// void print_list(t_list *head) {
//     while (head != NULL) {
//         printf("%d ", *(int *)(head->content));
//         head = head->next;
//     }
//     printf("\n");
// }
// int main() {
//     // Create an initial linked list with two nodes
//     t_list *head = malloc(sizeof(t_list));
//     int data1 = 42;
//     head->content = &data1;

//     t_list *node2 = malloc(sizeof(t_list));
//     int data2 = 24;
//     node2->content = &data2;
//     head->next = node2;

//     // Create a new node
//     t_list *new_node = malloc(sizeof(t_list));
//     int data3 = 100;
//     new_node->content = &data3;
//     new_node->next = NULL;

//     // Using your custom ft_lstadd_back function
//     ft_lstadd_back(&head, new_node);

//     // Print the contents of the linked list 
//	   // after adding a new node at the back
//     printf("Custom ft_lstadd_back - Result: ");
//     print_list(head);

//     // Free the memory allocated for the linked list
//     free(head);
//     free(node2);
//     free(new_node);

//     return 0;
// }

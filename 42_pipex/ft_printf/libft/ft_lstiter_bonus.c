/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:29:08 by svalchuk          #+#    #+#             */
/*   Updated: 2023/11/29 16:54:24 by svalchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (lst == NULL || f == NULL)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}

// #include <stdio.h>
// #include <stdlib.h>
// // Example function to apply some operation to the content of a node
// void square_content(void *content) {
//     int *value = (int *)content;
//     printf("%d ", (*value) * (*value));
// }
// // Helper function to print the contents of a linked list
// void print_list(t_list *head) {
//     while (head != NULL) {
//         printf("%d ", *(int *)(head->content));
//         head = head->next;
//     }
//     printf("\n");
// }
// int main() {
//     // Create a linked list with three nodes
//     t_list *head = malloc(sizeof(t_list));
//     int data1 = 2;
//     head->content = &data1;

//     t_list *node2 = malloc(sizeof(t_list));
//     int data2 = 3;
//     node2->content = &data2;
//     head->next = node2;

//     t_list *node3 = malloc(sizeof(t_list));
//     int data3 = 4;
//     node3->content = &data3;
//     node2->next = node3;
//     node3->next = NULL;

//     // Using your custom ft_lstiter function
//     printf("Custom ft_lstiter: ");
//     ft_lstiter(head, square_content);
//     printf("\n");

//     // Print the contents of the linked list after applying the operation
//     printf("Result after applying operation: ");
//     print_list(head);

//     // Free the memory allocated for the linked list
//     free(head);
//     free(node2);
//     free(node3);

//     return 0;
// }

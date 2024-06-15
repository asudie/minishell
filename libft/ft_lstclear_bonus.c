/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:37:19 by svalchuk          #+#    #+#             */
/*   Updated: 2023/11/29 15:28:02 by svalchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;

	if (lst)
	{
		while (*lst)
		{
			tmp = (*lst)->next;
			ft_lstdelone(*lst, del);
			*lst = tmp;
		}
	}
}

// #include <stdio.h>
// #include <stdlib.h>
// // Example function to delete the content of a node
// void delete_content(void *content) {
//     free(content);
// }
// // Helper function to print the contents of a linked list
// void print_list(t_list *head) {
//     while (head != NULL) {
//         printf("%s ", (char *)(head->content));
//         head = head->next;
//     }
//     printf("\n");
// }
// int main() {
//     // Create a linked list with three nodes
//     t_list *head = malloc(sizeof(t_list));
//     char *data1 = strdup("Hello");
//     head->content = data1;

//     t_list *node2 = malloc(sizeof(t_list));
//     char *data2 = strdup(", ");
//     node2->content = data2;
//     head->next = node2;

//     t_list *node3 = malloc(sizeof(t_list));
//     char *data3 = strdup("World!");
//     node3->content = data3;
//     node2->next = node3;
//     node3->next = NULL;

//     // Using your custom ft_lstclear function
//     printf("Custom ft_lstclear - Clearing the list:\n");
//     ft_lstclear(&head, delete_content);

//     // Print the contents of the linked list after clearing
//     printf("Result after clearing: ");
//     print_list(head);

//     // Note: The linked list head is now NULL as it has been cleared

//     return 0;
// }

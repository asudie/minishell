/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:29:15 by svalchuk          #+#    #+#             */
/*   Updated: 2023/11/29 17:55:09 by svalchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*element;

	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	new_list = NULL;
	while (lst)
	{
		element = (t_list *)malloc(sizeof(*new_list));
		if (element == NULL)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		element->content = f(lst->content);
		element->next = NULL;
		ft_lstadd_back(&new_list, element);
		lst = lst->next;
	}
	return (new_list);
}

// Old, better but not working
// t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
// {
// 	t_list	*new_list;
// 	t_list	*element;

// 	if (lst == NULL || f == NULL || del == NULL)
// 		return (NULL);
// 	new_list = NULL;
// 	while (lst)
// 	{
//		// this part dont work
// 		element = ft_lstnew(f(lst->content));
// 		if (element == NULL)
// 		{
// 			ft_lstclear(&new_list, del);
// 			return (NULL);
// 		}
// 		ft_lstadd_back(&new_list, element);
// 		lst = lst->next;
// 	}
// 	return (new_list);
// }

// #include <stdio.h>
// #include <stdlib.h>
// //Helper function to print the contents of a linked list
// void print_list(t_list *head) {
//     while (head != NULL) {
//         printf("%d ", *(int *)(head->content));
//         head = head->next;
//     }
//     printf("\n");
// }
// // Example function to transform the content of a node
// void *double_content(void *content) {
//     int *value = (int *)content;
//     int *new_value = malloc(sizeof(int));
//     *new_value = (*value) * 2;
//     return (void *)new_value;
// }
// // Example function to delete the content of a node
// void delete_content(void *content) {
//     free(content);
// }
// int main() {
//     // Create a linked list with three nodes
//     t_list *head = ft_lstnew((void *)malloc(sizeof(int)));
//     int *data1 = (int *)(head->content);
//     *data1 = 2;

//     t_list *node2 = ft_lstnew((void *)malloc(sizeof(int)));
//     int *data2 = (int *)(node2->content);
//     *data2 = 3;
//     ft_lstadd_back(&head, node2);

//     t_list *node3 = ft_lstnew((void *)malloc(sizeof(int)));
//     int *data3 = (int *)(node3->content);
//     *data3 = 4;
//     ft_lstadd_back(&head, node3);

//     // Using your custom ft_lstmap function
//     printf("Custom ft_lstmap - Doubling each node's content: ");
//     t_list *new_list = ft_lstmap(head, double_content, delete_content);
//     print_list(new_list);
//     printf("\n");

//     // Free the memory allocated for the linked lists
//     ft_lstclear(&head, delete_content);
//     ft_lstclear(&new_list, delete_content);

//     return 0;
// }

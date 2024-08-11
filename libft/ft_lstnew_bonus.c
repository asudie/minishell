/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:48:40 by svalchuk          #+#    #+#             */
/*   Updated: 2024/08/02 20:47:12 by svalchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = ft_malloc(sizeof(t_list));
	if (node == NULL)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}

// #include <stdio.h>
// #include <stdlib.h>
// int main() {
//     int data = 42;

//     // Using your custom ft_lstnew function
//     t_list *node = ft_lstnew(&data);

//     // Print the content of the created node
//     if (node != NULL) {
//         printf("Custom ft_lstnew - Content: %d\n", *(int *)(node->content));
//         free(node);
//     } else {
//         printf("Custom ft_lstnew - Node creation failed.\n");
//     }

//     return 0;
// }

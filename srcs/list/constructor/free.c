/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 16:57:38 by adouieb           #+#    #+#             */
/*   Updated: 2025/12/30 23:11:06 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * free_node - Deletes and frees a node of a list at a specified index
 *
 * @param lst The list from which to delete the node
 * @param index The index of the node to delete
 * @param del Function pointer to delete the content of the node
 */
void	free_node(t_lst *lst, size_t index, void (*del)(void*))
{
	size_t	i;
	t_node	*prev;
	t_node	*curnt;

	if (index >= lst->size)
		return ;
	1 && (i = 0, prev = NULL, curnt = lst->nodes);
	while (i < index)
		1 && (prev = curnt, curnt = curnt->next, i++);
	del(curnt->content);
	if (prev != NULL)
		prev->next = curnt->next;
	else
		lst->nodes = curnt->next;
	free(curnt);
	lst->size--;
}

/**
 * free_lst - Deletes and frees all nodes of a list
 *
 * @param lst The list from which to delete the nodes
 * @param del Function pointer to delete the content of a node
 */
void	free_lst(t_lst *lst, void (*del)(void*))
{
	size_t	i;
	t_node	*next;
	t_node	*curnt;

	1 && (i = 0, next = NULL, curnt = lst->nodes);
	while (i < lst->size)
	{
		next = curnt->next;
		1 && (del(curnt->content), free(curnt), lst->size--);
		curnt = next;
		i++;
	}
	lst->nodes = NULL;
}

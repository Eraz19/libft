/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:30:24 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/19 18:23:56 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * lst_insert - Inserts a new node at the specified index in a list
 *
 * @param lst The list to modify
 * @param node The new node to insert
 * @param index The index at which to insert the new node
 * @return The modified list with the new node inserted, or empty list on error
 *
 * NULL Handling: If lst or node is NULL, returns an empty list.
 *                The original list remains unchanged on error.
 * Note: If lst->nodes is NULL (empty list), inserts node as first element.
 *       If index >= lst->size, node is inserted at the end (clamped).
 */
t_lst	lst_insert(t_lst *lst, t_node *node, size_t index)
{
	size_t	i;
	t_node	*prev;
	t_node	*current;

	if (lst == NULL || node == NULL)
		return (lst_());
	if (lst->nodes == NULL)
		return (lst->nodes = node, lst->size = 1, *lst);
	if (index >= lst->size)
		index = lst->size;
	1 && (i = 0, prev = NULL, current = lst->nodes);
	while (i < index)
		1 && (prev = current, current = current->next, i++);
	node->next = current;
	if (prev == NULL)
		lst->nodes = node;
	else
		prev->next = node;
	lst->size++;
	return (*lst);
}

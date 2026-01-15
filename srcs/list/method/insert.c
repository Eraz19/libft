/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:30:24 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/10 19:38:08 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * lst_insert - Inserts a new node at the specified index in a list
 *
 * @param lst The list to modify
 * @param node The new node to insert
 * @param index The index at which to insert the new node
 * Note: Does nothing if lst or node is NULL; if index >= lst->size, inserts at end
 */
t_lst	lst_insert(t_lst *lst, t_node *node, size_t index)
{
	size_t	i;
	t_node	*prev;
	t_node	*curnt;

	if (lst == NULL || node == NULL)
		return ;
	if (index >= lst->size)
		index = lst->size;
	1 && (i = 0, prev = NULL, curnt = lst->nodes);
	while (i < index)
		1 && (prev = curnt, curnt = curnt->next, i++);
	node->next = curnt;
	if (prev == NULL)
		lst->nodes = node;
	else
		prev->next = node;
	lst->size++;
}

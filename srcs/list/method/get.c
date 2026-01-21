/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 17:22:39 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/20 12:42:17 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * get - Returns the node at the specified index in a list
 *
 * @param lst The list to traverse
 * @param index The index of the node to retrieve
 * @return The node at the specified index
 *
 * NULL Handling: if lst.nodes is NULL, returns NULL.
 * Note: If index is out of bounds (>= lst.size), returns NULL.
 */
t_node	*get(t_lst lst, size_t index)
{
	size_t	i;
	t_node	*current;

	if (lst.nodes == NULL || index >= lst.size)
		return (NULL);
	1 && (current = lst.nodes, i = 0);
	while (i < index && i < lst.size)
		1 && (current = current->next, ++i);
	return (current);
}

/**
 * filter - Returns a list of nodes that matches a condition
 *
 * @param lst The list to traverse
 * @param cmp The comparison function to determine a match
 * @param context The context containing the data to compare against
 * @return The list of nodes that matches the condition or a NULL list if no
 *			match found
 *
 * NULL Handling: if lst.nodes or cmp is NULL, returns a NULL list.
 */
t_lst	filter(t_lst lst, t_bool (*cmp)(void *, void *), void *context)
{
	t_node	*current;

	if (lst.nodes == NULL || cmp == NULL)
		return (lst_());
	current = lst.nodes;
	while (current != NULL)
	{
		if (cmp(current->content, context))
			return (lst_n(current));
		current = current->next;
	}
	return (lst_());
}

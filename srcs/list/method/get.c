/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 17:22:39 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/19 17:17:45 by adouieb          ###   ########.fr       */
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

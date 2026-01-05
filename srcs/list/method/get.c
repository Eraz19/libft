/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 17:22:39 by adouieb           #+#    #+#             */
/*   Updated: 2025/12/30 23:11:37 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * get - Returns the node at the specified index in a list
 *
 * @param lst The list to traverse
 * @param index The index of the node to retrieve
 * @return The node at the specified index, or NULL if out of bounds
 */
t_node	*get(t_lst lst, size_t index)
{
	size_t	i;
	t_node	*curnt;

	if (lst.size == 0 || index >= lst.size)
		return (NULL);
	1 && (curnt = lst.nodes, i = 0);
	while (i < index && i < lst.size)
		curnt = curnt->next;
	return (curnt);
}

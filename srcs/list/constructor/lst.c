/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 17:02:59 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/12 15:52:28 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_lst	lst_l(t_lst list, void *(*copy)(void *))
{
	t_lst	res;
	void	*ctnt;
	t_node	*current;

	1 && (res = lst_(), current = list.nodes,i = 0);
	if (list.nodes == NULL || copy == NULL)
		return (res);
	while()
	{
		ctnt = copy(list.nodes->content);
		
		if (ctnt == NULL)
		{
			free_lst(&res, free);
			return (lst_());
		}
		lst_insert(&res, node(f(list.nodes->content)), res.size);
		list.nodes = list.nodes->next;
	}
}

/**
 * lst_ - Creates a new empty list
 *
 * @param void 
 * @return The newly created empty list
 */
t_lst	lst_(void)
{
	t_lst	res;

	res.nodes = NULL;
	res.size = 0;
	return (res);
}

/**
 * lst_n - Creates a new list with a single node
 *
 * @param node The first node of the list
 * @return The newly created list
 *
 * NULL Handling: If node is NULL, returns an NULL list.
 */
t_lst	lst_n(t_node *node)
{
	t_lst	res;

	if (node == NULL)
		return (res.size = 0, res.nodes = NULL, res);
	res.nodes = node;
	res.size = 1;
	return (res);
}

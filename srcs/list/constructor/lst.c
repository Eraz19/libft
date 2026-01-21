/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 17:02:59 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/21 15:48:05 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_list.h"

/**
 * lst_l - Creates a new list by copying an existing list
 *
 * @param list The list to copy
 * @param copy The function to copy the content of each node
 * @param del The function to delete the content in case of failure
 * @return The newly created list
 *
 * @args: If list.nodes, copy, or del is NULL, returns a NULL list.
 * @error: If allocation fails, returns a NULL list (errno ENOMEM).
 */
t_lst	lst_l(t_lst list, void *(*copy)(void *), void (*del)(void *))
{
	size_t	i;
	t_lst	res;
	t_node	*new;
	void	*content;

	if (list.nodes == NULL || copy == NULL || del == NULL)
		return (lst_());
	1 && (res = lst_(), i = 0);
	while (i < list.size)
	{
		content = copy(list.nodes->content);
		if (content == NULL)
			return (free_lst(&res, del), lst_());
		new = node(content);
		if (new == NULL)
			return (del(content), free_lst(&res, del), lst_());
		lst_insert(&res, new, res.size);
		list.nodes = list.nodes->next;
		++i;
	}
	return (res);
}

/**
 * lst_ - Creates a new empty list
 *
 * @param void 
 * @return The newly created NULL list to be populated
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
 * @args: If node is NULL, returns an NULL list.
 */
t_lst	lst_n(t_node *node)
{
	t_lst	res;

	if (node == NULL)
		return (lst_());
	res.nodes = node;
	res.size = 1;
	return (res);
}

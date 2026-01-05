/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 17:18:28 by adouieb           #+#    #+#             */
/*   Updated: 2025/12/30 23:12:14 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * lst_foreach - Applies a function to each node of a list for side effects
 *
 * @param lst The list to iterate over
 * @param f The function to apply to each node's content
 */
void	lst_foreach(t_lst lst, void (*f)(void *))
{
	size_t	i;
	t_node	*curnt;

	if (lst.nodes == NULL)
		return ;
	1 && (i = 0, curnt = lst.nodes);
	while (i < lst.size)
		(f(curnt->content), curnt = curnt->next, i++);
}

/**
 * lst_map - Applies a function to each node to create a new list
 *
 * MEMORY OWNERSHIP: This function consumes (frees) the input 'lst' and
 * returns a newly allocated list. Always reassign the result:
 *     lst = lst_map(lst, transform, del);  // ✓ Correct usage
 *
 * @param lst The list to map over (will be freed)
 * @param f The function to apply to each node's content
 * @param del Function pointer to delete content on failure
 * @return A new list with transformed nodes, or NULL list content on failure
 */
t_lst	lst_map(t_lst lst, void *(*f)(void *), void (*del)(void *))
{
	size_t	i;
	t_lst	res;
	t_node	*new;
	void	*ctnt;
	t_node	*curnt;

	1 && (i = 0, res = lst_(), new = NULL, curnt = lst.nodes);
	if (lst.nodes == NULL)
		return (res);
	while (i < lst.size)
	{
		ctnt = f(curnt->content);
		if (ctnt == NULL)
			return (free_lst(&res, del), free_lst(&lst, del), res);
		new = node(ctnt);
		if (new == NULL)
			return (del(ctnt), free_lst(&res, del), free_lst(&lst, del), res);
		lst_insert(&res, new, res.size);
		1 && (curnt = curnt->next, i++);
	}
	free_lst(&lst, del);
	return (res);
}

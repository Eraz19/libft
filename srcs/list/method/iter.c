/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 17:18:28 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/21 15:50:02 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_list.h"

/**
 * lst_foreach - Applies a function to each node of a list for side effects
 *
 * @param lst The list to iterate over
 * @param f The function to apply to each node's content
 * 
 * @args: If lst.nodes is NULL, does nothing.
 */
void	lst_foreach(t_lst lst, void (*f)(void *))
{
	size_t	i;
	t_node	*current;

	if (lst.nodes == NULL || f == NULL)
		return ;
	1 && (i = 0, current = lst.nodes);
	while (i < lst.size)
		(f(current->content), current = current->next, i++);
}

/**
 * lst_map - Applies a function to each node to create a new list
 *
 * MEMORY OWNERSHIP: This function consumes (frees) the input 'lst', the
 * original 'lst' becomes invalid.
 * To keep a copy of the list, first duplicate it before. 
 * Always reassign the result:
 *     t_lst lst = lst_l(original_lst);
 *     lst = lst_map(&lst, transform, del); // ✓ Correct usage
 *     original_lst                         // ✓ remains valid
 *
 * @param lst The list to map over (always freed)
 * @param f The function to apply to each node's content
 * @param del The function to free node content
 * @return A new list with transformed nodes
 * 
 * @args: If lst, lst->nodes, f, or del is NULL, returns a NULL list.
 * @error: If allocation fails, returns a NULL list (errno ENOMEM).
 */
t_lst	lst_map(t_lst *lst, void *(*f)(void *), void (*del)(void *))
{
	size_t	i;
	t_lst	res;
	t_node	*new;
	void	*content;
	t_node	*current;

	if (lst == NULL || lst->nodes == NULL || f == NULL || del == NULL)
		return (lst_());
	1 && (i = 0, res = lst_(), new = NULL, current = lst->nodes);
	while (i < lst->size)
	{
		content = f(current->content);
		if (content == NULL)
			return (free_lst(&res, del), free_lst(lst, del), res);
		new = node(content);
		if (new == NULL)
			return (del(content), free_lst(&res, del), free_lst(lst, del), res);
		lst_insert(&res, new, res.size);
		1 && (current = current->next, i++);
	}
	free_lst(lst, del);
	return (res);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 17:02:59 by adouieb           #+#    #+#             */
/*   Updated: 2025/12/29 19:21:24 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * lst - Creates a new empty list
 *
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
 * lst - Creates a new list
 *
 * @param node The first node of the list
 * @return The newly created list
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

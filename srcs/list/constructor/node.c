/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 18:12:15 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/21 15:48:29 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_list.h"

/**
 * node - Creates a new list node
 *
 * @param content The pointer to the content to store in the node
 * @return The newly created node
 *
 * @args: If content is NULL, returns NULL.
 * @error: If allocation fails, returns NULL (errno ENOMEM).
 */
t_node	*node(void *content)
{
	t_node	*new;

	if (content == NULL)
		return (NULL);
	new = malloc(sizeof(t_node));
	if (new == NULL)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 18:12:15 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/12 14:42:57 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * node - Creates a new list node
 *
 * @param content The content to store in the node
 * @return The newly created node
 *
 * NULL Handling: If content is NULL, returns NULL.
 * Error: If allocation fails, returns NULL (errno ENOMEM).
 */
t_node	*node(void *content)
{
	t_node	*new;

	if (content == NULL)
		return (NULL);
	new = malloc(sizeof(t_node));
	if (new == NULL)
		return (errno = ENOMEM, NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

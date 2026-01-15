/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 16:00:00 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/15 12:25:47 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * free_dbuf - Frees a dynamic buffer and clears its memory
 *
 * @param buf The pointer to the buffer to free
 */
void	free_dbuf(t_dbuf *buf)
{
	size_t	i;

	if (buf == NULL || buf->data == NULL)
		return ;
	i = 0;
	while (i < buf->size)
		((t_i8 *)buf->data)[i++] = 0;
	free(buf->data);
	buf->len = 0;
	buf->size = 0;
	buf->data = NULL;
}

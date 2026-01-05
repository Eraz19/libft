/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 16:00:00 by adouieb           #+#    #+#             */
/*   Updated: 2025/12/30 19:05:46 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * free_dbuf - Frees the memory allocated for a dynamic buffer
 *
 * @param buf The pointer to the buffer to free
 */
void	free_dbuf(t_dbuf *buf)
{
	if (buf->data == NULL)
		return ;
	free(buf->data);
	buf->len = 0;
	buf->size = 0;
	buf->data = NULL;
}

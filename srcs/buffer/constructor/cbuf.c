/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cbuf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 16:15:00 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/19 17:04:04 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * cbuf - Creates a constant buffer structure from raw data
 *
 * @param data Pointer to the data
 * @param size The size of the data in bytes
 * @return The newly created t_cbuf
 *
 * NULL Handling: If s is NULL, returns a NULL t_cbuf.
 * Note: If size = 0, returns a NULL t_cbuf.
 */
t_cbuf	cbuf(const void *data, size_t size)
{
	t_cbuf	buf;

	if (data == NULL || size == 0)
		return (buf.data = data, buf.size = 0, buf);
	buf.data = data;
	buf.size = size;
	return (buf);
}

/**
 * cbuf_d - Converts a dynamic buffer structure to a constant buffer structure
 *
 * @param buf The t_dbuf to convert
 * @return A t_cbuf representing the same data where size is buf.len
 *
 * NULL Handling: If buf.data is NULL, returns a NULL t_cbuf.
 * WARNING: The size value of the result t_cbuf is buf.len not buf.size.
 */
t_cbuf	cbuf_d(t_dbuf buf)
{
	t_cbuf	res;

	if (buf.data == NULL)
		return (cbuf(NULL, 0));
	res.data = buf.data;
	res.size = buf.len;
	return (res);
}

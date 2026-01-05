/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cbuf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 16:15:00 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/01 20:12:27 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * cbuf - Creates a constant buffer structure from raw data
 *
 * @param data Pointer to the data
 * @param size The size of the data in bytes
 * @return The newly created t_cbuf
 */
t_cbuf	cbuf(const void *data, size_t size)
{
	t_cbuf	buf;

	buf.data = data;
	buf.size = size;
	return (buf);
}

/**
 * cbuf_d - Converts a dynamic buffer structure to a constant buffer structure
 *
 * @param buf The t_dbuf to convert
 * @return A t_cbuf representing the same data where size is buf.len
 */
t_cbuf	cbuf_d(t_dbuf buf)
{
	t_cbuf	res;

	res.data = buf.data;
	res.size = buf.len;
	return (res);
}

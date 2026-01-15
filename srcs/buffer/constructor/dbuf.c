/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dbuf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 16:27:51 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/15 12:16:35 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * dbuf_d - Duplicates a dynamic buffer structure
 *
 * @param buf The t_dbuf structure to duplicate
 * @return A new t_dbuf containing a copy of the data
 *
 * NULL Handling: If buf.data is NULL, returns a NULL t_dbuf.
 * Error: If allocation fails, returns a NULL t_dbuf (errno ENOMEM).
 */
t_dbuf	dbuf_d(t_dbuf buf)
{
	size_t	i;
	t_dbuf	buf_;

	if (buf.data == NULL)
		return (dbuf_s(0));
	1 && (buf_ = dbuf_s(buf.size), i = 0);
	while (i < buf.len)
		1 && (((t_u8 *)buf_.data)[i] = ((t_u8 *)buf.data)[i], ++i);
	buf_.len = buf.len;
	return (buf_);
}

/**
 * dbuf_s - Creates a new dynamic buffer structure with allocated memory
 *
 * @param size The size in bytes to allocate (elements * type_size)
 * @return The newly created t_dbuf initialized to zero
 *
 * Note: If size = 0, returns a NULL t_dbuf.
 * Error: If allocation fails, returns a NULL t_dbuf (errno ENOMEM).
 */
t_dbuf	dbuf_s(size_t size)
{
	size_t	i;
	t_dbuf	buf;

	if (size == 0)
		return (buf.data = NULL, buf.size = 0, buf.len = 0, buf);
	buf.data = malloc(size);
	if (buf.data == NULL)
		return (buf.size = 0, buf.len = 0, buf);
	else
	{
		1 && (i = 0, buf.len = 0, buf.size = size);
		while (i < buf.size)
			((t_i8 *)buf.data)[i++] = 0;
		return (buf);
	}
}

/**
 * dbuf_c - Creates a new dynamic buffer structure from a constant buffer
 *
 * @param buf The t_cbuf structure to convert
 * @return A new t_dbuf containing a copy of the data
 *
 * NULL Handling: If buf.data is NULL, returns a NULL t_dbuf.
 * Error: If allocation fails, returns a NULL t_dbuf (errno ENOMEM).
 */
t_dbuf	dbuf_c(t_cbuf buf)
{
	size_t	i;
	t_dbuf	res;

	if (buf.data == NULL)
		return (dbuf_s(0));
	res = dbuf_s(buf.size);
	if (res.data == NULL)
		return (res);
	i = 0;
	while (i < buf.size)
		1 && (((t_u8 *)res.data)[i] = ((const t_u8 *)buf.data)[i], ++i);
	res.len = buf.size;
	return (res);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 16:00:00 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/15 12:29:27 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_dbuf	buf_realloc(t_dbuf buf, size_t new_size, t_buf_strat mode)
{
	size_t	i;
	t_dbuf	new_buf;
	size_t	target_size;

	1 && (i = 0, target_size = buf.size * 2);
	if (new_size > buf.size)
	{
		if (mode == x2_)
		{
			while (target_size < new_size)
				target_size *= 2;
			new_buf = dbuf_s(target_size);
		}
		else
			new_buf = dbuf_s(new_size);
		if (new_buf.data == NULL)
			return (free_dbuf(&buf), new_buf);
		while (i < buf.len)
			1 && (((t_u8 *)new_buf.data)[i] = ((t_u8 *)buf.data)[i], ++i);
		return (new_buf.len = buf.len, free_dbuf(&buf), new_buf);
	}
	return (buf);
}

static void	buf_shift_right(t_dbuf res, size_t i, size_t orig_len, size_t gap)
{
	size_t	buf_len;

	if (i < orig_len)
	{
		buf_len = orig_len;
		while (buf_len > i)
		{
			buf_len--;
			((t_u8 *)res.data)[buf_len + gap] = ((t_u8 *)res.data)[buf_len];
		}
	}
}

/**
 * buf_insertc - Inserts a constant buffer into a buffer
 *
 * MEMORY OWNERSHIP: This function may reallocate 'buf' if more space is
 * needed. Always reassign the result to handle both cases:
 *     buf = buf_insertc(buf, insrt, i, mode);  // ✓ Correct usage
 * The original 'buf' is freed only if reallocation occurs.
 *
 * @param buf The t_dbuf to insert into (may be freed if reallocated)
 * @param insrt The t_cbuf to insert
 * @param i The position to insert at
 * @param mode The buffer strategy mode
 *    - E_  : Only allocate the exact needed size
 *    - x2_ : Double the buffer size if needed
 * @return A t_dbuf with the inserted content (may be same or new buffer)
 */
t_dbuf	buf_insertc(t_dbuf buf, t_cbuf insrt, size_t i, t_buf_strat mode)
{
	size_t	j;
	t_dbuf	res;
	size_t	new_size;
	size_t	orig_len;

	if (buf.data == NULL)
		return (dbuf_c(insrt));
	if (insrt.data == NULL)
		return (buf);
	1 && (j = 0, new_size = buf.len + insrt.size, orig_len = buf.len);
	if (i > buf.len)
		i = buf.len;
	res = buf_realloc(buf, new_size, mode);
	if (res.data == NULL)
		return (res);
	buf_shift_right(res, i, orig_len, insrt.size);
	while (j < insrt.size)
		1 && (((t_u8 *)res.data)[i + j] = ((const t_u8 *)insrt.data)[j], j++);
	return (res.len = new_size, res);
}

/**
 * buf_insert - Inserts a dynamic buffer into another buffer
 *
 * MEMORY OWNERSHIP: This function always frees 'insrt' and may reallocate
 * 'buf' if more space is needed. Always reassign the result:
 *     buf = buf_insert(buf, insrt, i, mode);  // ✓ Correct usage
 * The 'buf' is freed only if reallocation occurs.
 *
 * @param buf The t_dbuf to insert into (may be freed if reallocated)
 * @param insrt The t_dbuf to insert (always freed)
 * @param i The position to insert at
 * @param mode The buffer strategy mode
 *    - E_  : Only allocate the exact needed size
 *    - x2_ : Double the buffer size if needed
 * @return A t_dbuf with the inserted content (may be same or new buffer)
 */
t_dbuf	buf_insert(t_dbuf buf, t_dbuf insrt, size_t i, t_buf_strat mode)
{
	size_t	j;
	t_dbuf	res;
	size_t	new_size;
	size_t	orig_len;

	if (buf.data == NULL)
		return (res = dbuf_d(insrt), free_dbuf(&insrt), res);
	if (insrt.data == NULL)
		return (buf);
	1 && (j = 0, new_size = buf.len + insrt.len, orig_len = buf.len);
	if (i > buf.len)
		i = buf.len;
	res = buf_realloc(buf, new_size, mode);
	if (res.data == NULL)
		return (free_dbuf(&insrt), res);
	buf_shift_right(res, i, orig_len, insrt.len);
	while (j < insrt.len)
		1 && (((t_u8 *)res.data)[i + j] = ((t_u8 *)insrt.data)[j], j++);
	return (free_dbuf(&insrt), res.len = new_size, res);
}

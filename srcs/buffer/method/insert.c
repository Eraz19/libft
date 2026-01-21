/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 16:00:00 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/21 15:55:31 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_buffer.h"

/**
 * buf_realloc - Reallocates a dynamic buffer if needed
 *
 * MEMORY OWNERSHIP: This function consumes (frees) the input 'buf', the
 * original 'buf' becomes invalid.
 * To keep a copy of the buffer, first duplicate it before.
 * Always reassign the result:
 *     t_dbuf buf_copy = dbuf_d(original_buf);
 *     buf_copy = buf_realloc(buf_copy, new_size, mode); // ✓ Correct usage
 *     original_buf                                      // ✓ remains valid
 *
 * @param buf The t_dbuf to reallocate (always freed)
 * @param new_size The new size required
 * @param mode The buffer strategy mode
 *    - E  : Only allocate the exact needed size
 *    - x2 : Double the buffer size if needed
 * @return A new t_dbuf containing the reallocation of the original buffer
 *
 * @args: If new_size <= buf.size, returns buf untouched.
 * @error: If allocation fails, returns a NULL t_dbuf (errno ENOMEM).
 *
 */
static t_dbuf	buf_realloc(t_dbuf *buf, size_t new_size, t_buf_strat mode)
{
	size_t	i;
	t_dbuf	new_buf;
	size_t	target_size;

	1 && (i = 0, target_size = buf->size * 2);
	if (new_size > buf->size)
	{
		if (mode == x2)
		{
			while (target_size < new_size)
				target_size *= 2;
			new_buf = dbuf_s(target_size);
		}
		else
			new_buf = dbuf_s(new_size);
		if (new_buf.data == NULL)
			return (free_dbuf(buf), new_buf);
		while (i < buf->len)
			1 && (((t_u8 *)new_buf.data)[i] = ((t_u8 *)buf->data)[i], ++i);
		return (new_buf.len = buf->len, free_dbuf(buf), new_buf);
	}
	return (*buf);
}

/**
 * buf_shift_right - Shifts bytes right to make room for insertion
 *
 * @param res The t_dbuf containing the data to shift
 * @param i The starting position for the shift
 * @param orig_len The original length of the buffer
 * @param gap The number of positions to shift by
 */
static void	buf_shift_right(t_dbuf res, size_t i, size_t orig_len, size_t gap)
{
	if (i < orig_len)
	{
		while (orig_len > i)
		{
			orig_len--;
			((t_u8 *)res.data)[orig_len + gap] = ((t_u8 *)res.data)[orig_len];
		}
	}
}

/**
 * buf_insertc - Inserts a constant buffer into a dynamic buffer
 *
 * MEMORY OWNERSHIP: This function consumes (frees) the input 'buf' if a
 * reallocation is needed to accommodate the new content and returns a newly
 * allocated buffer.
 * The original 'buf' pointer becomes invalid if a reallocation occurs.
 * To keep a copy of the buffer, first duplicate it before.
 * Always reassign the result:
 *     t_dbuf buf_copy = dbuf_d(original_buf);
 *     buf_copy = buf_insertc(&buf_copy, insert_buf, i, E); // ✓ Correct usage
 *     original_buf                                         // ✓ remains valid
 *
 * @param buf The pointer to the t_dbuf to insert into (may be freed if realloc)
 * @param insrt The t_cbuf to insert
 * @param i The position to insert at (clamped to buf->len if too large)
 * @param mode The buffer strategy mode
 *    - E  : Only allocate the exact needed size
 *    - x2 : Double the buffer size if needed
 * @return A t_dbuf with the inserted content
 *
 * @args: If both buf, buf->data and insrt.data are NULL, returns a NULL t_dbuf.
 *        If only buf and buf->data is NULL, returns insrt.
 *        If only insrt.data is NULL, returns buf untouched.
 * @error: If allocation fails, returns a NULL t_dbuf (errno ENOMEM).
 */
t_dbuf	buf_insertc(t_dbuf *buf, t_cbuf insrt, size_t i, t_buf_strat mode)
{
	size_t	j;
	size_t	new_size;
	size_t	orig_len;

	if (buf == NULL || (buf->data == NULL && insrt.data == NULL))
		return (dbuf_s(0));
	if (buf->data == NULL)
		return (dbuf_c(insrt));
	if (insrt.data == NULL)
		return (*buf);
	1 && (j = 0, new_size = buf->len + insrt.size, orig_len = buf->len);
	if (i > buf->len)
		i = buf->len;
	if (new_size > buf->size)
		*buf = buf_realloc(buf, new_size, mode);
	if (buf->data == NULL)
		return (*buf);
	buf_shift_right(*buf, i, orig_len, insrt.size);
	while (j < insrt.size)
		1 && (((t_u8 *)buf->data)[i + j] = ((const t_u8 *)insrt.data)[j], j++);
	return (buf->len = new_size, *buf);
}

/**
 * buf_insert - Inserts a dynamic buffer into another dynamic buffer
 *
 * MEMORY OWNERSHIP: This function always consumes (frees) 'insrt'.
 * It also consumes (frees) 'buf' if a reallocation is needed to accommodate
 * the new content.
 * The original 'buf' pointer becomes invalid if a reallocation occurs.
 * To keep a copy of the buffer, first duplicate it before.
 * Always reassign the result:
 *     t_dbuf buf_copy = dbuf_d(original_buf);
 *     t_dbuf insert_buf = dbuf_d(buffer_to_insert);
 *     buf_copy = buf_insert(&buf_copy, &insert_buf, i, E); // ✓ Correct usage
 *     original_buf                                         // ✓ remains valid
 *     buffer_to_insert                                     // ✓ remains valid
 *
 * @param buf The pointer to the t_dbuf to insert into (may be freed if realloc)
 * @param insrt The pointer to the t_dbuf to insert (always freed)
 * @param i The position to insert at (clamped to buf->len if too large)
 * @param mode The buffer strategy mode
 *    - E_  : Only allocate the exact needed size
 *    - x2_ : Double the buffer size if needed
 * @return A t_dbuf with the inserted content
 *
 * @args: If both buf, insert, buf->data and insrt->data are NULL, returns a
 *            NULL t_dbuf.
 *        If only buf and buf->data is NULL, returns insrt.
 *        If only insert and insrt->data is NULL, returns buf untouched.
 * @error: If allocation fails, returns a NULL t_dbuf (errno ENOMEM).
 */
t_dbuf	buf_insert(t_dbuf *buf, t_dbuf *insrt, size_t i, t_buf_strat mode)
{
	size_t	j;
	t_dbuf	res;
	size_t	new_size;
	size_t	orig_len;

	if (buf == NULL || insrt == NULL)
		return (dbuf_s(0));
	if (buf->data == NULL && insrt->data == NULL)
		return (free_dbuf(insrt), dbuf_s(0));
	if (buf->data == NULL)
		return (res = dbuf_d(*insrt), free_dbuf(insrt), res);
	if (insrt->data == NULL)
		return (free_dbuf(insrt), *buf);
	1 && (j = 0, new_size = buf->len + insrt->len, orig_len = buf->len);
	if (i > buf->len)
		i = buf->len;
	if (new_size > buf->size)
		*buf = buf_realloc(buf, new_size, mode);
	if (buf->data == NULL)
		return (free_dbuf(insrt), *buf);
	buf_shift_right(*buf, i, orig_len, insrt->len);
	while (j < insrt->len)
		1 && (((t_u8 *)buf->data)[i + j] = ((t_u8 *)insrt->data)[j], j++);
	return (buf->len = new_size, free_dbuf(insrt), *buf);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_conversion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 23:38:57 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/20 20:30:20 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

/**
 * str_from_buf - Converts a dynamic buffer to a dynamic string
 *
 * MEMORY OWNERSHIP: This function consumes (frees) the input 'buf', the
 * original 'buf' becomes invalid.
 * To keep a copy of the buffer, first duplicate it before:
 *     t_dbuf buf_copy = dbuf_d(original_buf);
 *     t_dstr str = str_from_buf(&buf_copy);
 *     original_buf // ✓ remains valid.
 *
 * @param buf The pointer to the dynamic buffer to convert (always freed)
 * @return A newly allocated t_dstr with the buf content and null terminator.
 *
 * NULL Handling: If buf->data is NULL, returns a NULL t_dstr.
 * Error handling: If allocation fails, returns a NULL t_dstr (errno ENOMEM).
 */
t_dstr	str_from_buf(t_dbuf *buf)
{
	size_t	i;
	t_dstr	str;

	if (buf->data == NULL)
		return (free_dbuf(buf), dstr_s(0));
	str = dstr_s(buf->len + 1);
	if (str.s == NULL)
		return (free_dbuf(buf), str);
	i = 0;
	while (i < buf->len)
		1 && (str.s[i] = ((t_i8 *)(buf->data))[i], ++i);
	str.s[buf->len] = '\0';
	str.len = buf->len;
	str.size = buf->len + 1;
	free_dbuf(buf);
	return (str);
}

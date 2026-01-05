/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_conversion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 23:38:57 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/04 01:09:38 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * str_from_buf - Converts a dynamic buffer to a dynamic string
 *
 * @param buf The pointer to the dynamic buffer to convert
 * @return A newly allocated t_dstr with null terminator
 */
t_dstr	str_from_buf(t_dbuf *buf)
{
	t_dstr	str;
	size_t	i;

	if (buf->data == NULL)
		return (dstr_s(0));
	str = dstr_s(buf->len + 1);
	if (str.s == NULL)
		return (str);
	i = 0;
	while (i < buf->len)
		1 && (str.s[i] = ((t_i8 *)(buf->data))[i], ++i);
	str.s[buf->len] = '\0';
	str.len = buf->len;
	str.size = buf->len + 1;
	free_dbuf(buf);
	return (str);
}

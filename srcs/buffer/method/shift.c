/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shift.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 15:41:30 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/19 18:18:24 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * buf_shift - Shifts a t_cbuf constant buffer by a given offset
 *
 * @param buf The t_cbuf to shift
 * @param offset The number of bytes to shift the buffer pointer forward
 * @return The shifted t_cbuf with updated pointer and size
 *
 * NULL Handling: If buf.data is NULL, returns a NULL t_cbuf.
 * Note: If offset > buf.size, returns a NULL t_cbuf (no data remaining).
 */
t_cbuf	buf_shift(t_cbuf buf, size_t offset)
{
	if (buf.data == NULL)
		return (buf);
	if (offset >= buf.size)
		return (cbuf(NULL, 0));
	buf.data = (const t_u8 *)(buf.data) + offset;
	buf.size -= offset;
	return (buf);
}

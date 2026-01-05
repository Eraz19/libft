/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shift.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 15:41:30 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/04 00:18:39 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * buf_shift - Shifts a t_cbuf constant buffer by a given offset
 *
 * @param buf The t_cbuf to shift
 * @param offset The number of bytes to shift the buffer pointer forward
 * @return The shifted t_cbuf with updated pointer and size, or contains NULL
 *			if offset exceeds size
 */
t_cbuf	buf_shift(t_cbuf buf, size_t offset)
{
	if (buf.data == NULL)
		return (buf);
	if (offset > buf.size)
		return (cbuf(NULL, 0));
	buf.data = (const t_u8 *)buf.data + offset;
	buf.size -= offset;
	return (buf);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 11:18:13 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/21 15:53:51 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_buffer.h"

/**
 * buf_cmp - Compares two buffers
 *
 * @param buf1 The first t_cbuf to compare
 * @param buf2 The second t_cbuf to compare
 * @return Negative if buf1 < buf2, positive if buf1 > buf2, or 0 if equal
 */
t_i32	buf_cmp(t_cbuf buf1, t_cbuf buf2)
{
	size_t		i;
	const t_u8	*b1;
	const t_u8	*b2;

	if (buf1.data == NULL && buf2.data == NULL)
		return (0);
	if (buf1.data == NULL)
		return (-1);
	if (buf2.data == NULL)
		return (1);
	1 && (i = 0, b1 = (const t_u8 *)buf1.data, b2 = (const t_u8 *)buf2.data);
	while (i < buf1.size && i < buf2.size)
	{
		if (b1[i] != b2[i])
			return (b1[i] - b2[i]);
		++i;
	}
	if (i < buf1.size)
		return (b1[i]);
	if (i < buf2.size)
		return (-b2[i]);
	return (0);
}

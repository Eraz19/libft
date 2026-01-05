/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shift.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 23:34:15 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/04 00:19:06 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * str_shift - Shifts a t_cstr constant string by a given offset
 *
 * @param str The t_cstr to shift
 * @param offset The number of bytes to shift the string pointer forward
 * @return The shifted t_cstr with updated pointer, len, and size, or contains NULL
 *			if offset exceeds len
 */
t_cstr	str_shift(t_cstr str, size_t offset)
{
	if (str.s == NULL)
		return (str);
	if (offset > str.len)
		return (cstr(NULL));
	str.s += offset;
	str.len -= offset;
	str.size -= offset;
	return (str);
}

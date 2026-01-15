/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shift.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 23:34:15 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/15 12:29:20 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * str_shift - Shifts a t_cstr constant string by a given offset
 *
 * @param str The t_cstr to shift
 * @param offset The number of characters to shift the string pointer forward
 * @return The shifted t_cstr with updated pointer, len, and size
 *
 * NULL Handling: If str.s is NULL, returns a NULL t_cstr.
 * Note: If offset > str.len, returns a NULL t_cstr (no data remaining).
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

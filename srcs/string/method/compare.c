/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:04:38 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/08 14:46:18 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * str_cmp - Compares two strings (including NULL strings)
 *
 * @param str1 The first t_cstr to compare
 * @param str2 The second t_cstr to compare
 * @return Negative if str1 < str2, positive if str1 > str2, or 0 if equal
 */
t_i32	str_cmp(t_cstr str1, t_cstr str2)
{
	size_t		i;
	const t_u8	*s1;
	const t_u8	*s2;

	if (str1.s == NULL && str2.s == NULL)
		return (0);
	if (str1.s == NULL)
		return (-1);
	if (str2.s == NULL)
		return (1);
	1 && (i = 0, s1 = (const t_u8 *)str1.s, s2 = (const t_u8 *)str2.s);
	while (i < str1.len && i < str2.len)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		++i;
	}
	if (i < str1.len)
		return (s1[i]);
	if (i < str2.len)
		return (-s2[i]);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstr.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 14:17:43 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/15 12:22:45 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * cstr - Creates a constant string structure from a string literal
 *
 * @param s Pointer to the string literal
 * @return The newly created t_cstr with len and size set
 *
 * NULL Handling: If s is NULL, returns a NULL t_cstr.
 */
t_cstr	cstr(const t_i8 *s)
{
	t_cstr	str;
	size_t	len;

	if (s == NULL)
		return (str.s = s, str.len = 0, str.size = 0, str);
	len = 0;
	while (s[len] != '\0')
		++len;
	return (str.s = s, str.len = len, str.size = str.len + 1, str);
}

/**
 * cstr_d - Converts a dynamic string structure to a constant string structure
 *
 * @param str The t_dstr to convert
 * @return A t_cstr representing the same data
 *
 * NULL Handling: If str.s is NULL, returns a NULL t_cstr.
 */
t_cstr	cstr_d(t_dstr str)
{
	t_cstr	res;

	if (str.s == NULL)
		return (cstr(NULL));
	res.s = str.s;
	res.len = str.len;
	res.size = str.size;
	return (res);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:17:47 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/12 14:13:20 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * str_trim - Trims characters from the beginning and end of a string
 *
 * MEMORY OWNERSHIP: This function consumes (frees) the input 'str', the
 * original 'str' becomes invalid.
 * To keep a copy of the string, first duplicate it before.
 * Always reassign the result:
 *     t_dstr str_copy = dstr_d(original_str);
 *     str_copy = str_trim(&str_copy, set);  // ✓ Correct usage
 *     original_str                          // ✓ remains valid
 *
 * @param str The t_dstr to trim (always freed)
 * @param set The t_cstr containing characters to remove
 * @return A new t_dstr with trimmed content
 *
 * NULL Handling: If str.s is NULL, returns a NULL t_dstr.
 *                If set.s is NULL, returns a duplicate of str.
 * Error: If allocation fails, returns a NULL t_dstr (errno ENOMEM).
 */
t_dstr	str_trim(t_dstr *str, t_cstr set)
{
	size_t	end;
	t_dstr	res;
	size_t	start;

	if (str->s == NULL)
		return (free_dstr(str), dstr_s(0));
	if (set.s == NULL)
		return (res = dstr_d(*str), free_dstr(str), res);
	1 && (start = 0, end = str->len);
	while (start < str->len && str_findchr(set, str->s[start]).s)
		++start;
	while (end > start && str_findchr(set, str->s[end - 1]).s)
		--end;
	res = str_sub(cstr_d(*str), start, end - start);
	free_dstr(str);
	return (res);
}

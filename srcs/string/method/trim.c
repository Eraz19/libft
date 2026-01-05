/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:17:47 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/02 20:50:24 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * str_trim - Trims characters from the beginning and end of a string
 *
 * MEMORY OWNERSHIP: This function consumes (frees) the input 'str' and
 * returns a newly allocated string. Always reassign the result:
 *     str = str_trim(str, set);  // ✓ Correct usage
 * The original 'str' pointer becomes invalid after this call.
 *
 * @param str The t_dstr to trim (will be freed)
 * @param set The t_cstr containing characters to remove
 * @return A new t_dstr with trimmed content
 */
t_dstr	str_trim(t_dstr str, t_cstr set)
{
	size_t	start;
	size_t	end;
	t_dstr	res;

	if (str.len == 0)
		return (free_dstr(&str), dstr_s(1));
	start = 0;
	end = str.len;
	while (start < str.len && str_findchr(set, str.s[start]).s)
		++start;
	while (end > start && str_findchr(set, str.s[end - 1]).s)
		--end;
	res = str_sub(cstr_d(str), start, end - start);
	free_dstr(&str);
	return (res);
}

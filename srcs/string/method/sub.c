/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 20:47:11 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/12 14:13:20 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libft.h"

/**
 * str_sub - Extracts a substring from a constant string
 *
 * @param str The source t_cstr
 * @param start The starting index of the substring
 * @param len The maximum length of the substring
 * @return A new t_dstr containing the substring
 *
 * NULL Handling: If str.s is NULL or start >= str.len, returns a NULL t_dstr.
 * Error: If allocation fails, returns a NULL t_dstr (errno ENOMEM).
 */
t_dstr	str_sub(t_cstr str, size_t start, size_t len)
{
	size_t	i;
	t_dstr	res;

	if (str.s == NULL || start >= str.len)
		res = dstr_s(0);
	else if (start + len > str.len)
		res = dstr_s((str.len - start) + 1);
	else
		res = dstr_s(len + 1);
	if (res.s == NULL)
		return (res);
	if (res.size == 1)
		res.s[0] = '\0';
	else
	{
		i = 0;
		while (i < res.size - 1 && start + i < str.len)
			1 && (res.s[i] = str.s[start + i], ++i);
		1 && (res.len = i, res.s[i] = '\0');
	}
	return (res);
}

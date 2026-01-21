/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repeat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 16:15:19 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/21 15:28:06 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_string.h"

/**
 * str_repeat - Repeats the given string n times and returns the new string
 *
 * @param str The string to be repeated
 * @param n The number of times to repeat the string
 * @return A new string that is the result of repeating str n times
 *
 * @args: If str.s is NULL or n is 0, returns a NULL t_dstr.
 *        If str is an empty string (str.len == 0), returns an empty string.
 * @error: If allocation fails, returns a NULL t_dstr (errno ENOMEM).
 */
t_dstr	str_repeat(t_cstr str, size_t n)
{
	size_t	i;
	size_t	j;
	t_dstr	res;

	if (str.s == NULL || n == 0)
		return (dstr_s(0));
	if (str.len == 0)
		return (dstr_s(1));
	1 && (res = dstr_s((str.len * n) + 1), i = 0);
	if (res.s == NULL)
		return (res);
	while (i < n && res.s != NULL)
	{
		j = 0;
		while (j < str.len)
			1 && (res.s[(i * str.len) + j] = str.s[j], j++);
		i++;
	}
	res.s[str.len * n] = '\0';
	res.len = str.len * n;
	return (res);
}

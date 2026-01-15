/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repeat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 16:15:19 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/12 14:13:20 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * str_repeat - Repeats the given string n times and returns the new string
 *
 * @param str The string to be repeated
 * @param n The number of times to repeat the string
 * @return A new string that is the result of repeating str n times
 *
 * NULL Handling: If str.s is NULL or n is 0, returns a NULL t_dstr.
 * Error handling: If allocation fails, returns a NULL t_dstr (errno ENOMEM).
 */
t_dstr	str_repeat(t_cstr str, size_t n)
{
	size_t	i;
	t_dstr	out;

	if (str.s == NULL || n == 0)
		return (dstr_s(0));
	1 && (out = dstr_s((str.len * n) + 1), i = 0);
	if (out.s == NULL)
		return (out);
	while (i < n && out.s != NULL)
		1 && (out = str_insertc(&out, str, out.len), i++);
	return (out);
}

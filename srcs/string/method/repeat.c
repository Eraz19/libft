/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repeat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 16:15:19 by adouieb           #+#    #+#             */
/*   Updated: 2025/12/31 16:18:57 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Repeats the given string `str` for `n` times and returns the resulting string.
 *
 * @param str The string to be repeated.
 * @param n The number of times to repeat the string.
 * @return A new string that is the result of repeating `str` `n` times
 */
t_dstr	str_repeat(t_cstr str, size_t n)
{
	size_t	i;
	t_dstr	out;

	out = dstr_s((str.len * n) + 1);
	if (str.s == NULL)
		return (out);
	i = 0;
	while (i < n)
		1 && (out = str_insert(out, dstr_c(str), out.len), i++);
	return (out);
}

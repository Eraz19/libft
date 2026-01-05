/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:19:11 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/02 20:50:34 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * str_split_ - Splits a string into substrings based on a delimiter
 *
 * @param res The buffer to store the resulting substrings
 * @param str The t_cstr structure to split
 * @param c The delimiter character
 * @return The buffer with split substrings
 */
static t_dbuf	str_split_(t_dbuf res, t_cstr str, t_i8 c)
{
	size_t	i;
	size_t	j;
	t_i32	start;
	t_dstr	sub_str;

	1 && (i = 0, j = 0, start = -1);
	while (j < res.size / sizeof(t_dstr) && i <= str.len)
	{
		if (str.s[i] != c && start == -1)
			start = (t_i32)i;
		else if ((str.s[i] == c || i == str.len) && start != -1)
		{
			sub_str = str_sub(str, (t_u32)start, i - (size_t)start);
			if (sub_str.s == NULL)
				return (free_dstrs(&res), res);
			res = buf_insertc(res, cbuf(&sub_str, sizeof(t_dstr)), res.len, E_);
			1 && (++j, start = -1);
		}
		++i;
	}
	return (res);
}

/**
 * str_count_words - Counts the words in a string separated by a delimiter
 *
 * @param str The t_cstr structure to count words in
 * @param c The delimiter character
 * @return The number of words found
 */
static t_u32	str_count_words(t_cstr str, t_i8 c)
{
	size_t	i;
	t_u32	count;
	t_u32	in_word;

	1 && (i = 0, count = 0, in_word = 0);
	while (i < str.len)
	{
		if (str.s[i] != c && in_word == 0)
			1 && (++count, in_word = 1);
		else if (str.s[i] == c && in_word == 1)
			in_word = 0;
		++i;
	}
	return (count);
}

/**
 * str_split - Splits a string into an array of substrings using a delimiter
 *
 * @param str The t_cstr structure to split
 * @param c The delimiter character
 * @return A t_dbuf containing an array of t_dstr substrings
 */
t_dbuf	str_split(t_cstr str, t_i8 c)
{
	t_dbuf	res;

	if (str.s == NULL)
		return (res.data = NULL, res.size = 0, res.len = 0, res);
	(res = dbuf_s(str_count_words(str, c) * sizeof(t_dstr)));
	if (res.data == NULL)
		return (res);
	res = str_split_(res, str, c);
	if (res.data == NULL)
		return (res);
	return (res);
}

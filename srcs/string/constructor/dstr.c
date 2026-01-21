/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dstr.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:37:01 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/21 15:33:19 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_string.h"

/**
 * dstr_d - Duplicates a dynamic string structure
 *
 * @param str The t_dstr structure to duplicate
 * @return A new t_dstr containing a copy of the string
 *
 * @args: If str.s is NULL, returns a NULL t_dstr.
 * @error: If allocation fails, returns a NULL t_dstr (errno ENOMEM).
 */
t_dstr	dstr_d(t_dstr str)
{
	size_t	i;
	t_dstr	str_;

	if (str.s == NULL)
		return (dstr_s(0));
	1 && (str_ = dstr_s(str.size), i = 0);
	if (str_.s == NULL)
		return (str_);
	while (i < str.len)
		1 && (str_.s[i] = str.s[i], ++i);
	str_.s[i] = '\0';
	str_.len = str.len;
	return (str_);
}

/**
 * dstr_s - Creates a new dynamic string structure with allocated buffer
 *
 * @param size The size of the buffer to allocate
 * @return The newly created t_dstr initialized as an empty string
 *
 * @args: If size = 0, returns a NULL t_dstr.
 * @error: If allocation fails, returns a NULL t_dstr (errno ENOMEM).
 */
t_dstr	dstr_s(size_t size)
{
	t_dstr	str;

	if (size == 0)
		return (str.s = NULL, str.len = 0, str.size = 0, str);
	str.s = malloc(sizeof(t_i8) * size);
	if (str.s == NULL)
		return (str.len = 0, str.size = 0, str);
	str.len = 0;
	str.size = size;
	str.s[0] = '\0';
	return (str);
}

/**
 * dstr_c - Creates a new dynamic string structure from a constant string
 *
 * @param str The t_cstr structure to convert
 * @return A new t_dstr containing a copy of the string
 *
 * @args: If str.s is NULL, returns a NULL t_dstr.
 * @error: If allocation fails, returns a NULL t_dstr (errno ENOMEM).
 */
t_dstr	dstr_c(t_cstr str)
{
	size_t	i;
	t_dstr	res;

	if (str.s == NULL)
		return (dstr_s(0));
	res = dstr_s(str.len + 1);
	if (res.s == NULL)
		return (res);
	i = 0;
	while (i < str.len)
		1 && (res.s[i] = str.s[i], ++i);
	res.len = i;
	res.s[i] = '\0';
	return (res);
}

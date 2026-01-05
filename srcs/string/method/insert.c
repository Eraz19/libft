/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:30:31 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/04 00:18:25 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * str_insertc - Inserts a constant string into a dynamic string
 *
 * MEMORY OWNERSHIP: This function consumes (frees) the input 'str' and
 * returns a newly allocated string. Always reassign the result:
 *     str = str_insertc(str, insrt, i);  // ✓ Correct usage
 * The original 'str' pointer becomes invalid after this call.
 *
 * @param str The t_dstr to insert into (will be freed)
 * @param insrt The t_cstr to insert
 * @param i The position to insert at
 * @return A new t_dstr with the inserted content, or contains NULL on 
 * 			allocation failure or both inputs are NULL		
 */
t_dstr	str_insertc(t_dstr str, t_cstr insrt, size_t i)
{
	size_t	j;
	t_dstr	res;

	if (str.s == NULL && insrt.s == NULL)
		return (dstr_s(0));
	res = dstr_s((str.len + insrt.len) + 1);
	if (res.s == NULL)
		return (free_dstr(&str), res);
	if (i > str.len)
		i = str.len;
	j = 0;
	while (j < str.len && j < i)
		1 && (res.s[j] = str.s[j], ++j);
	while (j - i < insrt.len)
		1 && (res.s[j] = insrt.s[j - i], ++j);
	while (j - insrt.len < str.len)
		1 && (res.s[j] = str.s[j - insrt.len], ++j);
	res.len = j;
	res.s[j] = '\0';
	return (free_dstr(&str), res);
}

/**
 * str_insert - Inserts a dynamic string into another dynamic string
 *
 * MEMORY OWNERSHIP: This function consumes (frees) both 'str' and 'insrt'
 * and returns a newly allocated string. Always reassign the result:
 *     str = str_insert(str, insrt, i);  // ✓ Correct usage
 * Both input pointers become invalid after this call.
 *
 * @param str The t_dstr to insert into (will be freed)
 * @param insrt The t_dstr to insert (will be freed)
 * @param i The position to insert at
 * @return A new t_dstr with the inserted content, or contains NULL on
 * 			allocation failure or both inputs are NULL
 */
t_dstr	str_insert(t_dstr str, t_dstr insrt, size_t i)
{
	size_t	j;
	t_dstr	res;

	if (str.s == NULL && insrt.s == NULL)
		return (dstr_s(0));
	res = dstr_s((str.len + insrt.len) + 1);
	if (res.s == NULL)
		return (free_dstr(&str), free_dstr(&insrt), res);
	if (i > str.len)
		i = str.len;
	j = 0;
	while (j < str.len && j < i)
		1 && (res.s[j] = str.s[j], ++j);
	while (j - i < insrt.len)
		1 && (res.s[j] = insrt.s[j - i], ++j);
	while (j - insrt.len < str.len)
		1 && (res.s[j] = str.s[j - insrt.len], ++j);
	res.len = j;
	res.s[j] = '\0';
	return (free_dstr(&str), free_dstr(&insrt), res);
}

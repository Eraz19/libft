/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:30:31 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/21 16:32:23 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_string.h"

/**
 * str_realloc - Reallocates a dynamic string if needed
 *
 * MEMORY OWNERSHIP: This function consumes (frees) the input 'str', the
 * original 'str' becomes invalid.
 * To keep a copy of the string, first duplicate it before.
 * Always reassign the result:
 *     t_dstr str_copy = dstr_d(original_str);
 *     str_copy = str_realloc(&str_copy, new_size); // ✓ Correct usage
 *     original_str                                 // ✓ remains valid
 *
 * @param str The pointer to the t_dstr to reallocate (always freed)
 * @param new_size The new size required
 * @return A new t_dstr containing the reallocation of the original string
 *
 * @args: If new_size = 0, returns a NULL t_dstr.
 * @error: If allocation fails, returns a NULL t_dstr (errno ENOMEM).
 *
 */
static t_dstr	str_realloc(t_dstr *str, size_t new_size)
{
	size_t	i;
	t_dstr	str_;

	if (new_size == 0)
		return (free_dstr(str), dstr_s(0));
	1 && (str_ = dstr_s(new_size), i = 0);
	if (str_.s == NULL)
		return (free_dstr(str), str_);
	while (i < str->len)
		1 && (str_.s[i] = str->s[i], ++i);
	str_.s[i] = '\0';
	return (str_.len = str->len, free_dstr(str), str_);
}

/**
 * str_shift_right - Shifts characters right to make room for insertion
 *
 * @param res The t_dstr containing the string to shift
 * @param i The starting position for the shift
 * @param origin_len The original length of the string
 * @param gap The number of positions to shift by
 */
static void	str_shift_right(t_dstr res, size_t i, size_t origin_len, size_t gap)
{
	while (origin_len > i)
	{
		origin_len--;
		((t_u8 *)res.s)[origin_len + gap] = ((t_u8 *)res.s)[origin_len];
	}
}

/**
 * str_insertc - Inserts a constant string into a dynamic string
 *
 * MEMORY OWNERSHIP: This function consumes (frees) the input 'str' if a
 * reallocation is needed to accommodate the new content and returns a newly
 * allocated string.
 * The original 'str' pointer becomes invalid if a reallocation occurs.
 * To keep a copy of the string, first duplicate it before.
 * Always reassign the result:
 *     t_dstr str_copy = dstr_d(original_str);
 *     str_copy = str_insertc(&str_copy, insert_str, i);  // ✓ Correct usage
 *     original_str                                       // ✓ remains valid
 *
 * @param str The pointer to the t_dstr to insert into (may be freed if realloc)
 * @param insrt The t_cstr to insert
 * @param i The position to insert at (clamped to str->len if too large)
 * @return A t_dstr with the inserted content
 *
 * @args: If both str, str->s and insrt.s are NULL, returns a NULL t_dstr.
 *        If only str and str->s is NULL, returns insrt.
 *        If only insrt.s is NULL, returns str untouched.
 * @error: If allocation fails, returns a NULL t_dstr (errno ENOMEM).
 */
t_dstr	str_insertc(t_dstr *str, t_cstr insrt, size_t i)
{
	size_t	j;
	size_t	new_size;
	size_t	origin_len;

	if (str == NULL || (str->s == NULL && insrt.s == NULL))
		return (dstr_s(0));
	if (str->s == NULL)
		return (dstr_c(insrt));
	if (insrt.s == NULL)
		return (*str);
	1 && (j = 0, new_size = str->len + insrt.len, origin_len = str->len);
	if (i > str->len)
		i = str->len;
	if (new_size + 1 > str->size)
		*str = str_realloc(str, new_size + 1);
	if (str->s == NULL)
		return (*str);
	str_shift_right(*str, i, origin_len, insrt.len);
	while (j < insrt.len)
		1 && (((t_u8 *)str->s)[i + j] = ((const t_u8 *)insrt.s)[j], j++);
	str->s[new_size] = '\0';
	return (str->len = new_size, *str);
}

/**
 * str_insert - Inserts a dynamic string into another dynamic string
 *
 * MEMORY OWNERSHIP: This function always consumes (frees) 'insrt'.
 * It also consumes (frees) 'str' if a reallocation is needed to accommodate
 * the new content.
 * The original 'str' pointer becomes invalid if a reallocation occurs.
 * To keep a copy of the string, first duplicate it before.
 * Always reassign the result:
 *     t_dstr str_copy = dstr_d(original_str);
 *     t_dstr insert_str = dstr_d(string_to_insert);
 *     str_copy = str_insert(&str_copy, &insert_str, i); // ✓ Correct usage
 *     original_str                                      // ✓ remains valid
 *     string_to_insert                                  // ✓ remains valid
 *
 * @param str The pointer to the t_dstr to insert into (may be freed if realloc)
 * @param insrt The pointer to the t_dstr to insert (always freed)
 * @param i The position to insert at (clamped to str->len if too large)
 * @return A t_dstr with the inserted content
 *
 * @args: If both str, insert, str->s and insrt.s are NULL, returns a NULL
 *            t_dstr.
 *        If only str and str->s is NULL, returns insrt.
 *        If only insert and insrt.s is NULL, returns str untouched.
 * @error: If allocation fails, returns a NULL t_dstr (errno ENOMEM).
 */
t_dstr	str_insert(t_dstr *str, t_dstr *insrt, size_t i)
{
	size_t	j;
	t_dstr	res;
	size_t	new_size;
	size_t	origin_len;

	if ((str == NULL && insrt == NULL) || (str->s == NULL && insrt->s == NULL))
		return (dstr_s(0));
	if (str == NULL || str->s == NULL)
		return (res = dstr_d(*insrt), free_dstr(insrt), res);
	if (insrt == NULL || insrt->s == NULL)
		return (free_dstr(insrt), *str);
	1 && (j = 0, new_size = str->len + insrt->len, origin_len = str->len);
	if (i > str->len)
		i = str->len;
	if (new_size + 1 > str->size)
		*str = str_realloc(str, new_size + 1);
	if (str->s == NULL)
		return (free_dstr(insrt), *str);
	str_shift_right(*str, i, origin_len, insrt->len);
	while (j < insrt->len)
		1 && (((t_u8 *)str->s)[i + j] = ((const t_u8 *)insrt->s)[j], j++);
	str->s[new_size] = '\0';
	return (str->len = new_size, free_dstr(insrt), *str);
}

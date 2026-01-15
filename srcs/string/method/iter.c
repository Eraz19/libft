/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:20:50 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/12 14:13:20 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * str_foreach - Applies a function to each element of a string for side effects
 *
 * @param str The t_cstr structure to iterate over
 * @param f The function to apply to each character (with index)
 * @return void
 *
 * NULL Handling: Does nothing if str.s is NULL t_cstr or f is NULL
 */
void	str_foreach(t_cstr str, void (*f)(t_u32, t_i8))
{
	size_t	i;

	i = 0;
	if (str.s == NULL || f == NULL)
		return ;
	while (i < str.len)
		(f((t_u32)i, str.s[i]), ++i);
}

/**
 * str_map - Applies a function to each character to create a new string
 *
 * MEMORY OWNERSHIP: This function consumes (frees) the input 'str', the
 * original 'str' becomes invalid.
 * To keep a copy of the string, first duplicate it before.
 * Always reassign the result:
 *     t_dstr str_copy = dstr_d(original_str);
 *     str_copy = str_map(&str_copy, transform_func);  // ✓ Correct usage
 *     original_str                                    // ✓ remains valid
 *
 * @param str The pointer to the t_dstr to map over (always freed)
 * @param f The function to apply to each character (with index)
 * @return A new t_dstr with the transformed characters
 *
 * NULL Handling: if str.s is NULL or f is NULL, returns a NULL t_dstr.
 * Error: If allocation fails, returns a NULL t_dstr (errno ENOMEM).
 */
t_dstr	str_map(t_dstr *str, t_i8 (*f)(t_u32, t_i8))
{
	size_t	i;
	t_dstr	res;

	i = 0;
	if (str->s == NULL || f == NULL)
		return (free_dstr(str), dstr_s(0));
	res = dstr_s(str->size);
	if (res.s == NULL)
		return (free_dstr(str), res);
	while (i < str->len)
		1 && (res.s[i] = f((t_u32)i, str->s[i]), ++i);
	res.s[i] = '\0';
	res.len = str->len;
	free_dstr(str);
	return (res);
}

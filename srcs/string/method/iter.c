/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:20:50 by adouieb           #+#    #+#             */
/*   Updated: 2025/12/30 22:52:48 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * str_foreach - Applies a function to each element of a string for side effects
 *
 * @param str The t_cstr structure to iterate over
 * @param f The function to apply to each character (with index)
 */
void	str_foreach(t_cstr str, void (*f)(t_u32, t_i8))
{
	size_t	i;

	i = 0;
	while (i < str.len)
		(f((t_u32)i, str.s[i]), ++i);
}

/**
 * str_map - Applies a function to each character to create a new string
 *
 * MEMORY OWNERSHIP: This function consumes (frees) the input 'str' and
 * returns a newly allocated string. Always reassign the result:
 *     str = str_map(str, transform_func);  // ✓ Correct usage
 *
 * @param str The t_dstr to map over (will be freed)
 * @param f The function to apply to each character (with index)
 * @return A new t_dstr with the transformed characters
 */
t_dstr	str_map(t_dstr str, t_i8 (*f)(t_u32, t_i8))
{
	size_t	i;
	t_dstr	res;

	i = 0;
	res = dstr_s(str.size);
	if (res.s == NULL)
		return (free_dstr(&str), res);
	while (i < str.len)
		1 && (res.s[i] = f((t_u32)i, str.s[i]), ++i);
	res.s[i] = '\0';
	res.len = str.len;
	free_dstr(&str);
	return (res);
}

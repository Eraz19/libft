/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_conversion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 23:35:24 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/21 15:31:32 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_string.h"

/**
 * str_from_char - Converts an character to a string
 *
 * @param c The character to convert
 * @return A new t_dstr containing the character as a string
 *
 * @error: If allocation fails, returns a NULL t_dstr (errno ENOMEM).
 */
t_dstr	str_from_char(t_i8 c)
{
	t_dstr	str;

	str = dstr_s(2);
	if (str.s == NULL)
		return (str);
	str.s[0] = c;
	str.s[1] = '\0';
	str.len = 1;
	return (str);
}

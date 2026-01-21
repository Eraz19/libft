/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 17:03:08 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/21 16:39:16 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

/**
 * str_from_args_str - Interpret printf args as string and convert to t_dstr.
 *
 * @param value The argument value
 * @param content The rule content defining the interpretation of the args
 * @return The result of the interpretation of the string arg
 *
 * @error: On allocation failure, returns a NULL t_dstr (errno ENOMEM).
 */
static t_dstr	str_from_args_str(t_args_types value, t_rule_content *content)
{
	if (value._ptr == NULL)
	{
		if (content->prec >= 0 && content->prec < 6)
			content->prec = 0;
		return (dstr_c(cstr("(null)")));
	}
	return (dstr_c(cstr(value._ptr)));
}

/**
 * str_from_args_ptr - Interpret printf args as pointer and convert to t_dstr.
 *
 * @param value The argument value
 * @param content The rule content defining the interpretation of the args
 * @return The result of the interpretation of the pointer arg
 *
 * @error: On allocation failure, returns a NULL t_dstr (errno ENOMEM).
 */
static t_dstr	str_from_args_ptr(t_args_types value, t_rule_content *content)
{
	if (value._addr == NULL)
		return (dstr_c(cstr("(nil)")));
	content->out = out_alt;
	return (str_from_long((t_i64)value._addr, cstr(CHARSET_HEX), FALSE));
}

/**
 * str_from_args - Interpret printf args based on rule and convert to t_dstr.
 *
 * @param value The argument value
 * @param content The rule content defining the interpretation of the args
 * @return The result of the interpretation of the args
 *
 * @error: On allocation failure, returns a NULL t_dstr (errno ENOMEM).
 */
t_dstr	str_from_args(t_args_types value, t_rule_content *content)
{
	if (content->type == _char)
		return (str_from_char((t_i8)value._char));
	else if (content->type == _str)
		return (str_from_args_str(value, content));
	else if (content->type == _dec || content->type == _int)
		return (str_from_int(value._int, cstr(CHARSET_DEC), TRUE));
	else if (content->type == _usign)
		return (str_from_int(value._int, cstr(CHARSET_DEC), FALSE));
	else if (content->type == _hex)
		return (str_from_int(value._int, cstr(CHARSET_HEX), FALSE));
	else if (content->type == _HEX)
		return (str_from_int(value._int, cstr(CHARSET_UHEX), FALSE));
	if (content->type == _ptr)
		return (str_from_args_ptr(value, content));
	return (str_from_char('%'));
}

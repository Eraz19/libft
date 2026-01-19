/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 17:03:08 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/19 18:49:25 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_dstr	str_from_args_str(t_args_types value, t_rule_ctnt *ctnt)
{
	if (value._ptr == NULL)
	{
		if (ctnt->prec >= 0 && ctnt->prec < 6)
			ctnt->prec = 0;
		return (dstr_c(cstr("(null)")));
	}
	return (dstr_c(cstr(value._ptr)));
}

static t_dstr	str_from_args_ptr(t_args_types value, t_rule_ctnt *ctnt)
{
	if (value._addr == NULL)
		return (dstr_c(cstr("(nil)")));
	ctnt->out = out_alt;
	return (str_from_long((t_i64)value._addr, cstr(CHARSET_HEX), FALSE));
}

t_dstr	str_from_args(t_args_types value, t_rule_ctnt *ctnt)
{
	if (ctnt->type == _char)
		return (str_from_char((t_i8)value._char));
	else if (ctnt->type == _str)
		return (str_from_args_str(value, ctnt));
	else if (ctnt->type == _dec || ctnt->type == _int)
		return (str_from_int(value._int, cstr(CHARSET_DEC), TRUE));
	else if (ctnt->type == _usign)
		return (str_from_int(value._int, cstr(CHARSET_DEC), FALSE));
	else if (ctnt->type == _hex)
		return (str_from_int(value._int, cstr(CHARSET_HEX), FALSE));
	else if (ctnt->type == _HEX)
		return (str_from_int(value._int, cstr(CHARSET_UHEX), FALSE));
	if (ctnt->type == _ptr)
		return (str_from_args_ptr(value, ctnt));
	return (str_from_char('%'));
}

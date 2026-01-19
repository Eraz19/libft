/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 15:53:51 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/19 19:05:30 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_dstr	apply_flag_altout(t_dstr out, t_rule_ctnt *content)
{
	size_t	i;

	if (content->out == out_alt)
	{
		if ((content->type == _hex || content->type == _HEX))
		{
			i = 0;
			while (i < out.len && out.s[i] == '0')
				++i;
			if (i == out.len)
				return (out);
			if (content->type == _hex)
				return (str_insertc(&out, cstr("0x"), 0));
			else
				return (str_insertc(&out, cstr("0X"), 0));
		}
		else if (content->type == _ptr)
			return (str_insertc(&out, cstr("0x"), 0));
	}
	return (out);
}

static t_dstr	apply_flag_prec(t_dstr out, t_rule_ctnt *content)
{
	t_rule_type	rule_type;

	if (content->prec < 0)
		return (out);
	1 && (rule_type = content->type);
	if (rule_type == _str)
		out = apply_flag_prec_str(out, content);
	else if (rule_type == _usign || rule_type == _hex || rule_type == _HEX)
	{
		out = apply_flag_prec_uint(out, content);
		if (content->pad == pad_zero)
			content->pad = pad_std;
	}
	else if (rule_type == _int || rule_type == _dec)
	{
		out = apply_flag_prec_int(out, content);
		if (content->pad == pad_zero)
			content->pad = pad_std;
	}
	return (out);
}

static t_dstr	apply_flag_pad(t_dstr out, t_rule_ctnt *content)
{
	t_dstr		pad;
	size_t		rule_width;

	rule_width = (size_t)content->width;
	if (rule_width > out.len)
	{
		if (content->pad == pad_zero)
			pad = str_repeat(cstr("0"), rule_width - out.len);
		else
			pad = str_repeat(cstr(" "), rule_width - out.len);
		if (content->pad == pad_right)
			return (str_insert(&out, &pad, out.len));
		else
		{
			if (content->pad == pad_zero && out.len > 1
				&& (out.s[0] == '0' && (out.s[1] == 'x' || out.s[1] == 'X')))
				return (str_insert(&out, &pad, 2));
			else if (content->pad == pad_zero && out.len > 0
				&& (out.s[0] == '-' || out.s[0] == '+' || out.s[0] == ' '))
				return (str_insert(&out, &pad, 1));
			else
				return (str_insert(&out, &pad, 0));
		}
	}
	return (out);
}

static t_dstr	apply_flag_sign(t_dstr out, t_rule_ctnt *content)
{
	t_bool	is_neg;

	is_neg = FALSE;
	if (out.len != 0 && out.s[0] == '-')
		is_neg = TRUE;
	if (content->sign == sign_space && is_neg == FALSE)
		return (str_insertc(&out, cstr(" "), 0));
	else if (content->sign == sign_plus && is_neg == FALSE)
		return (str_insertc(&out, cstr("+"), 0));
	return (out);
}

t_dstr	apply_flags(t_dstr str, t_rule_ctnt *content)
{
	t_dstr	out;

	out = str;
	if (out.s == NULL)
		return (out);
	if (content->type != _perc)
	{
		if (content->type != _char && content->type != _ptr)
			out = apply_flag_prec(out, content);
		if (content->type == _hex || content->type == _HEX)
			out = apply_flag_altout(out, content);
		else if (content->type == _ptr)
			out = apply_flag_altout(out, content);
		if (content->type == _dec || content->type == _int)
			out = apply_flag_sign(out, content);
		out = apply_flag_pad(out, content);
	}
	return (out);
}

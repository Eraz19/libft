/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_precision.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 13:17:54 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/21 16:53:01 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

/**
 * apply_flag_prec_str - Applies precision flag on string args
 *
 * @param out The original output string
 * @param content The rule content containing precision info
 * @return The modified string with precision applied
 *
 * @error: On allocation failure, returns a NULL t_dstr (errno ENOMEM).
 */
t_dstr	apply_flag_prec_str(t_dstr out, t_rule_content *content)
{
	t_dstr	res;
	size_t	prec;

	prec = (size_t)content->prec;
	if (prec < out.len)
		return (res = str_sub(cstr_d(out), 0, prec), free_dstr(&out), res);
	return (out);
}

/**
 * apply_flag_prec_int - Applies precision flag on signed integer args
 *
 * @param out The original output string
 * @param content The rule content containing precision info
 * @return The modified string with precision applied
 *
 * @error: On allocation failure, returns a NULL t_dstr (errno ENOMEM).
 */
t_dstr	apply_flag_prec_int(t_dstr out, t_rule_content *content)
{
	t_dstr	pad;
	size_t	prec;
	size_t	digit_len;

	1 && (digit_len = out.len, prec = (size_t)content->prec);
	if (out.len > 0 && out.s[0] == '-')
		digit_len = out.len - 1;
	if (content->prec == 0 && out.len == 1 && out.s[0] == '0')
		return (free_dstr(&out), dstr_c(cstr("")));
	if (prec > digit_len)
	{
		pad = str_repeat(cstr("0"), prec - digit_len);
		if (out.len > 0 && out.s[0] == '-')
			return (str_insert(&out, &pad, 1));
		else
			return (str_insert(&out, &pad, 0));
	}
	return (out);
}

/** 
 * apply_flag_prec_uint - Applies precision flag on unsigned integer args
 *
 * @param out The original output string
 * @param content The rule content containing precision info
 * @return The modified string with precision applied
 *
 * @error: On allocation failure, returns a NULL t_dstr (errno ENOMEM).
 */
t_dstr	apply_flag_prec_uint(t_dstr out, t_rule_content *content)
{
	t_dstr	pad;
	size_t	prec;

	prec = (size_t)content->prec;
	if (content->prec == 0 && out.len == 1 && out.s[0] == '0')
		return (free_dstr(&out), dstr_c(cstr("")));
	if (prec > out.len)
	{
		pad = str_repeat(cstr("0"), prec - out.len);
		return (str_insert(&out, &pad, 0));
	}
	return (out);
}

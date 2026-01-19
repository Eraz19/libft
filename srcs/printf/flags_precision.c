/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_precision.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 13:17:54 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/19 18:57:25 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dstr	apply_flag_prec_str(t_dstr out, t_rule_ctnt *content)
{
	t_dstr	res;
	size_t	prec;

	prec = (size_t)content->prec;
	if (prec < out.len)
		return (res = str_sub(cstr_d(out), 0, prec), free_dstr(&out), res);
	return (out);
}

t_dstr	apply_flag_prec_int(t_dstr out, t_rule_ctnt *ctnt)
{
	t_dstr	pad;
	size_t	prec;
	size_t	digit_len;

	1 && (digit_len = out.len, prec = (size_t)ctnt->prec);
	if (out.len > 0 && out.s[0] == '-')
		digit_len = out.len - 1;
	if (ctnt->prec == 0 && out.len == 1 && out.s[0] == '0')
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

t_dstr	apply_flag_prec_uint(t_dstr out, t_rule_ctnt *content)
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

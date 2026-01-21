/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 10:31:26 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/20 19:31:13 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static t_dstr	append_rule_result(t_dstr *res, t_rule *rule, va_list ap)
{
	t_dstr			out;
	t_args_types	args;

	args._int = 0;
	if (rule->content->type != _perc)
	{
		if (rule->content->type == _ptr)
			args._addr = va_arg(ap, void *);
		else if (rule->content->type == _char)
			args._char = (t_i8)va_arg(ap, int);
		else if (rule->content->type == _str)
			args._ptr = va_arg(ap, char *);
		else
			args._int = va_arg(ap, int);
	}
	out = str_from_args(args, rule->content);
	out = apply_flags(out, rule->content);
	if (out.s == NULL)
		return (dstr_c(cstr(NULL)));
	*res = str_insert(res, &out, res->len);
	return (out);
}

static void	append_fmt_out_rule(t_dstr *res, t_cstr fmt_, size_t len)
{
	t_dstr	sub_buf;

	sub_buf = str_sub(fmt_, 0, len);
	*res = str_insert(res, &sub_buf, res->len);
}

static t_i32	print_result(t_dstr str, t_rules *rules, va_list ap)
{
	t_i32	len;

	if (rules->nodes != NULL)
		free_lst(rules, ft_free_rule_content);
	str_print(cstr_d(str), STDOUT_FILENO);
	len = (t_i32)str.len;
	free_dstr(&str);
	va_end(ap);
	return (len);
}

t_i32	ft_printf(const t_i8 *fmt, ...)
{
	va_list	ap;
	t_dstr	res;
	t_cstr	fmt_;
	t_rules	rules;

	va_start(ap, fmt);
	res = dstr_s(0);
	fmt_ = cstr(fmt);
	rules = ft_parse_fmt(fmt_);
	while (rules.size != 0)
	{
		if (((t_rule *)rules.nodes)->content->type == _error)
			return (print_result(res, &rules, ap));
		append_fmt_out_rule(&res, fmt_, (size_t)str_findindex(fmt_, R_DEL));
		if (res.s == NULL)
			return (print_result(res, &rules, ap));
		fmt_ = str_findchr(fmt_, R_DEL);
		append_rule_result(&res, (t_rule *)rules.nodes, ap);
		if (res.s == NULL)
			return (print_result(res, &rules, ap));
		fmt_ = str_shift(fmt_, ((t_rule *)rules.nodes)->content->len + 1);
		free_node(&rules, (t_node *)rules.nodes, ft_free_rule_content);
	}
	append_fmt_out_rule(&res, fmt_, fmt_.len);
	return (print_result(res, &rules, ap));
}

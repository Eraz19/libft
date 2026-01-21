/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 10:31:26 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/21 16:52:59 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include <stdarg.h>

/**
 * append_rule_result - Appends the formatted output to the result based on rule
 *
 * @param res Pointer to the result string
 * @param rule Pointer to the rule to process
 * @param ap The variable argument list
 * @return void
 *
 * @error: On allocation failure, sets res->s to NULL (errno ENOMEM).
 */
static void	append_rule_result(t_dstr *res, t_rule *rule, va_list ap)
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
		*res = out;
	*res = str_insert(res, &out, res->len);
}

/**
 * append_fmt_out_rule - Appends the non-format portion of the format string
 *
 * @param res Pointer to the result string
 * @param fmt_ The current position in the format string
 * @param len The length of the non-format portion to append
 * @return void
 *
 * @error: On allocation failure, sets res->s to NULL (errno ENOMEM).
 */
static void	append_fmt(t_dstr *res, t_cstr fmt_, size_t len)
{
	t_dstr	sub_buf;

	sub_buf = str_sub(fmt_, 0, len);
	*res = str_insert(res, &sub_buf, res->len);
}

/** 
 * print_result - Prints the final result and cleans up
 *
 * @param str The final result string to print
 * @param rules Pointer to the rules list to free
 * @param ap The variable argument list to end
 * @return The length of the printed string
 */
static t_i32	print_result(t_dstr str, t_rules *rules, va_list ap)
{
	t_i32	len;

	if (rules->nodes != NULL)
		free_lst(rules, free_rule_content);
	str_print(cstr_d(str), STDOUT_FILENO);
	len = (t_i32)str.len;
	free_dstr(&str);
	va_end(ap);
	return (len);
}

/**
 * ft_printf - Custom implementation of printf function
 *
 * @param fmt The format string
 * @param ... Variable arguments to format (variadic)
 * @return The number of characters printed
 */
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
		append_fmt(&res, fmt_, (size_t)str_findindex(fmt_, R_DEL));
		if (res.s == NULL)
			return (print_result(res, &rules, ap));
		fmt_ = str_findchr(fmt_, R_DEL);
		append_rule_result(&res, (t_rule *)rules.nodes, ap);
		if (res.s == NULL)
			return (print_result(res, &rules, ap));
		fmt_ = str_shift(fmt_, ((t_rule *)rules.nodes)->content->len + 1);
		free_node(&rules, (t_node *)rules.nodes, free_rule_content);
	}
	append_fmt(&res, fmt_, fmt_.len);
	return (print_result(res, &rules, ap));
}

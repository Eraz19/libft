/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 09:48:42 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/19 19:08:09 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_rule_type	parse_rule_type(t_i8 c)
{
	if (c == 'c')
		return (_char);
	else if (c == 's')
		return (_str);
	else if (c == 'p')
		return (_ptr);
	else if (c == 'd')
		return (_dec);
	else if (c == 'i')
		return (_int);
	else if (c == 'u')
		return (_usign);
	else if (c == 'x')
		return (_hex);
	else if (c == 'X')
		return (_HEX);
	else if (c == '%')
		return (_perc);
	else
		return (_error);
}

static t_bool	parse_flags(t_rule_ctnt *content, t_i8 c)
{
	if (c == '0' || c == '-' || c == ' ' || c == '+' || c == '#')
	{
		if (c == '0' && content->pad == pad_std)
			content->pad = pad_zero;
		else if (c == '-')
			content->pad = pad_right;
		else if (c == ' ' && content->sign == sign_std)
			content->sign = sign_space;
		else if (c == '+')
			content->sign = sign_plus;
		else if (c == '#')
			content->out = out_alt;
		return (TRUE);
	}
	else
		return (FALSE);
}

static t_bool	is_parsable(t_rule_ctnt *content, const t_i8 c)
{
	return (c != '\0' && content->type != _error);
}

static t_rule	*parse_rule(t_rule *rule, t_cstr fmt)
{
	size_t		i;
	t_rule_ctnt	*content;

	1 && (i = 0, content = rule->content);
	if (fmt.s[i] != '%')
	{
		while (is_parsable(content, fmt.s[i]) && parse_flags(content, fmt.s[i]))
			++i;
		while (is_parsable(content, fmt.s[i]) && c_isdigit(fmt.s[i]))
			content->width = (content->width * 10) + (fmt.s[i++] - '0');
		if (fmt.s[i] == '.')
		{
			1 && (++i, content->prec = 0);
			while (is_parsable(content, fmt.s[i]) && c_isdigit(fmt.s[i]))
				content->prec = (content->prec * 10) + (fmt.s[i++] - '0');
		}
	}
	content->type = parse_rule_type(fmt.s[i]);
	content->len = i + 1;
	return (rule);
}

t_rules	ft_parse_fmt(t_cstr fmt)
{
	t_rules	rules;
	t_rule	*new_rule;

	1 && (rules = lst_(), new_rule = NULL);
	while (fmt.s != NULL)
	{
		fmt = str_findchr(fmt, R_DEL);
		if (fmt.s != NULL)
		{
			new_rule = rule();
			if (new_rule == NULL)
				return (free_lst(&rules, ft_free_rule_content), rules);
			new_rule = parse_rule(new_rule, str_shift(fmt, 1));
			lst_insert(&rules, (t_node *)new_rule, rules.size);
			if (new_rule->content->type == _error)
				return (rules);
			fmt = str_shift(fmt, new_rule->content->len + 1);
		}
	}
	return (rules);
}

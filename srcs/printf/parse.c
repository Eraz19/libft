/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 09:48:42 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/21 15:08:50 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "libft_char.h"

/**
 * parse_rule_type - Parses the rule type from a character
 *
 * @param c The character representing the rule type
 * @return The corresponding t_rule_type enum value
 */
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

/**
 * parse_flags - Parses formatting flags from the format string
 *
 * @param content The rule content to populate with flags
 * @param c The current character to parse
 * @return TRUE if a flag was parsed, FALSE otherwise
 */
static t_bool	parse_flags(t_rule_content *content, t_i8 c)
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

/**
 * is_parsable - Checks if the current character can be parsed
 *
 * @param content The rule content containing formatting options
 * @param c The current character to check
 * @return TRUE if the character can be parsed, FALSE otherwise
 */
static t_bool	is_parsable(t_rule_content *content, const t_i8 c)
{
	return (c != '\0' && content->type != _error);
}

/**
 * parse_rule - Parses a single formatting rule from the format string
 *
 * @param rule Pointer to the rule to populate
 * @param fmt The format string starting after the '%'
 * @return The populated rule
 */
static t_rule	*parse_rule(t_rule *rule, t_cstr fmt)
{
	size_t			i;
	t_rule_content	*content;

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

/**
 * ft_parse_fmt - Parses the format string and extracts formatting rules
 *
 * @param fmt The format string to parse
 * @return A list of parsed rules
 *
 * @error: On allocation failure, returns a NULL list (errno ENOMEM).
 */
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
				return (free_lst(&rules, free_rule_content), rules);
			new_rule = parse_rule(new_rule, str_shift(fmt, 1));
			lst_insert(&rules, (t_node *)new_rule, rules.size);
			if (new_rule->content->type == _error)
				return (rules);
			fmt = str_shift(fmt, new_rule->content->len + 1);
		}
	}
	return (rules);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 14:20:26 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/21 15:44:28 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H

# include "libft_list.h"
# include "libft_string.h"

# define R_DEL '%'

typedef enum e_pad
{
	pad_std,
	pad_right,
	pad_zero,
}	t_pad;
typedef enum e_out
{
	out_std,
	out_alt,
}	t_out;
typedef enum e_sign
{
	sign_std,
	sign_plus,
	sign_space,
}	t_sign;
typedef enum e_rule_type
{
	_default,
	_char,
	_str,
	_ptr,
	_dec,
	_int,
	_usign,
	_hex,
	_HEX,
	_perc,
	_error,
}	t_rule_type;

typedef union u_args_types
{
	t_i32	_int;
	t_i8	_char;
	t_i8	*_ptr;
	void	*_addr;
}	t_args_types;

typedef struct t_rule_content
{
	t_rule_type	type;
	t_i32		prec;
	t_i32		width;
	t_pad		pad;
	t_out		out;
	t_sign		sign;
	size_t		len;
}	t_rule_content;
typedef struct t_rule
{
	t_rule_content	*content;
	struct t_rule	*next;
}	t_rule;
typedef t_lst	t_rules;

t_rule	*rule(void);
void	free_rule_content(void *content);

t_rules	ft_parse_fmt(t_cstr fmt);

t_dstr	str_from_args(t_args_types value, t_rule_content *content);

t_dstr	apply_flags(t_dstr str, t_rule_content *content);
t_dstr	apply_flag_prec_str(t_dstr out, t_rule_content *content);
t_dstr	apply_flag_prec_int(t_dstr out, t_rule_content *ctnt);
t_dstr	apply_flag_prec_uint(t_dstr out, t_rule_content *content);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_printf.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 17:09:11 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/19 19:32:06 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_PRINTF_H
# define LIBFT_PRINTF_H

# include "libft_types.h"
# include "libft_string.h"
# include "libft_list.h"
# include <stdarg.h>

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

typedef struct rule_ctnt
{
	t_rule_type	type;
	t_i32		prec;
	t_i32		width;
	t_pad		pad;
	t_out		out;
	t_sign		sign;
	size_t		len;
}	t_rule_ctnt;
typedef struct s_rule
{
	t_rule_ctnt		*content;
	struct s_rule	*next;
}	t_rule;
typedef t_lst	t_rules;

t_i32	ft_printf(const t_i8 *fmt, ...);

t_rule	*rule(void);

void	ft_free_rule_content(void *content);

t_dstr	apply_flags(t_dstr str, t_rule_ctnt *content);
t_dstr	apply_flag_prec_str(t_dstr out, t_rule_ctnt *content);
t_dstr	apply_flag_prec_int(t_dstr out, t_rule_ctnt *content);
t_dstr	apply_flag_prec_uint(t_dstr out, t_rule_ctnt *content);

t_dstr	str_from_args(t_args_types value, t_rule_ctnt *content);
t_rules	ft_parse_fmt(t_cstr fmt);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_char.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 19:05:18 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/21 20:05:50 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_CHAR_H
# define LIBFT_CHAR_H

# include "libft_types.h"

t_bool	c_isalpha(t_i32 c);
t_bool	c_isdigit(t_i32 c);
t_bool	c_isalnum(t_i32 c);
t_bool	c_isascii(t_i32 c);
t_bool	c_isprint(t_i32 c);
t_bool	c_isspace(t_i32 c);
t_i32	c_tolower(t_i32 c);
t_i32	c_toupper(t_i32 c);
t_bool	c_ishexdigit(t_i32 c);
t_bool	c_isuppercase(t_i32 c);
t_bool	c_islowercase(t_i32 c);

#endif

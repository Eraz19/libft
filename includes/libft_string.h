/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_string.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 19:05:18 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/04 01:09:03 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_STRING_H
# define LIBFT_STRING_H

# include "libft_types.h"

t_cstr	cstr_d(t_dstr str);
t_cstr	cstr(const t_i8 *s);

t_dstr	dstr_d(t_dstr str);
t_dstr	dstr_c(t_cstr str);
t_dstr	dstr_s(size_t size);

void	free_dstr(t_dstr *str);
void	free_dstrs(t_dbuf *str_buf);

t_dstr	str_from_char(t_i8 c);

t_i32	str_cmp(t_cstr str1, t_cstr str2);
t_i32	str_ncmp(t_cstr str1, t_cstr str2, size_t n);

t_cstr	str_findchr(t_cstr str, t_i32 c);
ssize_t	str_findindex(t_cstr str, t_i8 c);
t_cstr	str_findsub(t_cstr str, t_cstr sub);
t_cstr	str_findlastchr(t_cstr str, t_i32 c);
ssize_t	str_findlastindex(t_cstr str, t_i8 c);

t_dstr	str_insert(t_dstr str, t_dstr insrt, size_t i);
t_dstr	str_insertc(t_dstr str, t_cstr insrt, size_t i);

t_i32	str_to_int(t_cstr nptr, t_cstr base);
t_dstr	str_from_int(t_i32 n, t_cstr base, t_bool sign);

t_dstr	str_from_buf(t_dbuf *buf);

t_dstr	str_from_char(t_i8 c);

t_i64	str_to_long(t_cstr nptr, t_cstr base);
t_dstr	str_from_long(t_i64 n, t_cstr base, t_bool sign);

t_dstr	str_map(t_dstr str, t_i8 (*f)(t_u32, t_i8));
void	str_foreach(t_cstr str, void (*f)(t_u32, t_i8));

void	str_print(t_cstr str, t_i32 fd);

t_dstr	str_repeat(t_cstr str, size_t n);

t_cstr	str_shift(t_cstr str, size_t offset);

t_dbuf	str_split(t_cstr str, t_i8 c);

t_dstr	str_sub(t_cstr str, size_t start, size_t len);

t_dstr	str_trim(t_dstr str, t_cstr set);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_types.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 19:05:18 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/21 15:27:03 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_TYPES_H
# define LIBFT_TYPES_H

# include <errno.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

# define TRUE 1
# define FALSE 0

# define I8_MIN CHAR_MIN
# define I8_MAX CHAR_MAX
# define U8_MIN 0
# define U8_MAX UCHAR_MAX
# define I16_MIN SHORT_MIN
# define I16_MAX SHORT_MAX
# define U16_MIN 0
# define U16_MAX USHORT_MAX
# define I32_MIN INT_MIN
# define I32_MAX INT_MAX
# define U32_MIN 0
# define U32_MAX UINT_MAX
# define I64_MIN LONG_MIN
# define I64_MAX LONG_MAX
# define U64_MIN 0
# define U64_MAX ULONG_MAX
# define I128_MIN LLONG_MIN
# define I128_MAX LLONG_MAX
# define U128_MIN 0
# define U128_MAX ULLONG_MAX

# define I8_BUFFER 4
# define U8_BUFFER 3
# define I16_BUFFER 6
# define U16_BUFFER 5
# define I32_BUFFER 11
# define U32_BUFFER 10
# define I64_BUFFER 20
# define U64_BUFFER 20

# define CHARSET_DEC "0123456789"
# define CHARSET_HEX "0123456789abcdef"
# define CHARSET_UHEX "0123456789ABCDEF"

# define BUF_SIZE 1024

typedef char			t_i8;
typedef unsigned char	t_u8;
typedef short			t_i16;
typedef unsigned short	t_u16;
typedef int				t_i32;
typedef unsigned int	t_u32;
typedef long			t_i64;
typedef unsigned long	t_u64;

typedef t_u32			t_bool;

typedef union u_drop_const_uc_ptr
{
	t_u8		*cast;
	const t_u8	*c_cast;
}	t_drop_const_uc_ptr;
typedef union u_drop_const_c_ptr
{
	t_i8		*cast;
	const t_i8	*c_cast;
}	t_drop_const_c_ptr;

#endif

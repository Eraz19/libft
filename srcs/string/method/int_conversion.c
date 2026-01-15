/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_conversion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:18:08 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/12 14:13:20 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * c_isspace - Checks if a character is a whitespace character
 *
 * @param c The character to check
 * @return TRUE if whitespace, FALSE otherwise
 */
static t_bool	c_isspace(t_i8 c)
{
	if ((c >= '\t' && c <= '\r') || c == ' ')
		return (TRUE);
	else
		return (FALSE);
}

/**
 * str_to_int - Converts a string to an integer
 *
 * @param nptr The t_cstr containing the numeric string
 * @param base The character set representing the base
 *	rules for base:
 *	- No whitespace characters
 *	- No '+' or '-' signs
 *	- All characters must be unique
 * @return The converted integer value
 *
 * NULL Handling: If nptr.s or base.s is NULL, returns 0.
 * Note: If base.len < 2, returns 0.
 */
t_i32	str_to_int(t_cstr nptr, t_cstr base)
{
	size_t	i;
	t_i32	res;
	t_i32	sign;
	ssize_t	index;

	1 && (i = 0, res = 0, sign = 1, index = 0);
	if (nptr.s == NULL || base.s == NULL || base.len < 2)
		return (0);
	while (i < nptr.len && c_isspace(nptr.s[i]))
		++i;
	if (i < nptr.len && (nptr.s[i] == '+' || nptr.s[i] == '-'))
	{
		if (nptr.s[i] == '-')
			sign = -1;
		++i;
	}
	while (i < nptr.len && index != -1)
	{
		index = str_findindex(base, nptr.s[i]);
		if (index != -1)
			1 && (res = (res * (t_i32)base.len) + (t_i32)index, ++i);
	}
	return (sign * res);
}

/**
 * str_from_uint_ - Converts an unsigned integer to a string in a given base
 *
 * @param n The unsigned integer value
 * @param base The character set representing the base
 * @param buf The pointer to the buffer to write to
 * @return The updated buffer after conversion
 *
 * Error: If allocation fails during, returns NULL dbuf (errno ENOMEM).
 */
static t_dbuf	str_from_uint_(t_u32 n, t_cstr base, t_dbuf buf)
{
	while (n != 0)
	{
		buf = buf_insertc(buf, cbuf(&base.s[n % base.len], 1), 0, E_);
		if (buf.data == NULL)
			return (buf);
		n /= base.len;
	}
	return (buf);
}

/**
 * str_from_int_ - Converts a signed integer to a string in a given base
 *
 * @param n The signed integer value
 * @param base The character set representing the base
 * @param buf The pointer to the buffer to write to
 * @return The updated buffer after conversion
 *
 * Error: If allocation fails during, returns NULL dbuf (errno ENOMEM).
 */
static t_dbuf	str_from_int_(t_i32 n, t_cstr base, t_dbuf buf)
{
	t_u32	abs_n;
	t_bool	is_neg;

	1 && (is_neg = FALSE, abs_n = (t_u32)(abs_i(n)));
	if (n < 0)
		is_neg = TRUE;
	while (abs_n != 0)
	{
		buf = buf_insertc(buf, cbuf(&base.s[abs_n % base.len], 1), 0, E_);
		if (buf.data == NULL)
			return (buf);
		abs_n /= base.len;
	}
	if (is_neg)
		buf = buf_insertc(buf, cbuf("-", 1), 0, E_);
	return (buf);
}

/**
 * str_from_int - Converts an integer to a string in a specified base
 *
 * @param n The integer value to convert
 * @param base The character set representing the base
 * @param sign Whether to treat n as signed (TRUE) or unsigned (FALSE)
 * @return A new t_dstr containing the string representation
 *
 * NULL Handling: If base.s is NULL, returns a NULL t_dstr.
 * Note: If base.len < 2, returns a NULL t_dstr.
 * Error: If allocation fails, returns a NULL t_dstr (errno ENOMEM).
 */
t_dstr	str_from_int(t_i32 n, t_cstr base, t_bool sign)
{
	t_dstr	res;
	t_dbuf	buf;

	if (base.s == NULL || base.len < 2)
		return (dstr_s(0));
	if (n == 0)
		return (str_from_char(base.s[0]));
	buf = dbuf_s(I32_BUFFER);
	if (buf.data == NULL)
		return (dstr_s(0));
	if (sign == FALSE)
		buf = str_from_uint_((t_u32)n, base, buf);
	else
		buf = str_from_int_(n, base, buf);
	if (buf.data == NULL)
		return (dstr_s(0));
	res = str_from_buf(&buf);
	free_dbuf(&buf);
	return (res);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_conversion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:18:08 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/21 15:32:10 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math.h"
#include "libft_char.h"
#include "libft_string.h"

/**
 * is_overflow - Checks if adding a digit causes overflow for int
 *
 * @param current The current integer value
 * @param digit The next digit to add
 * @param base The base of the number system
 * @param sign The sign of the number (1 for positive, -1 for negative)
 * @return TRUE if overflow would occur, FALSE otherwise
 */
static t_bool	is_overflow(t_i32 current, t_i32 digit, t_i32 base, t_i32 sign)
{
	if (sign == 1)
	{
		if (current > (INT_MAX - digit) / base)
			return (TRUE);
	}
	else
	{
		if (current < (INT_MIN + digit) / base)
			return (TRUE);
	}
	return (FALSE);
}

/**
 * str_to_int - Converts a string to an integer
 *
 * @param res Pointer to store the result converted integer value
 * @param nptr The t_cstr containing the numeric string
 * @param base The character set representing the base
 *     rules for base:
 *         - No whitespace characters
 *         - No '+' or '-' signs
 *         - All characters must be unique
 * @return TRUE on success, FALSE on overflow or error
 *
 * @args: If nptr.s or base.s is NULL, returns FALSE.
 *        If base.len < 2, returns FALSE.
 */
t_bool	str_to_int(t_i32 *res, t_cstr nptr, t_cstr base)
{
	size_t	i;
	t_i32	sign;
	ssize_t	base_i;

	if (nptr.s == NULL || base.s == NULL || base.len < 2)
		return (FALSE);
	1 && (i = 0, *res = 0, sign = 1, base_i = 0);
	while (i < nptr.len && c_isspace(nptr.s[i]))
		++i;
	if (i < nptr.len && nptr.s[i] == '-')
		1 && (sign = -1, ++i);
	else if (i < nptr.len && nptr.s[i] == '+')
		++i;
	while (i < nptr.len && base_i != -1)
	{
		base_i = str_findindex(base, nptr.s[i]);
		if (base_i != -1)
		{
			if (is_overflow(*res, (t_i32)base_i, (t_i32)base.len, sign) == TRUE)
				return (FALSE);
			1 && (*res = (*res * (t_i32)base.len) + (t_i32)base_i, ++i);
		}
	}
	return (*res *= sign, TRUE);
}

/**
 * str_from_uint_ - Converts an unsigned integer to a string in a given base
 *
 * @param n The unsigned integer value
 * @param base The character set representing the base
 * @param buf The buffer to write to
 * @return The updated buffer after conversion
 *
 * @error: If allocation fails during, returns NULL dbuf (errno ENOMEM).
 */
static t_dbuf	str_from_uint_(t_u32 n, t_cstr base, t_dbuf buf)
{
	while (n != 0)
	{
		buf = buf_insertc(&buf, cbuf(&base.s[n % base.len], 1), 0, E);
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
 * @param buf The buffer to write to
 * @return The updated buffer after conversion
 *
 * @error: If allocation fails during, returns NULL dbuf (errno ENOMEM).
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
		buf = buf_insertc(&buf, cbuf(&base.s[abs_n % base.len], 1), 0, E);
		if (buf.data == NULL)
			return (buf);
		abs_n /= base.len;
	}
	if (is_neg)
		buf = buf_insertc(&buf, cbuf("-", 1), 0, E);
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
 * @args: If base.s is NULL, returns a NULL t_dstr.
 *        If base.len < 2, returns a NULL t_dstr.
 * @error: If allocation fails, returns a NULL t_dstr (errno ENOMEM).
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
	return (res);
}

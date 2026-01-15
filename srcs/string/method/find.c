/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:11:13 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/09 12:46:16 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * str_findchr - Locates the first occurrence of a character in a string
 *
 * @param str The t_cstr structure to search
 * @param c The character to locate
 * @return A t_cstr starting at the first occurrence, or NULL t_cstr
 *
 * NULL Handling: If str.s is NULL, returns NULL t_cstr.
 */
t_cstr	str_findchr(t_cstr str, t_i32 c)
{
	size_t	i;

	i = 0;
	if (str.s == NULL)
		return (cstr(NULL));
	while (i < str.len)
	{
		if (str.s[i] == (t_u8)c)
			return (str_shift(str, i));
		++i;
	}
	return (cstr(NULL));
}

/**
 * str_findlastchr - Locates the last occurrence of a character in a string
 *
 * @param str The t_cstr structure to search
 * @param c The character to locate
 * @return A t_cstr starting at the last occurrence, or NULL t_cstr
 *
 * NULL Handling: If str.s is NULL, returns NULL t_cstr
 */
t_cstr	str_findlastchr(t_cstr str, t_i32 c)
{
	size_t	i;

	i = 0;
	if (str.s == NULL)
		return (cstr(NULL));
	while (i < str.len + 1)
	{
		if (str.s[(str.len - i)] == (t_u8)c)
			return (str_shift(str, str.len - i));
		++i;
	}
	return (cstr(NULL));
}

/**
 * str_findindex - Locates the first occurrence of a character in a string
 *
 * @param str The string to search
 * @param c The character to locate
 * @return The index of the first occurrence, or -1
 *
 * NULL Handling: If str.s is NULL, returns -1.
 */
ssize_t	str_findindex(t_cstr str, t_i8 c)
{
	size_t	i;

	i = 0;
	if (str.s == NULL)
		return (-1);
	while (i < str.len)
	{
		if (str.s[i] == c)
			return ((ssize_t)i);
		++i;
	}
	return (-1);
}

/**
 * str_findlastindex - Locates the last occurrence of a character in a string
 *
 * @param str The string to search
 * @param c The character to locate
 * @return The index of the last occurrence, or -1
 *
 * NULL Handling: If str.s is NULL, returns -1.
 */
ssize_t	str_findlastindex(t_cstr str, t_i8 c)
{
	size_t	i;

	if (str.s == NULL)
		return (-1);
	i = str.len - 1;
	while (i > 0)
	{
		if (str.s[i] == c)
			return ((ssize_t)i);
		--i;
	}
	if (str.s[0] == c)
		return (0);
	return (-1);
}

/**
 * str_findsub - Locates a substring in a string
 *
 * @param str The t_cstr to search in
 * @param sub The t_cstr to search for
 * @return A t_cstr starting at the first occurrence, or NULL t_cstr
 * 
 * NULL Handling: If str.s is NULL, returns NULL t_cstr.
 *                If sub.s is NULL, returns cstr at beginning of str.
 */
t_cstr	str_findsub(t_cstr str, t_cstr sub)
{
	size_t	i;
	size_t	m_i;

	i = 0;
	if (str.s == NULL)
		return (cstr(NULL));
	if (sub.s == NULL)
		return (str);
	while (i < str.len)
	{
		m_i = 0;
		while (m_i < sub.len && i + m_i < str.len && str.s[i + m_i] == sub.s[m_i])
			++m_i;
		if (m_i == sub.len)
			return (str_shift(str, i));
		++i;
	}
	return (cstr(NULL));
}

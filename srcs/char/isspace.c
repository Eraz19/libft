/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isspace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 12:41:35 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/21 15:57:30 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_types.h"

/**
 * c_isspace - Checks if a character is a whitespace character
 *
 * @param c The character to check
 * @return TRUE if whitespace, FALSE otherwise
 *
 * INFO: Whitespace characters are: space, tab, newline, vertical tab,
 */
t_bool	c_isspace(t_i32 c)
{
	if ((c >= '\t' && c <= '\r') || c == ' ')
		return (TRUE);
	else
		return (FALSE);
}

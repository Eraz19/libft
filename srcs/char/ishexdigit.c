/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ishexdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 20:01:12 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/21 20:02:54 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_char.h"

/**
 * c_ishexdigit - Checks if a character is a hexadecimal digit
 *
 * @param c The character to check
 * @return TRUE if hexadecimal digit (0-9, A-F, a-f), FALSE otherwise
 */
t_bool	c_ishexdigit(t_i32 c)
{
	if (c_isdigit(c) || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f'))
		return (TRUE);
	return (FALSE);
}

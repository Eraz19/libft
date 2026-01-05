/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isprint.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 15:16:41 by adouieb           #+#    #+#             */
/*   Updated: 2025/12/28 16:19:21 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * c_isprint - Checks if a character is printable
 *
 * @param c The character to check
 * @return TRUE if printable, FALSE otherwise
 */
t_bool	c_isprint(t_i32 c)
{
	if (c >= ' ' && c <= '~')
		return (TRUE);
	else
		return (FALSE);
}

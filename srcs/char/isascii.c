/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isascii.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 15:16:15 by adouieb           #+#    #+#             */
/*   Updated: 2025/12/28 16:20:23 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * c_isascii - Checks if a character is a valid ASCII character
 *
 * @param c The character to check
 * @return TRUE if ASCII (0-127), FALSE otherwise
 */
t_bool	c_isascii(t_i32 c)
{
	if (c >= 0 && c <= 127)
		return (TRUE);
	else
		return (FALSE);
}

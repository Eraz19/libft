/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isdigit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 15:15:47 by adouieb           #+#    #+#             */
/*   Updated: 2025/12/28 16:19:51 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * c_isdigit - Checks if a character is a digit
 *
 * @param c The character to check
 * @return TRUE if digit (0-9), FALSE otherwise
 */
t_bool	c_isdigit(t_i32 c)
{
	if (c >= '0' && c <= '9')
		return (TRUE);
	else
		return (FALSE);
}

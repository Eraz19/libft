/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isuppercase.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 20:04:02 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/21 20:05:10 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_types.h"

/**
 * c_isuppercase - Checks if a character is an uppercase letter
 *
 * @param c The character to check
 * @return TRUE if the character is uppercase, FALSE otherwise
 */
t_bool	c_isuppercase(t_i32 c)
{
	if (c >= 'A' && c <= 'Z')
		return (TRUE);
	return (FALSE);
}

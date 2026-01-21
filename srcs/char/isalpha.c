/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isalpha.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 15:14:23 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/21 15:56:46 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_types.h"

/**
 * c_isalpha - Checks if a character is alphabetic
 *
 * @param c The character to check
 * @return TRUE if alphabetic, FALSE otherwise
 */
t_bool	c_isalpha(t_i32 c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (TRUE);
	else
		return (FALSE);
}

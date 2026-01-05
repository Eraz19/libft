/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toupper.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:00:33 by adouieb           #+#    #+#             */
/*   Updated: 2025/12/28 16:18:14 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * c_toupper - Converts a lowercase letter to uppercase
 *
 * @param c The character to convert
 * @return The uppercase equivalent, or the character unchanged if no lowercase
 */
t_i32	c_toupper(t_i32 c)
{
	if (c >= 'a' && c <= 'z')
		return (c - ('a' - 'A'));
	else
		return (c);
}

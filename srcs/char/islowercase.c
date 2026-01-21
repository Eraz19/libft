/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   islowercase.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 20:04:56 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/21 20:05:41 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_types.h"

/**
 * c_islowercase - Checks if a character is a lowercase letter
 *
 * @param c The character to check
 * @return TRUE if the character is lowercase, FALSE otherwise
 */
t_bool	c_islowercase(t_i32 c)
{
	return (c >= 'a' && c <= 'z');
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tolower.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:01:21 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/21 15:57:39 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_types.h"

/**
 * c_tolower - Converts an uppercase letter to lowercase
 *
 * @param c The character to convert
 * @return The lowercase equivalent, or the character unchanged if no uppercase
 */
t_i32	c_tolower(t_i32 c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + ('a' - 'A'));
	else
		return (c);
}

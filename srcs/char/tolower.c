/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tolower.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:01:21 by adouieb           #+#    #+#             */
/*   Updated: 2025/12/28 16:18:40 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isalnum.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 15:15:33 by adouieb           #+#    #+#             */
/*   Updated: 2025/12/28 16:21:03 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * c_isalnum - Checks if a character is alphanumeric
 *
 * @param c The character to check
 * @return TRUE if alphanumeric, FALSE otherwise
 */
t_bool	c_isalnum(t_i32 c)
{
	if (c_isalpha(c) || c_isdigit(c))
		return (TRUE);
	else
		return (FALSE);
}

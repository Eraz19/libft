/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 15:01:29 by adouieb           #+#    #+#             */
/*   Updated: 2025/12/29 15:07:04 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * str_print - Outputs the string to the given file descriptor
 *
 * @param str The t_cst containing the string to output
 * @param fd  The file descriptor to write to
 */
void	str_print(t_cstr str, t_i32 fd)
{
	if (str.s == NULL)
		write(fd, "null", 4);
	else
		write(fd, str.s, str.len);
}

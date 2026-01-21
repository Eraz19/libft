/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 15:01:29 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/21 15:28:16 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_string.h"

/**
 * str_print - Outputs the string to the given file descriptor
 *
 * @param str The t_cstr containing the string to output
 * @param fd  The file descriptor to write to
 * @return void
 *
 * @args: If str.s is NULL, writes "null" to the file descriptor.
 */
void	str_print(t_cstr str, t_i32 fd)
{
	if (str.s == NULL)
		write(fd, "null", 4);
	else
		write(fd, str.s, str.len);
}

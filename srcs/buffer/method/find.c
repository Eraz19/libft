/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 10:59:22 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/20 12:41:20 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * buf_findindex - Locates the first occurrence of bytes in a buffer
 *
 * WARNING: The buffer to search in will be searched jumping bytes.size to
 *				bytes.size, this imply that the index don't directly correspond
 *				to the location of the searched bytes, the real index will be:
 *
 *					real_index = found_index * bytes.size
 *
 * @param buf The buffer to search
 * @param bytes The bytes to locate
 * @return The index of the first occurrence, or -1
 *
 * NULL Handling: If buf.data or bytes.data is NULL, returns -1.
 */
ssize_t	buf_findindex(t_cbuf buf, t_cbuf bytes)
{
	size_t	i;

	if (buf.data == NULL || bytes.data == NULL)
		return (-1);
	i = 0;
	while (i + bytes.size <= buf.size)
	{
		if (buf_cmp(cbuf(buf.data + i, bytes.size), bytes) == 0)
			return ((ssize_t)i / (ssize_t)bytes.size);
		i += bytes.size;
	}
	return (-1);
}

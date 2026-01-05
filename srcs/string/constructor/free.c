/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 16:32:27 by adouieb           #+#    #+#             */
/*   Updated: 2025/12/30 19:07:36 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * free_dstrs - Frees an array of dynamic string structures
 *
 * @param str_buf The pointer to t_dbuf containing an array of t_dstr to free
 */
void	free_dstrs(t_dbuf *str_buf)
{
	size_t	i;

	i = 0;
	while (i < str_buf->len / sizeof(t_dstr))
		free_dstr(&((t_dstr *)str_buf->data)[i++]);
	free_dbuf(str_buf);
}

/**
 * free_dstr - Frees a dynamic string structure and clears its memory
 *
 * @param str Pointer to the t_dstr to free
 */
void	free_dstr(t_dstr *str)
{
	size_t	i;

	if (str->s != NULL)
	{
		i = 0;
		while (i < str->size)
			str->s[i++] = 0;
		free(str->s);
		str->len = 0;
		str->size = 0;
		str->s = NULL;
	}
}

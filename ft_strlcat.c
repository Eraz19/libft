/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 15:57:49 by adouieb           #+#    #+#             */
/*   Updated: 2025/11/10 19:18:39 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

size_t  ft_strlcat(char *dst, const char *src, size_t dsize)
{
    size_t  i;
    size_t  d_len;

    i = 0;
    d_len = ft_strlen(dst);
    while (src[i] != '\0' && i < (d_len + dsize) - 1)
    {
        dst[d_len + i] = src[i];
        ++i;   
    }
    dst[d_len + i] = '\0';
    return (d_len + ft_strlen(src));
}

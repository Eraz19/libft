/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 15:28:16 by adouieb           #+#    #+#             */
/*   Updated: 2025/11/10 20:41:04 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

size_t  ft_strlcpy(char *dst, const char *src, size_t dsize)
{
    size_t  i;

    i = 0;
    while (src[i] != '\0' && i < dsize - 1)
    {
        dst[i] = src[i];
        ++i;
    }
    dst[i] = '\0';
    return (ft_strlen(src));
}

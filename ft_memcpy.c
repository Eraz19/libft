/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 15:25:52 by adouieb           #+#    #+#             */
/*   Updated: 2025/11/09 18:57:46 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void    *ft_memcpy(void *dest, const void *src, size_t n)
{
    size_t              i;
    unsigned char       *dest_cast;
    const unsigned char *src_cast;

    i = 0;
    dest_cast = (unsigned char *)dest;
    src_cast = (const unsigned char *)src;
    while (i < n)
    {
        dest_cast[i] = src_cast[i];
        ++i;
    }
    return (dest);
}

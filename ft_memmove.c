/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 15:26:55 by adouieb           #+#    #+#             */
/*   Updated: 2025/11/10 13:51:22 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

static void ft_movef(unsigned char *dest, const unsigned char *src, size_t n)
{
    size_t  i;

    i = 0;
    while (i < n)
    {
        dest[i] = src[i];
        ++i;
    }
}

static void ft_moveb(unsigned char *dest, const unsigned char *src, size_t n)
{
    size_t  i;

    i = n - 1;
    while(i >= 0)
    {
        dest[i] = src[i];
        --i;            
    }
}

void    *ft_memmove(void *dest, const void *src, size_t n)
{
    unsigned char       *dest_cast;
    const unsigned char *src_cast;

    dest_cast = (unsigned char *)dest;
    src_cast = (const unsigned char *)src;
    if (dest_cast <= src_cast)
        ft_movef(dest_cast, src_cast, n);
    else
        ft_moveb(dest_cast, src_cast, n);
    return (dest);
}

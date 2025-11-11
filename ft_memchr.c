/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:07:41 by adouieb           #+#    #+#             */
/*   Updated: 2025/11/10 19:20:53 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void    *ft_memchr(const void *s, int c, size_t n)
{
    size_t  i;
    union 
    {
        const unsigned char  *cs_cast;
        unsigned char        *s_cast;
    }   u;

    i = 0;
    u.cs_cast = (const unsigned char *)s;
    while (i < n)
    {
        if (u.cs_cast[i] == (unsigned char)c)
            return ((void *)(u.s_cast + i));
        ++i;
    }
    return (NULL);
}

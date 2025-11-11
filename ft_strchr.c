/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:02:42 by adouieb           #+#    #+#             */
/*   Updated: 2025/11/10 19:22:03 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

char    *ft_strchr(const char *s, int c)
{
    size_t  i;
    size_t  s_len;
    union
    {
        const unsigned char  *cs_cast;
        unsigned char        *s_cast;
    }   u;

    i = 0;
    s_len = ft_strlen(s);
    u.cs_cast = (const unsigned char *)s;
    while (i <= s_len)
    {
        if (u.cs_cast[i] == (unsigned char)c)
            return ((char *)u.s_cast + i);
        ++i;
    }
    return (NULL);
}

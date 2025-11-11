/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:03:00 by adouieb           #+#    #+#             */
/*   Updated: 2025/11/10 19:25:23 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

char    *ft_strrchr(const char *s, int c)
{
    size_t  i;
    union
    {
        const unsigned char  *cs_cast;
        unsigned char        *s_cast;
    }   u;

    i = ft_strlen(s);
    u.cs_cast = (const unsigned char *)s;
    while (i >= 0)
    {
        if (u.cs_cast[i] == (unsigned char)c)
            return ((char *)u.s_cast + i);
        --i;
    }
    return (NULL);
}

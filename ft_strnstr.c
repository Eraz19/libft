/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:11:13 by adouieb           #+#    #+#             */
/*   Updated: 2025/11/10 19:23:52 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char    *ft_strnstr(const char *big, const char *little, size_t len)
{
    size_t  i;
    size_t  match_i;
    union
    {
        const unsigned char  *cs_cast;
        unsigned char        *s_cast;
    }   u;

    u.cs_cast = (const unsigned char *)big;
    if (little[0] == '\0')
        return ((char *)u.s_cast);
    i = 0;
    while (u.cs_cast[i] != '\0' && i < len)
    {
        match_i = 0;
        while (little[match_i] != '\0' && 
            i + match_i < len &&
            u.cs_cast[i + match_i] == little[match_i])
            ++match_i;
        if (little[match_i] == '\0')
            return ((char *)u.s_cast + i);
        ++i;
    }
    return (NULL);
}

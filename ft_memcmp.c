/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 15:52:17 by adouieb           #+#    #+#             */
/*   Updated: 2025/11/10 19:21:02 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int ft_memcmp(const void *s1, const void *s2, size_t n)
{
    size_t              i;
    const unsigned char *s1_cast;
    const unsigned char *s2_cast;

    i = 0;
    s1_cast = (const unsigned char *)s1;
    s2_cast = (const unsigned char *)s2;
    while (i < n)
    {
        if (s1_cast[i] != s2_cast[i])
            return (s1_cast[i] - s2_cast[i]);
        ++i;
    }
    return (0);
}

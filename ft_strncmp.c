/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:04:38 by adouieb           #+#    #+#             */
/*   Updated: 2025/11/10 19:12:51 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int ft_strncmp(const char *s1, const char *s2, size_t n)
{
    size_t              i;
    const unsigned char *s1_cast;
    const unsigned char *s2_cast;

    i = 0;
    s1_cast = (const unsigned char *)s1;
    s2_cast = (const unsigned char *)s2;
    while ((s1_cast[i] != '\0' || s2_cast[i] != '\0') && i < n)
    {
        if (s1_cast[i] != s2_cast[i])
            return (s1_cast[i] - s2_cast[i]);
        ++i;
    }
    return (s1_cast[i] - s2_cast[i]);
}

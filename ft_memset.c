/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 15:25:14 by adouieb           #+#    #+#             */
/*   Updated: 2025/11/09 18:59:09 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void    *ft_memset(void *s, int c, size_t n)
{
    size_t          i;
    unsigned char   *s_cast;

    i = 0;
    s_cast = (unsigned char *)s;
    while (i < n)
        s_cast[i++] = (unsigned char)c;
    return (s);
}

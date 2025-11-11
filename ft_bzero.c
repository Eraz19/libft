/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 15:18:52 by adouieb           #+#    #+#             */
/*   Updated: 2025/11/09 18:54:16 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void    ft_bzero(void *s, size_t n)
{
    size_t          i;
    unsigned char * s_cast;

    i = 0;
    s_cast = (unsigned char *)s;
    while (i < n)
        s_cast[i++] = (unsigned char)0;
}

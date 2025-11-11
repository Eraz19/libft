/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:19:39 by adouieb           #+#    #+#             */
/*   Updated: 2025/11/10 20:36:38 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stddef.h>

char    *ft_itoa(int n)
{
    size_t          i;
    size_t          result_size;
    int             nbr;
    char            *result;
    unsigned char   temp[10];

    nbr = n;
    i = 9;
    while (nbr != 0)
    {
        temp[i--] = ((unsigned char)(n % 10)) + '0';
        nbr /= 10;
    }
    if (n < 0)
        result_size = (9 - i) + 2;
    else
        result_size = (9 - i) + 1;
    result = malloc(sizeof(unsigned char) * (result_size));
    if (result == NULL)
        return (NULL);
    return ((char *)ft_memcpy(result, temp + (i + 1), 9 - i));
}

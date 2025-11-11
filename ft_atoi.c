/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 15:17:22 by adouieb           #+#    #+#             */
/*   Updated: 2025/11/11 21:38:40 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

static int  ft_isspace(char c)
{
    if ((c >= '\t' && c <= '\r') || c == ' ')
        return (1);
    else
        return (0);
}

int ft_atoi(const char *nptr)
{
    int             sign;
    int             result;
    size_t          i;
    
    sign = 1;
    result = 0;
    i = 0;
    while (nptr[i] != '\0' && ft_isspace(nptr[i]))
        ++i;
    if (nptr[i] != '\0' && (nptr[i] == '+' || nptr[i] == '-'))
    {
        if (nptr[i] == '-')
            sign = -1;
        ++i;
    }
    while (nptr[i] != '\0' && (nptr[i] >= '0' && nptr[i] <= '9'))
    {
        result = (result * 10) + (nptr[i] - '0');
        ++i;
    }
    return (sign * result);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 15:51:35 by adouieb           #+#    #+#             */
/*   Updated: 2025/11/10 19:38:23 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <errno.h>

void    *ft_calloc(size_t nmemb, size_t size)
{
    void    *result;

    if (nmemb > (SIZE_MAX / size))
    {
        errno = ENOMEM;
        return (NULL);
    }
    result = malloc(nmemb * size);
    if (result == NULL)
    {
        errno = ENOMEM;
        return (NULL);
    }
    ft_bzero(result, nmemb * size);
    return (result);
}

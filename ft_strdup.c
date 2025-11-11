/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:15:30 by adouieb           #+#    #+#             */
/*   Updated: 2025/11/10 20:55:00 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>
#include <stdlib.h>
#include <errno.h>

char    *ft_strdup(const char *s)
{
    size_t  s_len;
    char    *result;
    union
    {
        const char  *cs;
        char        *s;
    }   u;
    
    u.cs = s;
    s_len = ft_strlen(u.cs);
    result = malloc(sizeof(char) * (s_len + 1));
    if (result == NULL)
    {
        errno = ENOMEM;
        return (NULL);
    }
    ft_strlcpy(result, s, s_len + 1);
    return (result);
}

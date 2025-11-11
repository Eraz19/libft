/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:16:25 by adouieb           #+#    #+#             */
/*   Updated: 2025/11/10 20:55:20 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>
#include <stdlib.h>
#include <errno.h>

char    *ft_substr(char const *s, unsigned int start, size_t len)
{
    size_t  s_len;
    size_t  substr_len;
    char    *result;
    
    s_len = ft_strlen(s);
    if (start + len < s_len)
        substr_len = start + len;
    else
        substr_len = s_len - start;
    result = malloc(sizeof(char) * (substr_len + 1));
    if (result == NULL)
    {
        errno = ENOMEM;
        return (NULL);
    }
    ft_strlcpy(result, s + start, substr_len + 1);
    return (result);
}

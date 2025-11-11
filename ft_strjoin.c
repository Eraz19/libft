/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:17:17 by adouieb           #+#    #+#             */
/*   Updated: 2025/11/10 20:56:46 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>
#include <stdlib.h>
#include <errno.h>

char    *ft_strjoin(char const *s1, char const *s2)
{
    size_t  s1_len;
    size_t  s2_len;
    char    *result;

    s1_len = ft_strlen(s1);
    s2_len = ft_strlen(s2);
    result = malloc(sizeof(char) * (s1_len + s2_len + 1));
    if (result == NULL)
    {
        errno = ENOMEM;
        return (NULL);
    }
    ft_strlcpy(result, s1, s1_len + s2_len + 1);
    ft_strlcat(result, s2, s1_len + s2_len + 1);
    return (result);
}

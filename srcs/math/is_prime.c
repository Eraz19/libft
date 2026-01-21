/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_prime.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 19:14:55 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/21 19:20:15 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_types.h"

/**
 * is_prime_i - Checks if an integer is a prime number
 *
 * @param nb The unsigned integer to check
 * @return TRUE if the number is prime, FALSE otherwise
 */
t_bool	is_prime_i(t_u32 nb)
{
	t_u32	i;

	if (nb <= 2)
		return (FALSE);
	i = 2;
	while (i <= nb / 2)
	{
		if (nb % i == 0)
			return (FALSE);
		++i;
	}
	return (TRUE);
}

/**
 * is_prime_l - Checks if a long integer is a prime number
 *
 * @param nb The unsigned long integer to check
 * @return TRUE if the number is prime, FALSE otherwise
 */
t_bool	is_prime_l(t_u64 nb)
{
	t_u64	i;

	if (nb <= 2)
		return (FALSE);
	i = 2;
	while (i <= nb / 2)
	{
		if (nb % i == 0)
			return (FALSE);
		++i;
	}
	return (TRUE);
}

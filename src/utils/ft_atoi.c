/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:04:51 by mickmart          #+#    #+#             */
/*   Updated: 2025/04/23 14:18:55 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

int	ft_atoi(const char *str, int *overflow)
{
	long long	total;
	int			neg;

	neg = 1;
	total = 0;
	while (*str && ((*str >= 9 && *str <= 13) || *str == ' '))
		str++;
	if (*str && (*str == '-' || *str == '+'))
	{
		if (*str == '-')
			neg = neg * (-1);
		str++;
	}
	while (*str && (*str >= '0' && *str <= '9'))
		total = total * 10 + (*str++ - '0');
	total *= neg;
	if (total > 2147483647 || total < -2147483648)
	{
		*overflow = 1;
		return (0);
	}
	return (total);
}

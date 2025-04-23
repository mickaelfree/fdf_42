/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:48:53 by mickmart          #+#    #+#             */
/*   Updated: 2025/04/20 17:37:45 by mickmart         ###   ########.fr       */
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
/*
int	main(void)
{
  printf("%d\n",ft_atoi("-8430749809837"));
  printf("%d\n",INT_MAX);
  printf("%d\n",INT_MIN);
}
 */

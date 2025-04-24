/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:07:53 by mickmart          #+#    #+#             */
/*   Updated: 2025/04/24 17:07:56 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*set;

	set = (unsigned char *)s;
	while (n--)
		*set++ = c;
	return (s);
}

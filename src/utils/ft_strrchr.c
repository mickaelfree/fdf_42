/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:05:27 by mickmart          #+#    #+#             */
/*   Updated: 2025/04/23 14:05:51 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*last_c;

	last_c = NULL;
	while (*s)
	{
		if (*s == (unsigned char)c)
			last_c = s;
		s++;
	}
	if ((unsigned char)c == '\0')
	{
		return ((char *)s);
	}
	return ((char *)last_c);
}

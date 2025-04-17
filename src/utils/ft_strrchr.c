/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 09:47:30 by mickmart          #+#    #+#             */
/*   Updated: 2025/04/16 22:10:58 by mickmart         ###   ########.fr       */
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

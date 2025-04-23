/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:18:05 by mickmart          #+#    #+#             */
/*   Updated: 2025/04/17 16:07:18 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t sz)
{
	const char	*s;
	size_t		len;

	s = src;
	while (*s)
		s++;
	len = s - src;
	if (!sz || !dst || !src)
		return (len);
	s = src;
	while (--sz && *s)
		*dst++ = *s++;
	*dst = '\0';
	return (len);
}

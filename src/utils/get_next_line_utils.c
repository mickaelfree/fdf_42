/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:36:15 by mickmart          #+#    #+#             */
/*   Updated: 2024/11/25 16:37:12 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/fdf.h"

char	*ft_free_secure(char *str)
{
	free(str);
	return (NULL);
}

char	*ft_add_str(char *dest, char *s1, char *s2, ssize_t end)
{
	ssize_t	i;
	ssize_t	j;

	i = 0;
	j = 0;
	while (s1 && s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	while (j <= end)
	{
		dest[i + j] = s2[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

size_t	ft_strlen(const char *str)
{
	const char	*start;

	if (!str)
		return (0);
	start = str;
	while (1)
	{
		if (!str[0])
			return (str - start);
		if (!str[1])
			return (str - start + 1);
		if (!str[2])
			return (str - start + 2);
		if (!str[3])
			return (str - start + 3);
		str += 4;
	}
}

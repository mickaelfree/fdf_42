/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:51:45 by mickmart          #+#    #+#             */
/*   Updated: 2025/04/12 03:08:15 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

static char	*ft_strljoin(char *s1, char *s2, ssize_t end)
{
	char	*dest;
	size_t	lentotal;

	if (end == -1)
		end = ft_strlen(s2) - 1;
	lentotal = ft_strlen(s1) + end + 2;
	dest = malloc(sizeof(char) * lentotal);
	if (!dest)
		return (ft_free_secure(s1));
	dest = ft_add_str(dest, s1, s2, end);
	free(s1);
	return (dest);
}

static ssize_t	ft_find_newline(char *str)
{
	char	*start;

	start = str;
	while (1)
	{
		if (!str[0])
			return (-1);
		if (str[0] == '\n')
			return (str - start);
		if (!str[1])
			return (-1);
		if (str[1] == '\n')
			return (str - start + 1);
		if (!str[2])
			return (-1);
		if (str[2] == '\n')
			return (str - start + 2);
		if (!str[3])
			return (-1);
		if (str[3] == '\n')
			return (str - start + 3);
		str += 4;
	}
}

static void	ft_pending_save(char *save, ssize_t find_nl)
{
	size_t	i;

	i = 0;
	if (find_nl != -1)
	{
		find_nl++;
		while (save[find_nl])
		{
			save[i] = save[find_nl];
			i++;
			find_nl++;
		}
	}
	save[i] = '\0';
}

void	ft_add_save(char *save, ssize_t *read_otc, int fd)
{
	*read_otc = read(fd, save, BUFFER_SIZE);
	save[*read_otc] = '\0';
}

char	*get_next_line(int fd)
{
	static char	save[BUFFER_SIZE + 1];
	char		*line;
	ssize_t		find_nl;
	ssize_t		read_otc;

	line = NULL;
	read_otc = 1;
	find_nl = -1;
	while (read_otc != 0 && find_nl == -1)
	{
		if (!*save)
			ft_add_save(save, &read_otc, fd);
		if (read_otc == -1)
			return (ft_free_secure(line));
		if (read_otc != 0)
		{
			find_nl = ft_find_newline(save);
			line = ft_strljoin(line, save, find_nl);
			ft_pending_save(save, find_nl);
		}
	}
	return (line);
}

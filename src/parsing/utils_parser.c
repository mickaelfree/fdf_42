/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 12:21:15 by mickmart          #+#    #+#             */
/*   Updated: 2025/04/24 19:08:43 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

void	get_height(char *filename, t_fdf *fdf, int oldfd)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		cleanup_exit(fdf, EXIT_FAILURE, "Cannot open file", oldfd);
	fdf->map->height = 0;
	line = get_next_line(fd);
	if (line == NULL)
	{
		close(fd);
		cleanup_exit(fdf, EXIT_FAILURE, "Cannot open file", oldfd);
	}
	while (line)
	{
		fdf->map->height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

void	get_width(char *filename, t_fdf *fdf, int oldfd)
{
	int		fd;
	char	*line;
	char	**split;

	fd = open(filename, O_RDONLY);
	fdf->map->width = 0;
	if (fd < 0)
		cleanup_exit(fdf, EXIT_FAILURE, "Cannot open file", oldfd);
	line = get_next_line(fd);
	split = ft_split(line, " \n");
	if (!split)
	{
		close(fd);
		free(line);
		cleanup_exit(fdf, EXIT_FAILURE, "split failed", oldfd);
	}
	while (split[fdf->map->width])
		fdf->map->width++;
	free(line);
	ft_free_split(split);
	close(fd);
}

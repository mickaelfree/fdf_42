/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:45:23 by mickmart          #+#    #+#             */
/*   Updated: 2025/04/24 19:44:37 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

static void	fill_points(t_map *map, char **split, int y, int *i)
{
	int	x;

	x = 0;
	while (split[x] && x < map->width)
	{
		map->points[y][x].x = x;
		map->points[y][x].y = y;
		map->points[y][x].z = ft_atoi(split[x], i);
		map->points[y][x].color = 0xFFFFFF;
		x++;
	}
}

static void	init_map_points(t_fdf *fdf, int fd)
{
	int	y;
	int	size;

	size = sizeof(t_point) * fdf->map->width;
	fdf->map->points = safe_malloc(sizeof(t_point *) * fdf->map->height, fdf,
			fd);
	ft_memset(fdf->map->points, 0, sizeof(t_point *) * fdf->map->height);
	y = 0;
	while (y < fdf->map->height)
	{
		fdf->map->points[y] = safe_malloc(size, fdf, fd);
		ft_memset(fdf->map->points[y], 0, size);
		y++;
	}
}

void	fill_matrice(char *line, t_fdf *fdf, int y, int fd)
{
	char	**split;
	int		overflow;

	overflow = 0;
	split = ft_split(line, " ");
	if (!split)
	{
		free(line);
		cleanup_exit(fdf, EXIT_FAILURE, "Invalid map dimensions", fd);
	}
	fill_points(fdf->map, split, y, &overflow);
	ft_free_split(split);
	free(line);
	if (overflow == 1)
		cleanup_exit(fdf, EXIT_FAILURE, "Overflow", fd);
}

void	parse_map(char *filename, t_fdf *fdf)
{
	int		fd;
	char	*line;
	int		y;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		cleanup_exit(fdf, EXIT_FAILURE, "Cannot open file", 0);
	get_height(filename, fdf, fd);
	get_width(filename, fdf, fd);
	if (!fdf->map->height || !fdf->map->width)
		cleanup_exit(fdf, EXIT_FAILURE, "Invalid map dimensions", fd);
	init_map_points(fdf, fd);
	y = 0;
	line = get_next_line(fd);
	if (!line)
		cleanup_exit(fdf, EXIT_FAILURE, "parsing failed", fd);
	while (line && y < fdf->map->height)
	{
		fill_matrice(line, fdf, y++, fd);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	close(fd);
}

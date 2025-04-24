/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 12:21:15 by mickmart          #+#    #+#             */
/*   Updated: 2025/04/24 15:11:48 by mickmart         ###   ########.fr       */
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

void	get_height(char *filename, t_fdf *fdf)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		cleanup_exit(fdf, EXIT_FAILURE, "Cannot open file",0);
	fdf->map->height = 0;
	line = get_next_line(fd);
	while (line)
	{
		fdf->map->height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

void	get_width(char *filename, t_fdf *fdf)
{
	int		fd;
	char	*line;
	char	**split;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		cleanup_exit(fdf, EXIT_FAILURE, "Cannot open file",0);
	line = get_next_line(fd);
	split = ft_split(line, " \n");
	if (!split)
		cleanup_exit(fdf, EXIT_FAILURE, "Invalid map dimensions",fd);
	fdf->map->width = 0;
	while (split[fdf->map->width])
		fdf->map->width++;
	free(line);
	ft_free_split(split);
	close(fd);
}

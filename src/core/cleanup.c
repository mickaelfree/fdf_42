/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:44:45 by mickmart          #+#    #+#             */
/*   Updated: 2025/04/24 18:59:20 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

static void	free_map(t_map *map)
{
	int	i;

	if (!map)
		return ;
	if (map->points)
	{
		i = 0;
		while (i < map->height)
		{
			if (map->points[i])
			{
				free(map->points[i]);
				map->points[i] = NULL; }
			i++;
		}
		free(map->points);
		map->points = NULL;
	}
	free(map);
}

static void	free_graphics(t_fdf *fdf)
{
	if (!fdf || !fdf->mlx)
		return ;
	if (fdf->img)
	{
		mlx_destroy_image(fdf->mlx, fdf->img);
		fdf->img = NULL;
		fdf->addr = NULL;
	}
	if (fdf->win)
	{
		mlx_destroy_window(fdf->mlx, fdf->win);
		fdf->win = NULL;
	}
	mlx_destroy_display(fdf->mlx);
	free(fdf->mlx);
	fdf->mlx = NULL;
}

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

void	cleanup(t_fdf *fdf)
{
	if (!fdf)
		return ;
	if (fdf->map)
        {
		free_map(fdf->map);
                fdf->map = NULL;
        }
	free_graphics(fdf);
	free(fdf);
}

void	cleanup_exit(t_fdf *fdf, int status, char *msg, int fd)
{
	if (fd > 2)
		close(fd);
	cleanup(fdf);
	if (status)
		ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	exit(status);
}

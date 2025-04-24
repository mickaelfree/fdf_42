/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:43:24 by mickmart          #+#    #+#             */
/*   Updated: 2025/04/24 19:45:25 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

static void	draw_line_setup(t_point p1, t_point p2, int *params)
{
	params[0] = ft_abs(p2.x - p1.x);
	params[1] = ft_abs(p2.y - p1.y);
	if (p1.x < p2.x)
		params[2] = 1;
	else
		params[2] = -1;
	if (p1.y < p2.y)
		params[3] = 1;
	else
		params[3] = -1;
	params[4] = params[0] - params[1];
}

void	draw_line(t_fdf *fdf, t_point p1, t_point p2)
{
	int	params[5];
	int	e2;

	draw_line_setup(p1, p2, params);
	while (1)
	{
		my_mlx_pixel_put(fdf, p1.x, p1.y, p1.color);
		if (p1.x == p2.x && p1.y == p2.y)
			break ;
		e2 = 2 * params[4];
		if (e2 > -params[1])
		{
			params[4] -= params[1];
			p1.x += params[2];
		}
		if (e2 < params[0])
		{
			params[4] += params[0];
			p1.y += params[3];
		}
	}
}

static void	draw_horizontal_line(t_fdf *fdf, int i, int j)
{
	t_point	current;
	t_point	next;

	current = fdf->map->points[i][j];
	apply_transformations(&current.x, &current.y, current.z, fdf->map);
	if (j < fdf->map->width - 1)
	{
		next = fdf->map->points[i][j + 1];
		apply_transformations(&next.x, &next.y, next.z, fdf->map);
		draw_line(fdf, current, next);
	}
}

static void	draw_vertical_line(t_fdf *fdf, int i, int j)
{
	t_point	current;
	t_point	next;

	current = fdf->map->points[i][j];
	apply_transformations(&current.x, &current.y, current.z, fdf->map);
	if (i < fdf->map->height - 1)
	{
		next = fdf->map->points[i + 1][j];
		apply_transformations(&next.x, &next.y, next.z, fdf->map);
		draw_line(fdf, current, next);
	}
}

void	draw(t_fdf *fdf)
{
	int	i;
	int	j;

	i = 0;
	while (i < fdf->map->height)
	{
		j = 0;
		while (j < fdf->map->width)
		{
			draw_horizontal_line(fdf, i, j);
			draw_vertical_line(fdf, i, j);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
}

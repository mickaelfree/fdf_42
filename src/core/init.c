/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:44:24 by mickmart          #+#    #+#             */
/*   Updated: 2025/04/24 19:41:50 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

t_fdf	*setmem_fdf(t_fdf *fdf)
{
	fdf = safe_malloc(sizeof(t_fdf), NULL, 0);
	ft_memset(fdf, 0, sizeof(t_fdf));
	fdf->map = safe_malloc(sizeof(t_map), fdf, 0);
	ft_memset(fdf->map, 0, sizeof(t_map));
	return (fdf);
}

t_fdf	*init_fdf(t_fdf *fdf)
{
	fdf->mlx = mlx_init();
	if (!fdf->mlx)
		cleanup_exit(fdf, EXIT_FAILURE, "MLX initialization failed", 0);
	fdf->win = mlx_new_window(fdf->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "FDF");
	if (!fdf->win)
		cleanup_exit(fdf, EXIT_FAILURE, "Window creation failed", 0);
	fdf->img = mlx_new_image(fdf->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!fdf->img)
		cleanup_exit(fdf, EXIT_FAILURE, "Image creation failed", 0);
	fdf->addr = mlx_get_data_addr(fdf->img, &fdf->bits_per_pixel,
			&fdf->line_length, &fdf->endian);
	if (!fdf->addr)
		cleanup_exit(fdf, EXIT_FAILURE, "Image address failed", 0);
	return (fdf);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:44:24 by mickmart          #+#    #+#             */
/*   Updated: 2025/04/17 16:03:04 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

t_fdf	*init_fdf(void)
{
	t_fdf	*fdf;

	fdf = safe_malloc(sizeof(t_fdf), NULL);
	fdf->mlx = mlx_init();
	if (!fdf->mlx)
		cleanup_exit(fdf, EXIT_FAILURE, "MLX initialization failed");
	fdf->win = mlx_new_window(fdf->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "FDF");
	if (!fdf->win)
		cleanup_exit(fdf, EXIT_FAILURE, "Window creation failed");
	fdf->img = mlx_new_image(fdf->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!fdf->img)
		cleanup_exit(fdf, EXIT_FAILURE, "Image creation failed");
	fdf->addr = mlx_get_data_addr(fdf->img, &fdf->bits_per_pixel,
			&fdf->line_length, &fdf->endian);
	if (!fdf->addr)
		cleanup_exit(fdf, EXIT_FAILURE, "Image address failed");
	fdf->map = NULL;
	return (fdf);
}

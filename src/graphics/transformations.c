/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:43:04 by mickmart          #+#    #+#             */
/*   Updated: 2025/04/13 20:45:49 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

void	apply_transformations(int *x, int *y, int z, t_map *map)
{
	int	temp_x;
	int	temp_y;
	int	scale;
	int	center_x;
	int	center_y;

	center_x = map->width >> 1;
	center_y = map->height >> 1;
	*x -= center_x;
	*y -= center_y;
	scale = WINDOW_WIDTH / (map->width + map->height);
	if ((WINDOW_HEIGHT / ((map->width + map->height) >> 1)) < scale)
		scale = WINDOW_HEIGHT / ((map->width + map->height) >> 1);
	temp_x = (*x - *y) * scale;
	temp_y = (*x + *y) * (scale / 2) - z * (scale / 3);
	*x = temp_x + (WINDOW_WIDTH >> 1);
	*y = temp_y + (WINDOW_HEIGHT >> 1);
}

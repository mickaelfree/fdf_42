/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 18:04:01 by mickmart          #+#    #+#             */
/*   Updated: 2025/01/24 18:04:04 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "mlx_linux/mlx.h"

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
  char *dst;

  dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel /8));
  *(unsigned int*)dst = color;
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	mlx = mlx_init();
    
    mlx_win = mlx_new_window(mlx,1000,1000,"micka");
	img.img = mlx_new_image(mlx, 1000, 1000);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);

  my_mlx_pixel_put(&img,5, 5, 0x00FF0000);
  mlx_put_image_to_window(mlx,  mlx_win, img.img, 0, 0);
  mlx_loop(mlx);
}

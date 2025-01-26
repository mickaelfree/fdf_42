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

typedef struct s_data {
  void *img;
  char *addr;
  int bits_per_pixel;
  int line_length;
  int endian;


}t_data;

int main(void)
{
  void *mlx;
  void *mlx_wind;
  mlx = mlx_init();
  mlx_wind = mlx_new_window(mlx,1000,1000,"mick");
  mlx_loop(mlx);
}

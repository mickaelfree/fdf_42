/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:45:08 by mickmart          #+#    #+#             */
/*   Updated: 2025/04/17 16:03:51 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

int	handle_close(t_fdf *fdf)
{
	cleanup_exit(fdf, EXIT_SUCCESS, "Window closed");
	return (0);
}

int	main(int argc, char **argv)
{
	t_fdf	*fdf;

	if (argc != 2)
		cleanup_exit(NULL, EXIT_FAILURE, "Usage ./fdf <filename>");
	if (!checker_map(argv[1]))
		cleanup_exit(NULL, EXIT_FAILURE, "Invalid map file");
	fdf = init_fdf();
	parse_map(argv[1], fdf);
	draw(fdf);
	mlx_key_hook(fdf->win, handle_key, fdf);
	mlx_hook(fdf->win, 17, 0, handle_close, fdf);
	mlx_loop(fdf->mlx);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:44:08 by mickmart          #+#    #+#             */
/*   Updated: 2025/04/24 15:45:49 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

int	handle_key(int keycode, t_fdf *fdf)
{
	if (keycode == XK_Escape)
		cleanup_exit(fdf, EXIT_SUCCESS, "Window closed",0);
	return (0);
}

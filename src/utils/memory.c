/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:46:00 by mickmart          #+#    #+#             */
/*   Updated: 2025/04/24 15:46:52 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

void	*safe_malloc(size_t size, t_fdf *fdf,int fd)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		cleanup_exit(fdf, EXIT_FAILURE, "Memory allocation failed",fd);
	return (ptr);
}

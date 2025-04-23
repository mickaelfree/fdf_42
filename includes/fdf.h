/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 19:13:17 by mickmart          #+#    #+#             */
/*   Updated: 2025/04/20 17:32:14 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# include "../lib/mlx/mlx.h"
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

# define WINDOW_WIDTH 3840
# define WINDOW_HEIGHT 2160

/* Structures */
typedef struct s_point
{
	int		x;
	int		y;
	int		z;
	int		color;
}			t_point;

typedef struct s_map
{
	int		height;
	int		width;
	t_point	**points;
}			t_map;

typedef struct s_fdf
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	t_map	*map;
}			t_fdf;

/* Core functions */
t_fdf		*init_fdf(void);

/* Parsing functions */

int			checker_map(char *filename);
void		ft_free_split(char **split);
void		get_width(char *filename, t_fdf *fdf);
void		get_height(char *filename, t_fdf *fdf);
void		parse_map(char *filename, t_fdf *fdf);

/* Graphics functions */
void		my_mlx_pixel_put(t_fdf *fdf, int x, int y, int color);
void		draw(t_fdf *fdf);
void		draw_line(t_fdf *fdf, t_point p1, t_point p2);
void		apply_transformations(int *x, int *y, int z, t_map *map);

/* Event handlers */
int			handle_key(int keycode, t_fdf *fdf);
int			handle_close(t_fdf *fdf);

/* Utils */
void		cleanup_exit(t_fdf *fdf, int status, char *msg);
void		*safe_malloc(size_t size, t_fdf *fdf);
size_t		ft_strlen(const char *s);
char		*ft_free_secure(char *ptr);
char		*ft_add_str(char *dest, char *s1, char *s2, ssize_t end);
char		*get_next_line(int fd);
int			ft_atoi(const char *str, int *overflow);
int			ft_ishexformat(char *hex);
int			pos_in_str(char *str, char c);
char		**ft_split(char const *s, char *c);
size_t		ft_strlcpy(char *dst, const char *src, size_t sz);
int			ft_isdigit(char c);
int			ft_isspace(char c);
int			ft_isnothexformat(char *hex);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strrchr(const char *s, int c);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaltsev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 17:27:28 by omaltsev          #+#    #+#             */
/*   Updated: 2019/03/23 17:27:30 by omaltsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHIC_H
# define GRAPHIC_H

# define WIN_HEIGHT 1000
# define WIN_WIDTH 1000

# define X_MASK 0

# define ANGLE 0.05

# define WHITE 0xFFFFFF

# define ESC 53

# include <mlx.h>
# include <math.h>
# include "libft.h"

typedef struct	s_rot
{
	int		f_x;
	int		f_y;
	int		f_z;
	double	an_x;
	double	an_y;
	double	an_z;
}				t_rot;

typedef struct	s_player
{
	char	*let;
	int		p_num;
}				t_player;

typedef struct	s_coord
{
	int		x;
	int		y;
	int		z;
	int		color;
}				t_coord;

typedef struct	s_img
{
	void		*mlx_ptr;
	void		*mlx_win;
	void		*ptr;
	char		*addr;
	int			bpp;
	int			size_line;
	int			endian;
}				t_img;

typedef struct	s_fdf
{
	t_img			*img;
	t_player		*p1;
	t_player		*p2;
	int				m_y;
	int				m_x;
	t_coord			**map;
	t_coord			**iso_map;
	t_coord			**ro_map;
	t_coord			**par_map;
	int				flag;
	t_rot			*rot;
}				t_fdf;

void			read_map(t_fdf *fdf, int fd);
void			make_picture(t_fdf *fdf, t_coord **map);
void			iso(int *x, int *y, int z);
void			select_map(t_fdf *fdf);
void			remake_map(t_fdf *fdf);
void			rot_elem(t_fdf *fdf, int x, int y, t_coord **map);
void			set_flags_angles(t_fdf *fdf, int f_x, int f_y, int f_z);
void			rotation(t_fdf *fdf);
void			zoom(t_fdf *fdf, int num);
void			ft_error(int n);
void			ft_make_par(t_fdf *fdf);
void			ft_make_iso(t_fdf *fdf);

int				valid_fir_part(char **str);
int				open_file(char *file);
int				read_color(char *str);
void			key_init(t_fdf *fdf);
char			*f1_strjoin(char *s1, char *s2);
int				ft_count_words(char *str, char c);
void			free_map(char **map);
void			move(t_fdf *fdf, int on_x, int on_y);
int				gradient_col(t_coord *current, t_coord *p0,
					t_coord *p1, t_coord *delta);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaltsev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 17:23:40 by omaltsev          #+#    #+#             */
/*   Updated: 2019/03/23 17:23:42 by omaltsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphic.h"

int		valid_fir_part(char **str)
{
	int		i;

	i = 0;
	if (**str == '-')
		(*str)++;
	while (ft_strchr("0123456789", **str) && **str)
	{
		(*str)++;
		i++;
	}
	if (i == 0)
		return (1);
	return (0);
}

t_img	*open_window(void)
{
	t_img	*img;

	img = ft_memalloc(sizeof(t_img));
	img->mlx_ptr = mlx_init();
	img->mlx_win = mlx_new_window(img->mlx_ptr, WIN_WIDTH, WIN_HEIGHT,
				"fdf");
	img->ptr = mlx_new_image(img->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	img->addr = mlx_get_data_addr(img->ptr, &img->bpp,
				&img->size_line, &img->endian);
	return (img);
}

void	ft_error(int n)
{
	if (n == 1)
		ft_putstr("usage: ./fdf [file_name.fdf]\n");
	else if (n == 2)
		ft_putstr("invalid map.\n");
	else if (n == 3)
		ft_putstr("open directory is invalid.\n");
	else if (n == 4)
		ft_putstr("invalid file.\n");
	exit(0);
}

void	zero_flags(t_fdf *fdf)
{
	fdf->rot = ft_memalloc(sizeof(t_rot));
	fdf->flag = 0;
	fdf->rot->f_x = 0;
	fdf->rot->f_y = 0;
	fdf->rot->f_z = 0;
}

int		main(int argc, char **argv)
{
	int			fd;
	t_fdf		*fdf;

	if (argc != 2 || !(ft_strstr(argv[1], ".fdf")))
		ft_error(1);
	fd = open_file(argv[1]);
	fdf = ft_memalloc(sizeof(t_fdf));
	zero_flags(fdf);
	fdf->img = open_window();
	key_init(fdf);
	read_map(fdf, fd);
	select_map(fdf);
	mlx_loop(fdf->img->mlx_ptr);
	return (0);
}

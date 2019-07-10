/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   picture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaltsev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 11:59:57 by omaltsev          #+#    #+#             */
/*   Updated: 2019/03/25 11:59:59 by omaltsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphic.h"

void	ft_put_pixel(int x, int y, t_fdf *fdf, int color)
{
	int		i;

	x += WIN_WIDTH / 2;
	y += WIN_HEIGHT / 2;
	if ((x >= 0 && x < WIN_WIDTH) && (y >= 0 && y < WIN_HEIGHT))
	{
		i = ((x * fdf->img->bpp / 8) + (y * fdf->img->size_line));
		fdf->img->addr[i] = color;
		fdf->img->addr[++i] = color >> 8;
		fdf->img->addr[++i] = color >> 16;
	}
}

void	brethen_line(t_coord p0, t_coord p1, t_fdf *fdf, t_coord start)
{
	t_coord delta;
	t_coord	sign;
	t_coord	error;

	delta.x = abs(p1.x - p0.x);
	delta.y = abs(p1.y - p0.y);
	sign.x = p0.x < p1.x ? 1 : -1;
	sign.y = p0.y < p1.y ? 1 : -1;
	error.x = delta.x - delta.y;
	while (p0.x != p1.x || p0.y != p1.y)
	{
		ft_put_pixel(p0.x, p0.y, fdf, gradient_col(&p0, &start, &p1, &delta));
		error.y = error.x * 2;
		if (error.y > -delta.y)
		{
			error.x -= delta.y;
			p0.x += sign.x;
		}
		if (error.y < delta.x)
		{
			error.x += delta.x;
			p0.y += sign.y;
		}
	}
}

void	make_picture(t_fdf *fdf, t_coord **map)
{
	int		*i;
	int		y;
	int		x;
	t_coord	start;

	i = (int *)fdf->img->addr;
	y = 0;
	while (y < fdf->m_y)
	{
		x = 0;
		while (x < fdf->m_x)
		{
			start.x = map[y][x].x;
			start.y = map[y][x].y;
			start.color = map[y][x].color;
			ft_put_pixel(map[y][x].x, map[y][x].y, fdf, map[y][x].color);
			if (x + 1 != fdf->m_x)
				brethen_line(map[y][x], map[y][x + 1], fdf, start);
			if (y + 1 != fdf->m_y)
				brethen_line(map[y][x], map[y + 1][x], fdf, start);
			x++;
		}
		y++;
	}
}

void	select_map(t_fdf *fdf)
{
	if (fdf->flag == 0)
		make_picture(fdf, fdf->map);
	else if (fdf->flag == 1)
		make_picture(fdf, fdf->iso_map);
	else if (fdf->flag == 2)
		make_picture(fdf, fdf->par_map);
	else
	{
		rotation(fdf);
		make_picture(fdf, fdf->ro_map);
	}
	mlx_put_image_to_window(fdf->img->mlx_ptr, fdf->img->mlx_win,
			fdf->img->ptr, 0, 0);
}

void	remake_map(t_fdf *fdf)
{
	mlx_destroy_image(fdf->img->mlx_ptr, fdf->img->ptr);
	fdf->img->ptr = mlx_new_image(fdf->img->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	fdf->img->addr = mlx_get_data_addr(fdf->img->ptr, &fdf->img->bpp,
				&fdf->img->size_line, &fdf->img->endian);
	select_map(fdf);
}

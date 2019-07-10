/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaltsev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 16:45:26 by omaltsev          #+#    #+#             */
/*   Updated: 2019/03/27 16:45:28 by omaltsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphic.h"

void		iso(int *x, int *y, int z)
{
	int		pre_x;
	int		pre_y;

	pre_x = *x;
	pre_y = *y;
	*x = (pre_x - pre_y) * cos(0.523599);
	*y = -z + (pre_x + pre_y) * sin(0.523599);
}

static void	calc_zoom(t_fdf *fdf, int num, int x, int y)
{
	int		zoom;

	zoom = 2;
	if (num > 0)
	{
		fdf->par_map[y][x].x *= zoom;
		fdf->par_map[y][x].y *= zoom;
	}
	else
	{
		fdf->par_map[y][x].x /= zoom;
		fdf->par_map[y][x].y /= zoom;
	}
}

void		zoom(t_fdf *fdf, int num)
{
	int		x;
	int		y;

	y = -1;
	if ((num == -1 && fdf->par_map[0][1].x / 2 - fdf->par_map[0][0].x / 2 <= 1)
	|| (num == 1 && fdf->par_map[0][1].x * 2 - fdf->par_map[0][0].x * 2 > 450))
		return ;
	while (++y < fdf->m_y)
	{
		x = -1;
		while (++x < fdf->m_x)
		{
			calc_zoom(fdf, num, x, y);
		}
	}
}

void		ft_make_par(t_fdf *fdf)
{
	int		x;
	int		y;

	fdf->rot->an_x = 5;
	y = -1;
	while (++y < fdf->m_y)
	{
		x = -1;
		while (++x < fdf->m_x)
		{
			rot_elem(fdf, x, y, fdf->par_map);
			fdf->par_map[y][x].color = fdf->map[y][x].color;
		}
	}
	fdf->rot->an_x = 0;
}

void		ft_make_iso(t_fdf *fdf)
{
	int		x;
	int		y;

	y = -1;
	while (++y < fdf->m_y)
	{
		x = -1;
		while (++x < fdf->m_x)
		{
			fdf->iso_map[y][x].x = fdf->map[y][x].x;
			fdf->iso_map[y][x].y = fdf->map[y][x].y;
			fdf->iso_map[y][x].z = fdf->map[y][x].z;
			fdf->iso_map[y][x].color = fdf->map[y][x].color;
			iso(&fdf->iso_map[y][x].x, &fdf->iso_map[y][x].y,
				fdf->iso_map[y][x].z);
			fdf->ro_map[y][x].x = fdf->map[y][x].x;
			fdf->ro_map[y][x].y = fdf->map[y][x].y;
			fdf->ro_map[y][x].z = fdf->map[y][x].z;
			fdf->ro_map[y][x].color = fdf->map[y][x].color;
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaltsev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 13:54:59 by omaltsev          #+#    #+#             */
/*   Updated: 2019/03/28 13:55:01 by omaltsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphic.h"

void		set_flags_angles(t_fdf *fdf, int f_x, int f_y, int f_z)
{
	fdf->rot->f_x = f_x;
	fdf->rot->f_y = f_y;
	fdf->rot->f_z = f_z;
	if (f_x != 0)
	{
		if (f_x == 1)
			fdf->rot->an_x += ANGLE;
		if (f_x == -1)
			fdf->rot->an_x -= ANGLE;
	}
	if (f_y != 0)
	{
		if (f_y == 1)
			fdf->rot->an_y += ANGLE;
		if (f_y == -1)
			fdf->rot->an_y -= ANGLE;
	}
	if (f_z != 0)
	{
		if (f_z == 1)
			fdf->rot->an_z += ANGLE;
		if (f_z == -1)
			fdf->rot->an_z -= ANGLE;
	}
}

void		rot_elem(t_fdf *fdf, int x, int y, t_coord **map)
{
	int		tm_x;
	int		tm_y;
	int		tm_z;

	map[y][x].x = fdf->map[y][x].x * cos(fdf->rot->an_z) +
						-fdf->map[y][x].y * sin(fdf->rot->an_z);
	map[y][x].y = fdf->map[y][x].x * sin(fdf->rot->an_z) +
						fdf->map[y][x].y * cos(fdf->rot->an_z);
	tm_x = map[y][x].x;
	tm_y = map[y][x].y;
	map[y][x].y = tm_y * cos(fdf->rot->an_x) +
						fdf->map[y][x].z * sin(fdf->rot->an_x);
	map[y][x].z = -tm_y * sin(fdf->rot->an_x) +
						fdf->map[y][x].z * cos(fdf->rot->an_x);
	tm_y = map[y][x].y;
	tm_z = map[y][x].z;
	map[y][x].x = tm_x * cos(fdf->rot->an_y) +
						tm_z * sin(fdf->rot->an_y);
	map[y][x].z = -tm_x * sin(fdf->rot->an_y) +
						tm_z * cos(fdf->rot->an_y);
}

void		rotation(t_fdf *fdf)
{
	int		x;
	int		y;

	y = -1;
	while (++y < fdf->m_y)
	{
		x = -1;
		while (++x < fdf->m_x)
		{
			rot_elem(fdf, x, y, fdf->ro_map);
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaltsev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 15:43:32 by omaltsev          #+#    #+#             */
/*   Updated: 2019/03/24 15:43:34 by omaltsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphic.h"

static int		end(void *param)
{
	(void)param;
	exit(0);
	return (0);
}

static void		keys_rotation(int keycode, t_fdf *fdf)
{
	if (keycode == 84 && (fdf->flag = 4))
		set_flags_angles(fdf, 1, 0, 0);
	if (keycode == 87 && (fdf->flag = 4))
		set_flags_angles(fdf, -1, 0, 0);
	if (keycode == 85 && (fdf->flag = 4))
		set_flags_angles(fdf, 0, 1, 0);
	if (keycode == 83 && (fdf->flag = 4))
		set_flags_angles(fdf, 0, -1, 0);
	if (keycode == 88 && (fdf->flag = 4))
		set_flags_angles(fdf, 0, 0, 1);
	if (keycode == 86 && (fdf->flag = 4))
		set_flags_angles(fdf, 0, 0, -1);
}

static void		keys_move(int keycode, t_fdf *fdf)
{
	fdf->flag = 1;
	if (keycode == 123)
		move(fdf, -1, 0);
	if (keycode == 124)
		move(fdf, 1, 0);
	if (keycode == 125)
		move(fdf, 0, 1);
	if (keycode == 126)
		move(fdf, 0, -1);
}

static int		select_key(int keycode, t_fdf *fdf)
{
	if (keycode == ESC)
	{
		exit(0);
	}
	if (keycode == 18)
		fdf->flag = 1;
	if (keycode == 29)
		fdf->flag = 0;
	if (keycode == 19)
		fdf->flag = 2;
	if (keycode >= 83 && keycode <= 88)
		keys_rotation(keycode, fdf);
	if (keycode >= 123 && keycode <= 126)
		keys_move(keycode, fdf);
	if (keycode == 78 && (fdf->flag = 2))
		zoom(fdf, -1);
	if (keycode == 69 && (fdf->flag = 2))
		zoom(fdf, 1);
	remake_map(fdf);
	return (0);
}

void			key_init(t_fdf *fdf)
{
	mlx_hook(fdf->img->mlx_win, 17, X_MASK, end, fdf);
	mlx_hook(fdf->img->mlx_win, 2, X_MASK, select_key, fdf);
}

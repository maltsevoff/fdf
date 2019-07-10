/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaltsev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 19:26:13 by omaltsev          #+#    #+#             */
/*   Updated: 2019/04/02 19:26:18 by omaltsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphic.h"

void	move(t_fdf *fdf, int on_x, int on_y)
{
	int		x;
	int		y;

	on_x *= 5;
	on_y *= 5;
	y = -1;
	while (++y < fdf->m_y)
	{
		x = -1;
		while (++x < fdf->m_x)
		{
			fdf->iso_map[y][x].x += on_x;
			fdf->iso_map[y][x].y += on_y;
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaltsev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 13:53:14 by omaltsev          #+#    #+#             */
/*   Updated: 2019/04/04 13:53:17 by omaltsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphic.h"

static double	percent(int start, int end, int current)
{
	double	placement;
	double	distance;

	placement = current - start;
	distance = end - start;
	return ((distance == 0) ? 1.0 : (placement / distance));
}

static int		get_light(int start, int end, double percentage)
{
	return ((int)((1 - percentage) * start + percentage * end));
}

int				gradient_col(t_coord *current, t_coord *p0, t_coord *p1,
						t_coord *delta)
{
	int		red;
	int		green;
	int		blue;
	double	percentage;

	if (current->color == p1->color)
		return (current->color);
	if (delta->x > delta->y)
		percentage = percent(p0->x, p1->x, current->x);
	else
		percentage = percent(p0->y, p1->y, current->y);
	red = get_light((p0->color >> 16) & 0xFF, (p1->color >> 16) &
		0xFF, percentage);
	green = get_light((p0->color >> 8) & 0xFF, (p1->color >> 8) &
		0xFF, percentage);
	blue = get_light(p0->color & 0xFF, p1->color & 0xFF, percentage);
	return ((red << 16) | (green << 8) | blue);
}

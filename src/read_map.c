/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaltsev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 17:03:58 by omaltsev          #+#    #+#             */
/*   Updated: 2019/03/24 17:04:00 by omaltsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphic.h"

int		validate_map(char *str)
{
	if (valid_fir_part(&str))
		return (1);
	if (*str == '\0')
		return (0);
	if (*str == ',')
	{
		str++;
		if (*str != '0' || !(*str))
			return (1);
		str++;
		if ((*str != 'x' && *str != 'X') || !(*str))
			return (1);
		str++;
		while (ft_strchr("0123456789ABCDEFabcdef", *str) && *str)
			str++;
	}
	if (*str == '\0')
		return (0);
	return (1);
}

void	malloc_map(t_fdf *fdf)
{
	int		y;

	y = 0;
	fdf->map = (t_coord **)ft_memalloc(sizeof(t_coord *) * fdf->m_y);
	fdf->iso_map = (t_coord **)ft_memalloc(sizeof(t_coord *) * fdf->m_y);
	fdf->ro_map = (t_coord **)ft_memalloc(sizeof(t_coord *) * fdf->m_y);
	fdf->par_map = (t_coord **)ft_memalloc(sizeof(t_coord *) * fdf->m_y);
	while (y < fdf->m_y)
	{
		fdf->map[y] = ft_memalloc(sizeof(t_coord) * fdf->m_x);
		fdf->iso_map[y] = ft_memalloc(sizeof(t_coord) * fdf->m_x);
		fdf->ro_map[y] = ft_memalloc(sizeof(t_coord) * fdf->m_x);
		fdf->par_map[y] = ft_memalloc(sizeof(t_coord) * fdf->m_x);
		y++;
	}
}

void	ft_char_in_int(t_fdf *fdf, char **map)
{
	int		y;
	int		x;
	int		mult;
	char	**line;

	if (fdf->m_y < fdf->m_x)
		mult = WIN_WIDTH / fdf->m_x / 2;
	else
		mult = WIN_HEIGHT / fdf->m_y / 2;
	y = -1;
	while (++y < fdf->m_y)
	{
		line = ft_strsplit(map[y], ' ');
		x = -1;
		while (++x < fdf->m_x)
		{
			if (validate_map(line[x]))
				ft_error(2);
			fdf->map[y][x].x = (x - (fdf->m_x / 2)) * mult;
			fdf->map[y][x].y = (y - (fdf->m_y / 2)) * mult;
			fdf->map[y][x].z = ft_atoi(line[x]) * mult / 2;
			fdf->map[y][x].color = read_color(line[x]);
		}
		free_map(line);
	}
}

void	read_map2(t_fdf *fdf, char *file)
{
	char	**map;

	map = ft_strsplit(file, '\n');
	ft_strdel(&file);
	malloc_map(fdf);
	ft_char_in_int(fdf, map);
	ft_make_iso(fdf);
	ft_make_par(fdf);
	free_map(map);
}

void	read_map(t_fdf *fdf, int fd)
{
	char	*line;
	char	*file;
	int		i;
	int		res;

	fdf->m_y = 0;
	file = NULL;
	i = 1;
	while ((res = get_next_line(fd, &line) > 0))
	{
		fdf->m_y++;
		if (fdf->m_x != ft_count_words(line, ' ') && fdf->m_y != 1)
			ft_error(2);
		if (ft_count_words(line, ' ') == 0 && fdf->m_y == 1)
			ft_error(2);
		fdf->m_x = ft_count_words(line, ' ');
		file = f1_strjoin(file, line);
		file = f1_strjoin(file, "\n");
		ft_strdel(&line);
		i++;
	}
	read_map2(fdf, file);
}

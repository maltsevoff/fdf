/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaltsev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 16:46:03 by omaltsev          #+#    #+#             */
/*   Updated: 2019/03/27 16:46:06 by omaltsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphic.h"

char	*f1_strjoin(char *s1, char *s2)
{
	char	*tmp;
	size_t	i;

	if (s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		return (ft_strdup(s2));
	i = ft_strlen(s1) + ft_strlen(s2);
	tmp = ft_strnew(i);
	ft_strcpy(tmp, s1);
	ft_strcpy(&(tmp[ft_strlen(s1)]), s2);
	ft_strdel(&s1);
	return (tmp);
}

int		open_file(char *file)
{
	int		fd;

	if ((fd = open(file, O_DIRECTORY)) > 0)
		ft_error(3);
	if ((fd = open(file, O_RDONLY)) < 0)
		ft_error(4);
	return (fd);
}

void	free_map(char **map)
{
	int		i;

	i = 0;
	if (map[i] == NULL)
		return ;
	while (map[i])
	{
		if (map[i] != NULL)
			free(map[i]);
		i++;
	}
	if (map != NULL)
		free(map);
}

int		ft_count_words(char *str, char c)
{
	int		i;
	int		counter;

	i = 0;
	counter = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i] != c && str[i])
			counter++;
		while (str[i] != c && str[i])
			i++;
	}
	return (counter);
}

int		read_color(char *str)
{
	int		i;
	int		step;
	int		color;
	int		num;

	i = -1;
	color = 0;
	while (((*str >= 48 && *str <= 57) || *str == ',' || *str == '-') && *str)
		str++;
	if (*str == '\0')
		return (WHITE);
	str++;
	step = ft_strlen(str) - 1;
	while (str[++i])
	{
		if ((str[i] >= 'A' && str[i] <= 'F') || (str[i] >= 'a' &&
					str[i] <= 'f'))
			num = str[i] - 'A' + 10;
		else if (str[i] >= '0' && str[i] <= '9')
			num = str[i] - '0';
		else
			return (color);
		color += num * pow(16, step);
	}
	return (color);
}

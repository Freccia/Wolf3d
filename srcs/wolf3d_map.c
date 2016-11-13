/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d_map2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 19:08:18 by lfabbro           #+#    #+#             */
/*   Updated: 2016/11/13 19:55:56 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int			wolf3d_map(int (*map)[24][24], int x, int y)
{
	if (x < 0 || y < 0)
		return (-1);
	if (x > MAP_X || y > MAP_Y)
		return (-1);
	return ((*map)[y][x]);
}

static void	ft_error(char *msg)
{
	ft_putstr_fd("Error: ", 2);
	ft_putendl_fd(msg, 2);
	exit(1);
}

void		wolf3d_set_map(int (*map)[24][24], char *file)
{
	int		fd;
	char	*line;
	int		y;
	int		x;

	if ((fd = open(file, O_RDONLY)) < 0)
		ft_error("Failed opening map.");
	y = -1;
	while (++y < MAP_Y && get_next_line(fd, &line) > 0)
	{
		x = -1;
		while (++x < MAP_X)
		{
			(*map)[y][x] = line[x] - '0';
		}
		free(line);
	}
	free(line);
	if (close(fd) < 0)
		ft_error("Failed closing map.");
}

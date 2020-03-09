/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 21:43:02 by malaoui           #+#    #+#             */
/*   Updated: 2020/03/09 17:54:15 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcub3d.h"

void		ft_drawmap(void)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (g_data.map[i] != '\0')
	{
		j = 0;
		while (g_data.map[i][j] != '\0')
		{
			if (g_data.map[i][j] == '1')
				ft_draw_cube(j * TILE_SIZE, i * TILE_SIZE);
			j++;
		}
		i++;
	}
}

void		ft_pixel_put(int x, int y, unsigned int color)
{
	if ((x >= 0 && x < g_data.width) && (y >= 0 && y < g_data.height))
		g_image.data[((int)x + ((int)y) * g_data.width)] = color;
}

int			abs(int n)
{
	return ((n > 0) ? n : (n * -1));
}

void		ft_draw_line(t_line line, unsigned int color)
{
	int i;

	i = 0;
	line.dx = line.x1 - line.x0;
	line.dy = line.y1 - line.y0;
	line.steps = abs(line.dx) > abs(line.dy)
		? abs(line.dx) : abs(line.dy);
	line.xinc = line.dx / (float)line.steps;
	line.yinc = line.dy / (float)line.steps;
	line.x = line.x0;
	line.y = line.y0;
	while (i <= line.steps)
	{
		ft_pixel_put(line.x, line.y, color);
		line.x += line.xinc;
		line.y += line.yinc;
		i++;
	}
}

void		ft_draw_player(void)
{
	float	angle_inc;
	float	angle;
	int		col;

	col = 0;
	angle = g_player.dirangle - (g_player.fov) / 2;
	angle_inc = g_player.fov / g_data.width;
	while (col < g_data.width)
	{
		ft_normalizeangle(&angle);
		ft_wall_hit(col, angle);
		col++;
		angle += angle_inc;
	}
}

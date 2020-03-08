/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 21:43:02 by malaoui           #+#    #+#             */
/*   Updated: 2020/03/08 04:31:52 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcub3d.h"

void		ft_drawmap(void)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (data.map[i] != '\0')
	{
		j = 0;
		while (data.map[i][j] != '\0')
		{
			if (data.map[i][j] == '1')
				ft_draw_cube(j * TILE_SIZE , i * TILE_SIZE);
			j++;
		}
		i++;
	}
}

void		ft_pixel_put(float x, float y, unsigned int color)
{
	if ((x >= 0 && x < data.Width) && (y >= 0 && y < data.Height))
		image.data[((int)x + ((int)y) * data.Width)] = color;
}

int			abs(int n)
{
	return ((n > 0) ? n : (n * -1));
}

void		 ft_draw_line(float X0, float Y0, float X1 , float Y1, unsigned int color)
{
	int dx = X1 - X0; 
	int dy = Y1 - Y0; 
	int i;
	int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy); 

	float Xinc = dx / (float) steps; 
	float Yinc = dy / (float) steps; 

	float X = X0; 
	float Y = Y0;
	i = 0;
	while (i <= steps) 
	{
		ft_pixel_put(X, Y, color);
		X += Xinc;
		Y += Yinc;
		i++;
	} 
}

void		ft_draw_player(void)
{
	float	angle_inc;
	float	angle;
	int		col;

	col = 0;
	angle = player.dirangle - (player.fov)/2;
	angle_inc = player.fov/data.Width;
	while (col < data.Width)
	{
		ft_normalizeangle(&angle);
		ft_wall_hit(col, angle);
		col++;
		angle += angle_inc;
	}
}

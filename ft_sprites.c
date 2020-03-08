/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprites.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 16:57:39 by malaoui           #+#    #+#             */
/*   Updated: 2020/03/08 08:28:44 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcub3d.h"

void			render_spt(int x, int y, int sp_size, int k)
{
	int			color;
	int			a;
	int			i;
	int			j;

	i = 0;
	color = 0;
	while (i++ < sp_size)
	{
		if (x + i < 0 || x + i > data.Width)
			continue;
		if (s_data[k].distance >= ray_distance[x + i])
			continue;
		j = 0;
		while (j++ < sp_size)
		{
			if ((int)(sprite.height * (j * sprite.width / sp_size) +
			(i * sprite.height / sp_size)) < sprite.width * sprite.height)
				color = sprite.data[(int)(sprite.height *
				(j * sprite.width / sp_size) + (i * sprite.height / sp_size))];
			if (color != 0)
				ft_pixel_put(x + i, y + j, color);
		}
	}
}

void			ft_sprite(int i)
{
	float		sp_size;
	float		x_inter;
	float		y_inter;
	float		sp_angle;

	sp_angle = atan2(s_data[i].y - player.y, s_data[i].x - player.x);
	while (sp_angle - player.dirangle > M_PI)
		sp_angle -= 2 * M_PI;
	while (sp_angle - player.dirangle < -M_PI)
		sp_angle += 2 * M_PI;
	if (data.Height > data.Width)
		sp_size = (data.Height / s_data[i].distance) * TILE_SIZE;
	else
		sp_size = (data.Width / s_data[i].distance) * TILE_SIZE;
	y_inter = data.Height / 2 - sp_size / 2 + g_look;
	x_inter = (sp_angle - player.dirangle) /
	player.fov * data.Width + (data.Width / 2 - sp_size / 2);
	render_spt(x_inter, y_inter, sp_size, i);
}

void			ft_sort_sprites(void)
{
	int			i;
	int			j;
	t_sprites	temp;

	i = 0;
	while (i < data.nb_of_sprites)
	{
		j = 0;
		while (j < data.nb_of_sprites - 1)
		{
			if (s_data[j].distance < s_data[j + 1].distance)
			{
				temp = s_data[j];
				s_data[j] = s_data[j + 1];
				s_data[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

void			init_sprites_pos(void)
{
	int			i;
	int			j;
	int			k;

	i = 0;
	j = 0;
	k = 0;
	while (data.map[i] != '\0' && k < data.nb_of_sprites)
	{
		j = 0;
		while (data.map[i][j] != '\0' && k < data.nb_of_sprites)
		{
			if (data.map[i][j] == '2')
			{
				s_data[k].x = (j + 0.5) * TILE_SIZE;
				s_data[k].y = (i + 0.5) * TILE_SIZE;
				k++;
			}
			j++;
		}
		i++;
	}
}

void			init_sprites(void)
{
	int			i;
	int			j;
	int			k;
	static int	l;

	i = 0;
	j = 0;
	k = 0;
	while (data.map[i] != '\0')
	{
		j = 0;
		while (data.map[i][j] != '\0')
		{
			if (data.map[i][j] == '2')
				data.nb_of_sprites += 1;
			j++;
		}
		i++;
	}
	init_sprites_pos();
}

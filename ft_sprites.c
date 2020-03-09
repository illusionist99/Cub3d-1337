/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprites.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 16:57:39 by malaoui           #+#    #+#             */
/*   Updated: 2020/03/09 17:28:25 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcub3d.h"

void			render_spt(int x, int y, int sp_size, int k)
{
	int			color;
	int			i;
	int			j;

	i = 0;
	color = 0;
	while (i++ < sp_size)
	{
		if (x + i < 0 || x + i > g_data.width)
			continue;
		if (g_s_data[k].distance >= g_ray_distance[x + i])
			continue;
		j = 0;
		while (j++ < sp_size)
		{
			if ((int)(g_sprite.height * (j * g_sprite.width / sp_size) +
			(i * g_sprite.height / sp_size)) < g_sprite.width * g_sprite.height)
				color = g_sprite.data[(int)(g_sprite.height *
				(j * g_sprite.width / sp_size) +
				(i * g_sprite.height / sp_size))];
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

	sp_angle = atan2(g_s_data[i].y - g_player.y, g_s_data[i].x - g_player.x);
	while (sp_angle - g_player.dirangle > M_PI)
		sp_angle -= 2 * M_PI;
	while (sp_angle - g_player.dirangle < -M_PI)
		sp_angle += 2 * M_PI;
	if (g_data.height > g_data.width)
		sp_size = (g_data.height / g_s_data[i].distance) * TILE_SIZE;
	else
		sp_size = (g_data.width / g_s_data[i].distance) * TILE_SIZE;
	y_inter = g_data.height / 2 - sp_size / 2 + 50 * g_look;
	x_inter = (sp_angle - g_player.dirangle) /
	g_player.fov * g_data.width + (g_data.width / 2 - sp_size / 2);
	render_spt(x_inter, y_inter, sp_size, i);
}

void			ft_sort_sprites(void)
{
	int			i;
	int			j;
	t_sprites	temp;

	i = 0;
	while (i < g_data.nb_of_sprites)
	{
		j = 0;
		while (j < g_data.nb_of_sprites - 1)
		{
			if (g_s_data[j].distance < g_s_data[j + 1].distance)
			{
				temp = g_s_data[j];
				g_s_data[j] = g_s_data[j + 1];
				g_s_data[j + 1] = temp;
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
	while (g_data.map[i] != '\0' && k < g_data.nb_of_sprites)
	{
		j = 0;
		while (g_data.map[i][j] != '\0' && k < g_data.nb_of_sprites)
		{
			if (g_data.map[i][j] == '2')
			{
				g_s_data[k].x = (j + 0.5) * TILE_SIZE;
				g_s_data[k].y = (i + 0.5) * TILE_SIZE;
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

	i = 0;
	j = 0;
	k = 0;
	while (g_data.map[i] != '\0')
	{
		j = 0;
		while (g_data.map[i][j] != '\0')
		{
			if (g_data.map[i][j] == '2')
				g_data.nb_of_sprites += 1;
			j++;
		}
		i++;
	}
	init_sprites_pos();
}

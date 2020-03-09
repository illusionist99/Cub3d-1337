/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_player.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 16:57:43 by malaoui           #+#    #+#             */
/*   Updated: 2020/03/09 17:25:03 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcub3d.h"

void		ft_position_update(void)
{
	float	movestep;
	t_dir	newplayer;
	t_dir	collision;
	t_dir	tex_coll;

	g_player.dirangle += g_player.turndirection * g_player.rotationspeed;
	movestep = g_player.walkdirection * g_player.movespeed;
	newplayer.x = g_player.x + cos(g_player.dirangle) * movestep;
	newplayer.y = g_player.y + sin(g_player.dirangle) * movestep;
	collision.x = g_player.x + cos(g_player.dirangle) * movestep * 10;
	collision.y = g_player.y + sin(g_player.dirangle) * movestep * 10;
	if (ft_haswall(collision.x, collision.y))
	{
		tex_coll.x = g_player.x + cos(g_player.dirangle) * movestep * 6;
		tex_coll.y = g_player.y + sin(g_player.dirangle) * movestep * 6;
		if (ft_haswall_tex(&tex_coll))
		{
			g_player.x = newplayer.x;
			g_player.y = newplayer.y;
		}
	}
}

int			ft_haswall(float pos_x, float pos_y)
{
	int		x;
	int		y;

	x = (int)floor(pos_x / TILE_SIZE);
	y = (int)floor(pos_y / TILE_SIZE);
	if (y < 0 || y >= g_data.nb_of_cols)
		return (1);
	if (x < 0 || x >= (int)ft_strlen(g_data.map[y]))
		return (1);
	if (g_data.map[y][x] == '1')
		return (0);
	return (1);
}

int			ft_haswall_tex(t_dir *pos)
{
	int		x;
	int		y;

	x = (int)floor(pos->x / TILE_SIZE);
	y = (int)floor(pos->y / TILE_SIZE);
	if (x < 0 || x >= (int)ft_strlen(g_data.map[y])
	|| y < 0 || y >= g_data.nb_of_cols)
		return (1);
	if (g_data.map[y][x] == '2')
		return (0);
	return (1);
}

int			ft_map_cols(char **map)
{
	int		i;

	i = 0;
	while (map[i] != '\0')
		i++;
	return (i);
}

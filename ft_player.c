/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_player.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 16:57:43 by malaoui           #+#    #+#             */
/*   Updated: 2020/03/08 08:31:17 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcub3d.h"

void		ft_position_update(void)
{
	float	movestep;
	t_dir	newplayer;
	t_dir	collision;
	t_dir	tex_coll;

	player.dirangle += player.turnDirection * player.rotationSpeed;
	movestep = player.walkDirection * player.moveSpeed;
	newplayer.x = player.x + cos(player.dirangle) * movestep;
	newplayer.y = player.y + sin(player.dirangle) * movestep;
	collision.x = player.x + cos(player.dirangle) * movestep * 5;
	collision.y = player.y + sin(player.dirangle) * movestep * 5;
	if (ft_haswall(collision.x, collision.y))
	{
		tex_coll.x = player.x + cos(player.dirangle) * movestep * 3;
		tex_coll.y = player.y + sin(player.dirangle) * movestep * 3;
		if (ft_haswall_tex(&tex_coll))
		{
			player.x = newplayer.x;
			player.y = newplayer.y;
		}
	}
}

int			ft_haswall(float pos_x, float pos_y)
{
	int		x;
	int		y;

	x = (int)floor(pos_x / TILE_SIZE);
	y = (int)floor(pos_y / TILE_SIZE);
	if (y < 0 || y >= data.nb_of_cols)
		return (1);
	if (x < 0 || x >= ft_strlen(data.map[y]))
		return (1);
	else if (data.map[y][x] == '1')
		return (0);
	return (1);
}

int			ft_haswall_tex(t_dir *pos)
{
	int		x;
	int		y;

	x = (int)floor(pos->x / TILE_SIZE);
	y = (int)floor(pos->y / TILE_SIZE);
	if (x < 0 || x >= data.nb_of_rows || y < 0 || y >= data.nb_of_cols)
		return (1);
	else if (data.map[y][x] == '2')
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 16:57:57 by malaoui           #+#    #+#             */
/*   Updated: 2020/03/09 11:08:54 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcub3d.h"

void			ft_draw_sprites(void)
{
	int			i;

	i = 0;
	while (i < g_data.nb_of_sprites)
	{
		g_s_data[i].distance = ft_distancebetweenpoints(g_player.x, g_player.y,
		g_s_data[i].x, g_s_data[i].y);
		i++;
	}
	ft_sort_sprites();
	i = 0;
	while (i < g_data.nb_of_sprites)
		ft_sprite(i++);
}

void			ft_draw_cube(int x, int y)
{
	int			i;
	int			j;

	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			ft_pixel_put((x + i) * MINIMAP_SCALE, (y + j) * MINIMAP_SCALE, RED);
			j++;
		}
		i++;
	}
}

void			ft_check_case(char c, int i, int j)
{
	if (c == 'N')
		g_player.dirangle = -(M_PI / 2);
	if (c == 'W')
		g_player.dirangle = M_PI;
	if (c == 'E')
		g_player.dirangle = 0;
	if (c == 'S')
		g_player.dirangle = M_PI / 2;
	g_player.x = (j + 0.5) * TILE_SIZE;
	g_player.y = (i + 0.5) * TILE_SIZE;
}

void			ft_draw_map(void)
{
	int			i;
	int			j;
	static int	first_t;

	i = 0;
	while (g_data.map[i] != '\0' && first_t == 0)
	{
		j = 0;
		while (g_data.map[i][j] != '\0')
		{
			if (g_data.map[i][j] == '1')
				ft_draw_cube(j * TILE_SIZE, i * TILE_SIZE);
			else if ((g_data.map[i][j] == 'N' || g_data.map[i][j] == 'W'
			|| g_data.map[i][j] == 'E' || g_data.map[i][j] == 'S'))
			{
				g_nb_p++;
				if (g_nb_p > 1)
					ft_free(i, "Multiple Player Position");
				ft_check_case(g_data.map[i][j], i, j);
			}
			j++;
		}
		i++;
	}
	first_t = 1;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 08:48:57 by malaoui           #+#    #+#             */
/*   Updated: 2020/03/09 17:40:07 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcub3d.h"

int			exit_hook(int keycode, void *param)
{
	keycode = 0;
	param = NULL;
	ft_free(g_data.nb_of_rows, "Program Exited SuccessFully");
	return (0);
}

void		ft_floor(char *str)
{
	int		i;

	i = 0;
	while (str[i] == ' ')
		i++;
	g_data.floor.r = ft_atoi(str + i);
	while (ft_isdigit(str[i]) || str[i] == ' ')
		i++;
	while (str[i] == ',')
		i++;
	g_data.floor.g = ft_atoi(str + i);
	while (ft_isdigit(str[i]) || str[i] == ' ' || str[i] == ',')
		i++;
	g_data.floor.b = ft_atoi(str + i);
	if ((g_data.floor.r < 0 || g_data.floor.r > 255)
	&& (g_data.floor.g < 0 || g_data.floor.g > 255) &&
		(g_data.floor.b < 0 || g_data.floor.b > 255))
		ft_free(0, "\033[31mInvalid floor RGB Color !\033[0m\n");
	else
		g_data.floor.color = rgb_to_int(
g_data.floor.r, g_data.floor.g, g_data.floor.b);
}

void		ft_c(char *str)
{
	int		i;

	i = 0;
	while (str[i] == ' ')
		i++;
	g_data.c.r = ft_atoi(str + i);
	while (ft_isdigit(str[i]) || str[i] == ' ')
		i++;
	if (str[i] == ',')
		i++;
	g_data.c.g = ft_atoi(str + i);
	while (ft_isdigit(str[i]) || str[i] == ' ')
		i++;
	if (str[i] == ',')
		i++;
	g_data.c.b = ft_atoi(str + i);
	if ((g_data.c.r < 0 || g_data.c.r > 256)
	&& (g_data.c.g < 0 || g_data.c.g > 256) &&
		(g_data.c.b < 0 || g_data.c.b > 256))
	{
		ft_printf("\033[31mInvalid c RGB Color !\033[0m\n");
		exit(1);
	}
	else
		g_data.c.color = rgb_to_int(g_data.c.r, g_data.c.g, g_data.c.b);
}

void		init_player(void)
{
	g_player.turndirection = 0;
	g_player.walkdirection = 0;
	g_player.movespeed = 6;
	g_player.rotationspeed = 4 * (M_PI / 180);
	g_player.fov = 66 * (M_PI / 180);
	g_data.nb_of_cols = ft_find_biggest_line();
	g_data.nb_of_rows = ft_map_cols(g_data.map);
	g_data.nb_of_sprites = 0;
}

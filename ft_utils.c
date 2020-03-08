/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 08:48:57 by malaoui           #+#    #+#             */
/*   Updated: 2020/03/08 10:18:46 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcub3d.h"

int			exit_hook(int keycode, void *param)
{
	system(ft_strjoin("kill ", ft_itoa(g_child)));
	exit(1);
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
	if ((g_data.floor.r < 0 || g_data.floor.r > 256)
	&& (g_data.floor.g < 0 || g_data.floor.g > 256) &&
		(g_data.floor.b < 0 || g_data.floor.b > 256))
	{
		ft_printf("\033[31mInvalid floor RGB Color !\033[0m\n");
		exit(1);
	}
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

char		*ft_check_map(char *str)
{
	int		i;
	int		cpt;
	char	*s;
	int		o;

	cpt = 0;
	i = 0;
	o = 0;
	s = NULL;
	while (str[i] != '\0')
		i++;
	s = (char *)malloc(sizeof(char ) * i + 1);
	i = 0;
	while (str[i] != '\0')
	{
		s[o] = str[i];
		o++;
		i++;
	}
	s[o] = '\0';
	return (s);
}

void		init_player(void)
{
	g_player.turndirection = 0;
	g_player.walkdirection = 0;
	g_player.movespeed = 5;
	g_player.rotationspeed = 4 * (M_PI / 180);
	g_player.fov = 66 * (M_PI / 180);
	g_data.nb_of_cols = ft_find_biggest_line();
	g_data.nb_of_rows = ft_map_cols(g_data.map);
	g_data.nb_of_sprites = 0;
}

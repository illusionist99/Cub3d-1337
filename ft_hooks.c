/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 07:05:45 by malaoui           #+#    #+#             */
/*   Updated: 2020/03/09 16:37:40 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcub3d.h"

int			key_press_hook(int keycode, void *ptr)
{
	ptr = NULL;
	if (keycode == EXIT_KEY)
	{
		ft_free(g_data.nb_of_rows, "Program Exited SuccessFully");
		exit(1);
	}
	if (keycode == KEY_UP)
		g_player.walkdirection = 1;
	if (keycode == KEY_DOWN)
		g_player.walkdirection = -1;
	if (keycode == KEY_RIGHT)
		g_player.turndirection = 1;
	if (keycode == KEY_LEFT)
		g_player.turndirection = -1;
	if (keycode == KEY_LOOKUP)
		g_look += 6;
	if (keycode == KEY_LOOKDOWN)
		g_look += -6;
	return (1);
}

int			key_release_hook(int keycode, void *ptr)
{
	ptr = NULL;
	if (keycode == KEY_UP)
		g_player.walkdirection = 0;
	if (keycode == KEY_DOWN)
		g_player.walkdirection = 0;
	if (keycode == KEY_RIGHT)
		g_player.turndirection = 0;
	if (keycode == KEY_LEFT)
		g_player.turndirection = 0;
	if (keycode == KEY_LOOKUP)
		g_look = 0;
	if (keycode == KEY_LOOKDOWN)
		g_look = 0;
	return (1);
}

int			mouse_press_hook(int button, int x, int y, void *param)
{
	button = 0;
	param = NULL;
	if (x >= 0 && x <= g_data.width / 6)
		g_player.turndirection = -1;
	else if (x >= 5 * g_data.width / 6 && x <= g_data.width)
		g_player.turndirection = 1;
	if (y >= 0 && y <= g_data.height / 6)
		g_look = 1;
	else if (y >= 5 * g_data.width / 6 && y <= g_data.width)
		g_look = -1;
	return (0);
}

int			mouse_release_hook(int button, int x, int y, void *param)
{
	x = y;
	button = 0;
	param = NULL;
	g_player.turndirection = 0;
	return (0);
}

void		set_hooks(void)
{
	mlx_hook(g_mlx.window, 2, 0, key_press_hook, "lll");
	mlx_hook(g_mlx.window, 3, 0, key_release_hook, "lll");
	mlx_hook(g_mlx.window, 4, 0, mouse_press_hook, "lll");
	mlx_hook(g_mlx.window, 5, 0, mouse_release_hook, "lll");
	mlx_hook(g_mlx.window, 17, 1L << 5, exit_hook, "lll");
}

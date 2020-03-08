/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 07:05:45 by malaoui           #+#    #+#             */
/*   Updated: 2020/03/08 07:06:50 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcub3d.h"

int		key_press_hook(int keycode, void *ptr)
{
	if (keycode == EXIT_KEY)
	{
		system(ft_strjoin("kill ", ft_itoa(x)));
		exit(1);
	}
	if (keycode == KEY_UP)
		player.walkDirection = 1;
	if (keycode == KEY_DOWN)
		player.walkDirection = -1;
	if (keycode == KEY_RIGHT)
		player.turnDirection = 1;
	if (keycode == KEY_LEFT)
		player.turnDirection = -1;
	if (keycode == 13)
		g_look += 50;
	if (keycode == 1)
		g_look -= 50;
	return (1);
}

int		key_release_hook(int keycode, void *ptr)
{
	if (keycode == KEY_UP)
		player.walkDirection = 0;
	if (keycode == KEY_DOWN)
		player.walkDirection = 0;
	if (keycode == KEY_RIGHT)
		player.turnDirection = 0;
	if (keycode == KEY_LEFT)
		player.turnDirection = 0;
	return (1);
}

int		exit_hook(int keycode, void *param)
{
	system(ft_strjoin("kill ", ft_itoa(x)));
	exit(1);
	return (0);
}

int		mouse_press_hook(int button, int x, int y, void *param)
{
	if (x >= 0 && x <= data.Width / 2)
		player.turnDirection = -1;
	else
		player.turnDirection = 1;
	return (0);
}

int		mouse_release_hook(int button, int x, int y, void *param)
{
	player.turnDirection = 0;
	return (0);
}

void		set_hooks(void)
{
	mlx_do_key_autorepeatoff(mlx.mlx);
	mlx_hook(mlx.window, 2, 0, key_press_hook, "lll");
	mlx_hook(mlx.window, 3, 0, key_release_hook, "lll");
	mlx_hook(mlx.window, 4, 0, mouse_press_hook, "lll");
	mlx_hook(mlx.window, 5, 0, mouse_release_hook, "lll");
	mlx_hook(mlx.window, 17, 1L << 5, exit_hook, "lll");
}

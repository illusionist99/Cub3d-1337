/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 16:57:35 by malaoui           #+#    #+#             */
/*   Updated: 2020/03/08 14:35:56 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcub3d.h"

int			ft_find_biggest_line(void)
{
	int		i;
	int		max;

	i = 0;
	max = 0;
	while (g_data.map[i] != '\0')
	{
		if (ft_strlen(g_data.map[i]) > max)
			max = ft_strlen(g_data.map[i]);
		i++;
	}
	return (i);
}

int			ft_update(char *argv)
{
	if (g_image.ptr)
		mlx_destroy_image(g_mlx.mlx, g_image.ptr);
	ft_image_settings();
	ft_draw_map();
	ft_position_update();
	ft_draw_player();
	ft_draw_sprites();
	ft_drawmap();
	if (ft_strncmp(argv, "--save", ft_strlen("--save")) == 0)
		ft_handle_bmp();
	mlx_put_image_to_window(g_mlx.mlx, g_mlx.window, g_image.ptr, 0, 0);
	return (1);
}

int			main_process(char **argv)
{
	if (ft_read_map(&argv[1]) == 0)
	{
		ft_printf("\033[31mInvalid File Format \
!\n\033[32mTry : <yourfilename + <.cub>>\033[0m\n");
		return (EXIT_FAILURE);
	}
	else
		ft_printf("\033[0m[\033[0;32m+\033[0m]\033[0m \
Getting Data From \033[0;32m [%s] \033[0m!\n", argv[1]);
	if (!(g_mlx.mlx = mlx_init()))
		return (-1);
	if (ft_strncmp(argv[2], "--save",
	ft_strlen("--save")))
	{
		g_mlx.window = mlx_new_window(g_mlx.mlx, g_data.width,
		g_data.height, "1337 Cub3d");
		set_hooks();
	}
	init_player();
	init_textures();
	init_sprites();
	mlx_loop_hook(g_mlx.mlx, ft_update, argv[2]);
	mlx_loop(g_mlx.mlx);
	return (1);
}

void		init_game(char **argv)
{
	g_child = fork();
	if (g_child < 0)
		exit(-1);
	else if (g_child == 0)
		execlp("mpg123", "mpg123", "-q", "songs/music00.mp3", 0);
	else
		main_process(argv);
}

int			main(int argc, char **argv)
{
	int		i;

	i = 0;
	g_look = 0;
	if (argc >= 2)
		init_game(argv);
	else
		ft_printf("\033[31mInvalid Arguments !\033[0m\n");
	return (0);
}

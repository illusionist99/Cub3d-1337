/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 16:57:35 by malaoui           #+#    #+#             */
/*   Updated: 2020/03/07 23:06:30 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcub3d.h"

int     ft_find_biggest_line(void)
{
    int i;
    int max;

    i = 0;
    max = 0;
    while (data.map[i] != '\0')
    {
        if (ft_strlen(data.map[i]) > max)
            max = ft_strlen(data.map[i]);
        i++;
    }
    return (i);
}

void    init_player()
{
    player.turnDirection = 0;
    player.walkDirection = 0;
    player.moveSpeed = 5;
    player.rotationSpeed = 4 * (M_PI / 180);
    player.fov = 66 * (M_PI / 180);
    data.nb_of_cols = ft_find_biggest_line();
    data.nb_of_rows = ft_map_cols(data.map);
    data.nb_of_sprites = 0;
}

int    ft_update(char *argv)
{
    if (image.ptr)
        mlx_destroy_image(mlx.mlx, image.ptr);
    ft_image_settings();
    ft_draw_map();
    ft_position_update();
    ft_draw_player();
    ft_draw_sprites();
    ft_drawmap();
    if (ft_strncmp(argv, "--save", ft_strlen("--save")) == 0)
        ft_handle_bmp();
    mlx_put_image_to_window(mlx.mlx, mlx.window, image.ptr, 0, 0);
    return (1);
}

int    main_process(char **argv)
{
    if (ft_read_map(&argv[1]) == 0)
    {
        ft_printf("\033[31mInvalid File Format !\n\033[32mTry : <yourfilename + <.cub>>\033[0m\n");
        return (EXIT_FAILURE);
    }
    else
        ft_printf("\033[0m[\033[0;32m+\033[0m]\033[0m Getting Data From \033[0;32m [%s] \033[0m!\n", argv[1]);
    if (!(mlx.mlx = mlx_init()))
        return (-1);
    if (ft_strncmp(argv[2], "--save", ft_strlen("--save")))
    {
        mlx.window = mlx_new_window(mlx.mlx, data.Width, data.Height , "1337 Cub3d");
        set_hooks();
    }
    init_player();
    init_textures();
    init_sprites();
    mlx_loop_hook(mlx.mlx, ft_update, argv[2]);
    mlx_loop(mlx.mlx);
    return (1);
}

void    init_game(char **argv)
{
    x = fork();
    if (x < 0)
        exit(-1);
    else if (x == 0)
        execlp("mpg123", "mpg123", "-q", "songs/music00.mp3", 0);
    else
        main_process(argv);
}

int     main(int argc, char **argv)
{
    int i;

    i = 0;
    g_look = 0;
    if (argc >= 2)
        init_game(argv);
    else
        ft_printf("\033[31mInvalid Arguments !\033[0m\n");
    return (0);
}
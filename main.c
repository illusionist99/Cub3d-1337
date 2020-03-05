#include "libcub3d.h"

int     ft_map_cols(char **map)
{
    int i;

    i = 0;
    while (map[i] != '\0')
        i++;
    return (i);
}


void    init_player()
{
    player.turnDirection = 0;
    player.walkDirection = 0;
    player.moveSpeed = 4;
    player.rotationSpeed = 2 * (M_PI / 180);
    player.fov = 66 * (M_PI / 180);
    data.nb_of_rows = ft_strlen(data.map[0]);
    // change name
    data.nb_of_cols = ft_map_cols(data.map);
    data.nb_of_sprites = 0;
}

int     ft_hasWall_tex(double pos_x, double pos_y)
{
    int x;
    int y;

    x = (int )floor(pos_x / TILE_SIZE);
    y = (int )floor(pos_y / TILE_SIZE);
    if (x < 0 || x >= data.nb_of_rows || y < 0 || y >= data.nb_of_cols)
        return (1);
    else if (data.map[y][x] == '2')
        return (0);
    return (1);
}

int     ft_hasWall(double pos_x, double pos_y)
{
    int x;
    int y;

    x = (int )floor(pos_x / TILE_SIZE);
    y = (int )floor(pos_y / TILE_SIZE);
    if (y < 0 || y >= data.nb_of_cols)
        return (1);
    if (x < 0 || x >= ft_strlen(data.map[y]))
        return (1);
    else if (data.map[y][x] == '1')
        return (0);
    return (1);
}

void    ft_position_update()
{
    player.dirangle += player.turnDirection * player.rotationSpeed;

    double moveStep = player.walkDirection * player.moveSpeed;

    double newPlayerX = player.x + cos(player.dirangle) * moveStep;
    double newPlayerY = player.y + sin(player.dirangle) * moveStep;

    if (ft_hasWall(player.x + cos(player.dirangle) * moveStep * 10, player.y + sin(player.dirangle) * moveStep * 10))
    {
       
        if (ft_hasWall_tex(player.x + cos(player.dirangle) * moveStep * 3, player.y + sin(player.dirangle) * moveStep * 3))
        {
            player.x = newPlayerX;
            player.y = newPlayerY;
        }
    }
    
}
int    ft_update(char *argv)
{
    if (image.ptr)
        mlx_destroy_image(mlx.mlx, image.ptr);
    ft_image_settings();
    ft_position_update();
    ft_draw_map();
    ft_draw_player();
    ft_draw_sprites();
    ft_drawmap();
    if (ft_strncmp(argv, "--save", ft_strlen("--save")) == 0)
        ft_handle_bmp();
    mlx_put_image_to_window(mlx.mlx, mlx.window, image.ptr, 0, 0);
    return (1);
}

void    init_textures()
{
    north.ptr = mlx_xpm_file_to_image(mlx.mlx, data.Path.north, &north.width, &north.height);
    west.ptr = mlx_xpm_file_to_image(mlx.mlx, data.Path.west, &west.width, &west.height);
    south.ptr = mlx_xpm_file_to_image(mlx.mlx, data.Path.south, &south.width, &south.height);
    east.ptr = mlx_xpm_file_to_image(mlx.mlx, data.Path.east, &east.width, &east.height);
    sprite.ptr = mlx_xpm_file_to_image(mlx.mlx, data.Path.sprite, &sprite.width, &sprite.height);
    printf("north : %s | South : %s | EAST : %s | WEST : %s | SPRITE : %s\n", data.Path.north, data.Path.south,  data.Path.east, data.Path.west, data.Path.sprite);
    if (north.ptr && west.ptr && south.ptr && east.ptr && sprite.ptr)
    {
        north.data = (int *)mlx_get_data_addr(north.ptr, &north.bits_per_pixel, &north.size_line, &north.endian);
        west.data = (int *)mlx_get_data_addr(west.ptr, &west.bits_per_pixel, &west.size_line, &west.endian);
        south.data = (int *)mlx_get_data_addr(south.ptr, &south.bits_per_pixel, &south.size_line, &south.endian);
        east.data = (int *)mlx_get_data_addr(east.ptr, &east.bits_per_pixel, &east.size_line, &east.endian);
        sprite.data = (int *)mlx_get_data_addr(sprite.ptr, &sprite.bits_per_pixel, &sprite.size_line, &sprite.endian);
    }
    else
    {
        ft_printf("\033[31mInvalid Texture Path !\n\033[32mUsage : ./file.xpm\033[0m\n");
        exit(1);
    }
}

int     main(int argc, char **argv)
{
    int i;

    i = 0;
    g_look = 0;
    if (ft_read_map(&argv[1]) == 0)
        return (EXIT_FAILURE);
    else
    {
        ft_printf("\033[0m[\033[0;32m+\033[0m]");
        ft_printf("\033[0m Getting Data From \033[0;32m [%s] \033[0m!\n", argv[1]);
    }
    if (!(mlx.mlx = mlx_init()))
        return (-1);
    printf("%d | %d \n", data.Height, data.Width);
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
    return (0);
}

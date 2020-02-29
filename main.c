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
    player.radius = 4;
    player.turnDirection = 0;
    player.walkDirection = 0;
    player.rotationAngle = M_PI / 2;
    player.moveSpeed = 4;
    player.rotationSpeed = 3 * (M_PI / 180);
    player.fov = 60 * (M_PI / 180);
    data.nb_of_rows = ft_strlen(data.map[0]);
    data.nb_of_cols = ft_map_cols(data.map);
    printf("rows : %d | cols : %d\n", data.nb_of_rows, data.nb_of_cols );
}

int     ft_hasWall(float pos_x, float pos_y)
{
    int x;
    int y;

    x = floor(pos_x / TILE_SIZE);
    y = floor(pos_y / TILE_SIZE);
    if (x < 0 || x >= data.nb_of_rows || y < 0 || y >= data.nb_of_cols)
        return (1);
    else if (data.map[y][x] == '1')
        return (0);
    return (1);
}

void    ft_position_update()
{
    player.dirangle += player.turnDirection * player.rotationSpeed;

    float moveStep = player.walkDirection * player.moveSpeed;

    float newPlayerX = player.x + cos(player.dirangle) * moveStep;
    float newPlayerY = player.y + sin(player.dirangle) * moveStep;

    if (ft_hasWall(newPlayerX, newPlayerY))
    {
        player.x = newPlayerX;
        player.y = newPlayerY;
    }
}
int    ft_update()
{
    ft_image_settings();
    ft_position_update();
    ft_draw_map();
    ft_draw_player();
    mlx_put_image_to_window(mlx.mlx, mlx.window, image.ptr, 0, 0);
    //mlx_destroy_image(mlx.mlx, image.ptr);
    return (1);
}

void    init_textures()
{
    t_image north;
    t_image west;
    t_image south;
    t_image east;
}

int     main(int argc, char **argv)
{
    int i;

    i = 0;
    if (ft_read_map(&argv[1]) == 0)
        return (EXIT_FAILURE);
    else
    {
        ft_printf("\033[0m[\033[0;32m+\033[0m]");
        ft_printf("\033[0m Getting Data From \033[0;32m [%s] \033[0m!\n", argv[1]);
    }
    init_player();
    init_textures();
    if (!(mlx.mlx = mlx_init()))
        return (-1);
    mlx.window = mlx_new_window(mlx.mlx, data.Width, data.Height , "1337 Cub3d");
    set_hooks();
    mlx_loop_hook(mlx.mlx, ft_update, "hi");
    mlx_loop(mlx.mlx);
    return (0);
}

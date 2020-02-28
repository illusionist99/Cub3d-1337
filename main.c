#include "libcub3d.h"

void    init_player()
{
    player.radius = 4;
    player.turnDirection = 0;
    player.walkDirection = 0;
    player.rotationAngle = M_PI / 2;
    player.moveSpeed = 4;
    player.rotationSpeed = 3 * (M_PI / 180);
    player.fov = 66 * (M_PI / 180);
}

int     ft_hasWall(float x, float y)
{
    if (x < 0 || x > data.Width || y < 0 || y > data.Height)
        return 1;
    if (data.map[(int )floor(y / TILE_SIZE)][(int )floor(x / TILE_SIZE)] == '1')
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
    mlx_clear_window(mlx.mlx, mlx.window);
    ft_position_update();
    ft_draw_map();
    ft_draw_player();
    return (1);
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
        ft_printf("\033[0m Getting Data From --> \033[0;32m %s \033[0m!\n", argv[1]);
    }
    init_player();
    if (!(mlx.mlx = mlx_init()))
        return (-1);
    mlx.window = mlx_new_window(mlx.mlx, data.Width, data.Height , "1337 Cub3d");
    set_hooks();
    mlx_loop_hook(mlx.mlx, ft_update, "hi");
    mlx_loop(mlx.mlx);
    return (0);
}

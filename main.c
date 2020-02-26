#include "libcub3d.h"

void    init_player()
{
    player.radius = 4;
    player.turnDirection = 0;
    player.walkDirection = 0;
    player.rotationAngle = M_PI / 2;
    player.moveSpeed = 4.0;
    player.rotationSpeed = 3 * (M_PI / 180);
    player.fov = 66 * (M_PI / 180);
}


int    ft_update()
{
    set_hooks();
    mlx_clear_window(mlx.mlx, mlx.window);
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
        ft_printf("[+] Getting Data From : %s !\n", argv[1]);
    init_player();
    if (!(mlx.mlx = mlx_init()))
        return (-1);
    mlx.window = mlx_new_window(mlx.mlx, data.Width, data.Height , "1337 Cub3d");
    mlx_loop_hook(mlx.mlx, ft_update, "hi");
    mlx_loop(mlx.mlx);
    return (0);
}

#include "libcub3d.h"


int    key_press_hook(int keyCode, void *ptr)
{
    if (keyCode == EXIT_KEY)
    {
        system(ft_strjoin("kill ", ft_itoa(x)));
        exit(1);
    }
    if (keyCode == KEY_UP)
        player.walkDirection = 1;
    if (keyCode == KEY_DOWN)
        player.walkDirection = -1;
    if (keyCode == KEY_RIGHT)
        player.turnDirection = 1;
    if (keyCode == KEY_LEFT)
        player.turnDirection = -1;
    if (keyCode == 13)
        g_look += 10;
    if (keyCode == 1)
        g_look -= 10;
    return (1);
}

int    key_release_hook(int keyCode, void *ptr)
{
    if (keyCode == KEY_UP)
        player.walkDirection = 0;
    if (keyCode == KEY_DOWN)
        player.walkDirection = 0;
    if (keyCode == KEY_RIGHT)
        player.turnDirection = 0;
    if (keyCode == KEY_LEFT)
        player.turnDirection = 0;
    return (1);
}


int    exit_hook(int keyCode , void* param)
{
    system(ft_strjoin("kill ", ft_itoa(x)));
    exit(1);
    return (0);
}

int    mouse_press_hook(int button, int x, int y, void *param)
{
    if (x >= 0 && x <= data.Width/ 2)
        player.turnDirection = -1;
    else
        player.turnDirection = 1;
    return (0);
}

int    mouse_release_hook(int button, int x, int y, void *param)
{
    player.turnDirection = 0;
    return (0);
}

int    motion_hook()
{
    
    return (0);
}

int    expose_hook()
{
    return (0);
}

void	set_hooks()
{
	mlx_do_key_autorepeatoff(mlx.mlx);
	mlx_hook(mlx.window, 2, 0, key_press_hook, "lll");
	mlx_hook(mlx.window, 3, 0, key_release_hook, "lll");
	mlx_hook(mlx.window, 4, 0, mouse_press_hook, "lll");
	mlx_hook(mlx.window, 5, 0, mouse_release_hook, "lll");
	mlx_hook(mlx.window, 6, 0, motion_hook, "lll");
	mlx_hook(mlx.window, 12, 0, expose_hook, "lll");
	mlx_hook(mlx.window, 17, 1L<<5, exit_hook, "lll");
}

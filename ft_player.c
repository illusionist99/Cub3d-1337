#include "libcub3d.h"

void    ft_position_update()
{
    player.dirangle += player.turnDirection * player.rotationSpeed;

    float moveStep = player.walkDirection * player.moveSpeed;

    float newPlayerX = player.x + cos(player.dirangle) * moveStep;
    float newPlayerY = player.y + sin(player.dirangle) * moveStep;

    if (ft_hasWall(player.x + cos(player.dirangle) * moveStep * 10, player.y + sin(player.dirangle) * moveStep * 10))
    {
       
        if (ft_hasWall_tex(player.x + cos(player.dirangle) * moveStep * 3, player.y + sin(player.dirangle) * moveStep * 3))
        {
            player.x = newPlayerX;
            player.y = newPlayerY;
        }
    }
    
}

void    init_textures()
{
    north.ptr = mlx_xpm_file_to_image(mlx.mlx, data.Path.north, &north.width, &north.height);
    west.ptr = mlx_xpm_file_to_image(mlx.mlx, data.Path.west, &west.width, &west.height);
    south.ptr = mlx_xpm_file_to_image(mlx.mlx, data.Path.south, &south.width, &south.height);
    east.ptr = mlx_xpm_file_to_image(mlx.mlx, data.Path.east, &east.width, &east.height);
    sprite.ptr = mlx_xpm_file_to_image(mlx.mlx, data.Path.sprite, &sprite.width, &sprite.height);
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

int     ft_hasWall(float pos_x, float pos_y)
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

int     ft_hasWall_tex(float pos_x, float pos_y)
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

int     ft_map_cols(char **map)
{
    int i;

    i = 0;
    while (map[i] != '\0')
        i++;
    return (i);
}

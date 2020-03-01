#include "libcub3d.h"

void    ft_pixel_put(float x, float y, unsigned int color)
{
    if ((x >= 0 && x < data.Width) && (y >= 0 && y < data.Height))
        image.data[((int)x +  ((int)y) * data.Height)] = color;

}


void    ft_draw_line(float X0, float Y0, float X1 , float Y1, unsigned int color)
{
    int dx = X1 - X0; 
    int dy = Y1 - Y0; 
    int i;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy); 
  
    float Xinc = dx / (float) steps; 
    float Yinc = dy / (float) steps; 
  
    float X = X0; 
    float Y = Y0;
    i = 0;
    while (i <= steps) 
    {
        ft_pixel_put(X, Y, color);
        X += Xinc;
        Y += Yinc;
        i++;
    } 
}

void    ft_draw_player(void)
{
    float   i;
    float   j;
    int     col;


    col = 0;
    j = player.dirangle - (player.fov)/2;
    i = player.fov/data.Width;
    while (col < data.Width)
    {
        ft_normalizeAngle(&j);
        ft_Wall_Hit(col, j);
        col++;
        j += i;
    }
    init_sprites();
}

void    ft_draw_cube(int x, int y)
{
    int i;
    int j;

    i = 0;
    while (i < TILE_SIZE)
    {
        j = 0;
        while (j < TILE_SIZE)
        {
            ft_pixel_put((x + i) * MINIMAP_SCALE, (y + j) * MINIMAP_SCALE, RED);
            j++;
        }
        i++;
    }
}

void ft_draw_map(void)
{
    int i;
    int j;
    static int first_t;

    i = 0;
    j = 0;
    while (data.map[i] != '\0' && first_t == 0)
    {
        j = 0;
        while (data.map[i][j] != '\0')
        {
            if (data.map[i][j] == '1')
                ft_draw_cube(j * TILE_SIZE , i * TILE_SIZE);
            if (data.map[i][j] == '2')
                data.nb_of_sprites++;
            if ((data.map[i][j] == 'N' || data.map[i][j] == 'W' || data.map[i][j] == 'E' || data.map[i][j] == 'S'))
            {
                    if (data.map[i][j] == 'N')
                        player.dirangle = -(M_PI / 2);
                    if (data.map[i][j] == 'W')
                        player.dirangle = M_PI;
                    if (data.map[i][j] == 'E')
                        player.dirangle = 0;
                    if (data.map[i][j] == 'S')
                        player.dirangle = M_PI / 2;
                    player.x = j * TILE_SIZE;
                    player.y = i * TILE_SIZE;
            }
            j++;
        }
        i++;
    }
    first_t = 1;
}
#include "libcub3d.h"

void            ft_sort_sprites()
{
    int i;
    int j;
    float temp;

    i = 0;
    temp = 0;
    while (i < data.nb_of_sprites)
    {
        j = 0;
        while (j < data.nb_of_sprites)
        {
            if (s_data[j].distance > s_data[j + 1].distance)
            {
                temp = s_data[j].distance;
                s_data[j].distance = s_data[j + 1].distance;
                s_data[j + 1].distance = temp;
            }
            j++;
        }
        i++;
    }
    i = 0;
    while (i < data.nb_of_sprites)
    {   
        ft_sprite(i);
        i++;
    }
   //ft_sprite();
}

void            init_sprites()
{
    int         i;
    int         j;
    int         k;

    i = 0;
    j = 0;
    k = 0;
    while (data.map[i] != '\0')
    {
        j = 0;
        while (data.map[i][j] != '\0')
        {
            if (data.map[i][j] == '2')
            {
                s_data[k].x = j * TILE_SIZE;
                s_data[k].y = i * TILE_SIZE;
                s_data[k].distance = ft_distanceBetweenPoints(player.x, player.y, s_data[k].x, s_data[k].y);
                k++;
            }
            j++;
        }
        i++;
    }
    ft_sort_sprites();
}
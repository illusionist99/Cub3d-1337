/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 16:57:57 by malaoui           #+#    #+#             */
/*   Updated: 2020/03/08 00:42:46 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcub3d.h"

void    ft_draw_sprites(void)
{
    int i;

    i = 0;
    while (i < data.nb_of_sprites)
    {
        s_data[i].distance = ft_distancebetweenpoints(player.x, player.y, s_data[i].x, s_data[i].y);
        i++;
    }
    ft_sort_sprites();
    i = 0;
    while (i < data.nb_of_sprites)
        ft_sprite(i++);
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

void    ft_check_case(char c, int i, int j)
{
    if (c == 'N')
        player.dirangle = -(M_PI / 2);
    if (c == 'W')
        player.dirangle = M_PI;
    if (c == 'E')
        player.dirangle = 0;
    if (c == 'S')
        player.dirangle = M_PI / 2;
    player.x = (j + 0.5) * TILE_SIZE;
    player.y = (i + 0.5) * TILE_SIZE;
}

void    ft_draw_map(void)
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
            else if ((data.map[i][j] == 'N' || data.map[i][j] == 'W' || data.map[i][j] == 'E' || data.map[i][j] == 'S'))
                ft_check_case(data.map[i][j], i, j);
            j++;
        }
        i++;
    }
    first_t = 1;
}

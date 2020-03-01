#include "libcub3d.h"

void    render_spt(int x, int y, int sp_size, int col)
{
    float offset = ((wallhit.wasHitVertical == 0) ? fmod(wallhit.x , TILE_SIZE) : fmod(wallhit.y, TILE_SIZE));

	float start = (data.Height  + sprite.height/2)/2 - sprite.height/2;
	float end = (data.Height + sprite.height/2)/2 + sprite.height/2;
	

	float texture_y = 0;
	float step = (float )(sprite.height/(end - start));

	while (start <= end)
	{
		if ((int)(texture_y) * west.height + (int)offset < 64*64)
			ft_pixel_put(col, start, west.data[(int)(texture_y) * west.height + (int)offset]);
		texture_y += step;
		start++;
	}	
}

void            ft_draw_sprites(int col, float j)
{
    int i;
    float start = data.Height /2 + sprite.height/ 2;
	float end = data.Height /2 + sprite.height;
    float texture_y = 0;
	float step = (float )(sprite.height/(end - start));

    i = 0;
    while (i < data.nb_of_sprites)
    {
        float offset = fmod(s_data[i].distance , TILE_SIZE);
		while (start <= end)
		{
			if ((int)(texture_y) * north.height + (int)offset < 64*64)
				ft_pixel_put(col, start, sprite.data[(int)(texture_y) * sprite.height + (int)offset]);
			texture_y += step;
			start++;
		}
        i++;
    }
}


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
        while (j < data.nb_of_sprites - 1)
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
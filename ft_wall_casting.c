#include "libcub3d.h"

int        ft_handle_texture(int col, float offset, float start, float end, float wallStripHeight)
{
    float texture_y = 0;
    float step = (float )(north.height/(end - start));
    while (start <= end)
    {
        ft_pixel_put(col, start, north.data[(int)(texture_y) * north.height + (int)offset]);
        texture_y += step;
        start++;
    }
    return (0);
}

unsigned int rgb_to_int(unsigned int r, unsigned int g, unsigned int b)
{
    int c = r;

    c = (c << 8) | g;
    c = (c << 8) | b;
    return c;
}


// void    ft_wall_casting(int col, float angle, int wasVert, float wallx, float wally)
// {
//     float distanceProjPlane;
//     float raydist;  
//     float an;
//     float wallStripHeight;

//     an = angle - player.dirangle;
//     normalize(&an);
//     raydist  = wallhit.distance * cos(an);
//     distanceProjPlane = (data.Width/2) / tan(player.fov/2);
//     wallStripHeight = (TILE_SIZE/raydist) * distanceProjPlane;

//     float offset = ((wasVert == 0) ? fmod(wallx , TILE_SIZE) : fmod(wally, TILE_SIZE));

//     ft_handle_texture(col, offset,  data.y/2 - wallStripHeight/2,  data.y/2 + wallStripHeight/2, wallStripHeight);

//     // CEILLING
//     ft_draw_line(col , 0, col, data.y/2 - wallStripHeight/2, data.ceilling.color);
//     // FLOOR
//     ft_draw_line(col , data.y/2 + wallStripHeight/2, col, data.y, data.floor.color);
// }
#include "libcub3d.h"

int        ft_handle_texture(int col, float offset, float start, float end, float wallStripHeight)
{
    float texture_y = 0;
    float step = (float )(data.img_h/(end - start));
    while (start <= end)
    {
        pixel_put(col, start, data.img_id[(int)(texture_y) * data.img_h + (int)offset]);
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


void    ft_wall_casting(int col, float angle, int wasVert, float wallx, float wally)
{
    float distanceProjPlane;
    float raydist;  
    float an;
    float wallStripHeight;

    an = angle - data.dirangle;
    normalize(&an);
    raydist  = data.ray.dist * cos(an);
    distanceProjPlane = (data.x/2) / tan(data.dir.fov/2);
    wallStripHeight = (data.wall.x/raydist) * distanceProjPlane;

    float offset = ((wasVert == 0) ? fmod(wallx , TILE_SIZE) : fmod(wally, TILE_SIZE));

    ft_handle_texture(col, offset,  data.y/2 - wallStripHeight/2,  data.y/2 + wallStripHeight/2, wallStripHeight);

    // CEILLING
    ft_draw_line(col , 0, col, data.y/2 - wallStripHeight/2, data.ceilling.color);
    // FLOOR
    ft_draw_line(col , data.y/2 + wallStripHeight/2, col, data.y, data.floor.color);
}
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


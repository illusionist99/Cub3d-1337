#include "libcub3d.h"

float   ft_normalizeAngle(float *angle)
{
    *angle = fmod(*angle, 2 * M_PI);
    if (*angle < 0)
        *angle = (2 * M_PI) + *angle;
    return (*angle);
}

float   ft_distance_beetwen_points(float x0, float y0, float x1, float y1)
{
    return (sqrt(pow(x1 - x0, 2) + pow(y1 - y0, 2)));
}

unsigned int rgb_to_int(unsigned int r, unsigned int g, unsigned int b)
{
    int c = r;

    c = (c << 8) | g;
    c = (c << 8) | b;
    return c;
}

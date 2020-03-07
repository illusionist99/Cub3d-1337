#include "libcub3d.h"

float   ft_normalizeAngle(float *angle)
{
    *angle = fmod(*angle, 2 * M_PI);
    if (*angle < 0)
        *angle = (2 * M_PI) + *angle;
    return (*angle);
}

unsigned int rgb_to_int(unsigned int r, unsigned int g, unsigned int b)
{
    int c = r;

    c = (c << 8) | g;
    c = (c << 8) | b;
    return (c);
}

void    init_ray()
{
	ray.down = 0;
	ray.up = 0;
	ray.right = 0;
	ray.left = 0;
}

void    RayFacing(float angle)
{
	init_ray();
	ray.down = (angle > 0 && angle < M_PI);
	ray.up = !ray.down;
	ray.right = (angle < 0.5 * M_PI || angle > 1.5 * M_PI);
	ray.left = !ray.right;
}


float   ft_distanceBetweenPoints(float x1, float y1, float x2, float y2) 
{ 
    return sqrt(pow(x2 - x1, 2) +  pow(y2 - y1, 2)); 
}

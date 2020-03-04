#include "libcub3d.h"

void    ft_image_settings()
{
    image.ptr = mlx_new_image(mlx.mlx, data.Width, data.Height);
    image.data = (int *)mlx_get_data_addr(image.ptr, &(image.bits_per_pixel), &(image.size_line), &(image.endian));
}
#include "libcub3d.h"

void    ft_image_settings()
{
    image.ptr = mlx_new_image(mlx.mlx, data.Width, data.Height);
    image.data = (int *)mlx_get_data_addr(image.ptr, &(image.bits_per_pixel), &(image.size_line), &(image.endian));
    
    // /* Wall Tetures */
    // int bits_per_pixel = 0;
    // int size_l = 0;
    // int end = 0;

    // data.img_px = mlx_xpm_file_to_image(data.mlx_ptr, "textures/bluestone.xpm", &data.img_w, &data.img_h);
    // data.img_id = (int *)mlx_get_data_addr(data.img_px, &bits_per_pixel, &size_l, &end);
    // int w = 0;
    // int h = 0;
    // int bi = 0;
    // int si = 0;
    // int en = 0;
    // data.path.sky_xpm = mlx_xpm_file_to_image(data.mlx_ptr, "textures/wood.xpm", &w, &h);
    // data.path.sky_data = (int *)mlx_get_data_addr(data.path.sky_xpm, &bi, &si, &en);
}
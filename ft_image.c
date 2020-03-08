/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_image.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 16:57:48 by malaoui           #+#    #+#             */
/*   Updated: 2020/03/08 00:44:27 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcub3d.h"

void    ft_image_settings()
{
    image.ptr = mlx_new_image(mlx.mlx, data.Width, data.Height);
    image.data = (int *)mlx_get_data_addr(image.ptr, &(image.bits_per_pixel), &(image.size_line), &(image.endian));

    gun.ptr = mlx_xpm_file_to_image(mlx.mlx, "textures/gun0.xpm", &gun.width, &gun.height);
    gun.data = (int *)mlx_get_data_addr(image.ptr, &(gun.bits_per_pixel), &(gun.size_line), &(gun.endian));
}

void    get_text_data(void)
{
	north.ptr = mlx_xpm_file_to_image(mlx.mlx, data.Path.north,
			&north.width, &north.height);
	west.ptr = mlx_xpm_file_to_image(mlx.mlx, data.Path.west,
			&west.width, &west.height);
	south.ptr = mlx_xpm_file_to_image(mlx.mlx, data.Path.south,
			&south.width, &south.height);
	east.ptr = mlx_xpm_file_to_image(mlx.mlx, data.Path.east,
			&east.width, &east.height);
	sprite.ptr = mlx_xpm_file_to_image(mlx.mlx, data.Path.sprite,
			&sprite.width, &sprite.height);
}


void    init_textures(void)
{
    get_text_data();
	if (north.ptr && west.ptr && south.ptr && east.ptr && sprite.ptr)
	{
		north.data = (int *)mlx_get_data_addr(north.ptr, &north.bits_per_pixel,
				&north.size_line, &north.endian);
		west.data = (int *)mlx_get_data_addr(west.ptr, &west.bits_per_pixel,
				&west.size_line, &west.endian);
		south.data = (int *)mlx_get_data_addr(south.ptr, &south.bits_per_pixel,
				&south.size_line, &south.endian);
		east.data = (int *)mlx_get_data_addr(east.ptr, &east.bits_per_pixel,
				&east.size_line, &east.endian);
		sprite.data = (int *)mlx_get_data_addr(sprite.ptr, &sprite.bits_per_pixel,
				&sprite.size_line, &sprite.endian);
	}
	else
	{
		ft_printf("\033[31mInvalid Texture Path !\n\033[32mUsage : ./file.xpm\033[0m\n");
		exit(1);
	}
}
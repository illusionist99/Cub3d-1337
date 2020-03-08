/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_image.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 16:57:48 by malaoui           #+#    #+#             */
/*   Updated: 2020/03/08 10:16:21 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcub3d.h"

void		ft_image_settings(void)
{
	g_image.ptr = mlx_new_image(g_mlx.mlx, g_data.width, g_data.height);
	g_image.data = (int *)mlx_get_data_addr(g_image.ptr,
	&(g_image.bits_per_pixel), &(g_image.size_line), &(g_image.endian));
}

void		get_text_data(void)
{
	g_north.ptr = mlx_xpm_file_to_image(g_mlx.mlx, g_data.path.north,
			&g_north.width, &g_north.height);
	g_west.ptr = mlx_xpm_file_to_image(g_mlx.mlx, g_data.path.west,
			&g_west.width, &g_west.height);
	g_south.ptr = mlx_xpm_file_to_image(g_mlx.mlx, g_data.path.south,
			&g_south.width, &g_south.height);
	g_east.ptr = mlx_xpm_file_to_image(g_mlx.mlx, g_data.path.east,
			&g_east.width, &g_east.height);
	g_sprite.ptr = mlx_xpm_file_to_image(g_mlx.mlx, g_data.path.sprite,
			&g_sprite.width, &g_sprite.height);
}

void		init_textures(void)
{
	get_text_data();
	if (g_north.ptr && g_west.ptr && g_south.ptr && g_east.ptr && g_sprite.ptr)
	{
		g_north.data = (int *)mlx_get_data_addr(g_north.ptr,
		&g_north.bits_per_pixel,
				&g_north.size_line, &g_north.endian);
		g_west.data = (int *)mlx_get_data_addr(g_west.ptr,
		&g_west.bits_per_pixel,
				&g_west.size_line, &g_west.endian);
		g_south.data = (int *)mlx_get_data_addr(g_south.ptr,
		&g_south.bits_per_pixel,
				&g_south.size_line, &g_south.endian);
		g_east.data = (int *)mlx_get_data_addr(g_east.ptr,
		&g_east.bits_per_pixel,
				&g_east.size_line, &g_east.endian);
		g_sprite.data = (int *)mlx_get_data_addr(g_sprite.ptr,
		&g_sprite.bits_per_pixel,
				&g_sprite.size_line, &g_sprite.endian);
	}
	else
	{
		ft_printf("\033[31mInvalid Texture path \
!\n\033[32mUsage : ./file.xpm\033[0m\n");
		exit(1);
	}
}

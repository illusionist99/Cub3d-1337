/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_image.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 16:57:48 by malaoui           #+#    #+#             */
/*   Updated: 2020/03/09 12:49:43 by malaoui          ###   ########.fr       */
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
		ft_free(0, "\033[31mInvalid Texture path \
		\033[32mUsage : ./file.xpm");
}

void		ft_free(int n, char *s)
{
	ft_free_map(n, s);
	if (g_north.ptr)
		ft_free_struct(&g_north);
	if (g_west.ptr)
		ft_free_struct(&g_west);
	if (g_south.ptr)
		ft_free_struct(&g_south);
	if (g_east.ptr)
		ft_free_struct(&g_east);
	if (g_sprite.ptr)
		ft_free_struct(&g_sprite);
	ft_free_sprites(&(g_data.path));
	system(ft_strjoin("kill ", ft_itoa(g_child)));
	exit(1);
}

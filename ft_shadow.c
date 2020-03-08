/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shadow.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 14:13:11 by malaoui           #+#    #+#             */
/*   Updated: 2020/03/08 14:35:32 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcub3d.h"

unsigned int		shadow(int color, int col)
{
	t_color			shadow;
	float			fact;
	unsigned int	dark;

	fact = 250 / g_ray_distance[col];
	shadow.r = (((color >> 16) & 0xFF)) * fact;
	shadow.g = (((color >> 8) & 0xFF)) * fact;
	shadow.b = ((color) & (0xFF)) * fact;
	dark = rgb_to_int(shadow.r, shadow.g, shadow.b);
	if (dark > color)
		dark = color;
	return (dark);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ray.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 21:01:05 by malaoui           #+#    #+#             */
/*   Updated: 2020/03/09 16:24:07 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcub3d.h"

float			ft_normalizeangle(float *angle)
{
	*angle = fmod(*angle, 2 * M_PI);
	if (*angle < 0)
		*angle = (2 * M_PI) + *angle;
	return (*angle);
}

unsigned int	rgb_to_int(unsigned int r, unsigned int g, unsigned int b)
{
	int c;

	c = r;
	c = (c << 8) | g;
	c = (c << 8) | b;
	return (c);
}

void			init_ray(void)
{
	g_ray.down = 0;
	g_ray.up = 0;
	g_ray.right = 0;
	g_ray.left = 0;
}

void			rayfacing(float angle)
{
	init_ray();
	g_ray.down = (angle > 0 && angle < M_PI);
	g_ray.up = !g_ray.down;
	g_ray.right = (angle < 0.5 * M_PI || angle > 1.5 * M_PI);
	g_ray.left = !g_ray.right;
}

float			ft_distancebetweenpoints(float x1, float y1, float x2, float y2)
{
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

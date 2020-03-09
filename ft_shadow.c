/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shadow.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 14:13:11 by malaoui           #+#    #+#             */
/*   Updated: 2020/03/09 17:57:47 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcub3d.h"

unsigned int		shadow(unsigned int color, int col)
{
	t_color			shadow;
	float			fact;
	unsigned int	dark;

	fact = 200 / g_ray_distance[col];
	shadow.r = (((color >> 16) & 0xFF)) * fact;
	shadow.g = (((color >> 8) & 0xFF)) * fact;
	shadow.b = ((color) & (0xFF)) * fact;
	dark = rgb_to_int(shadow.r, shadow.g, shadow.b);
	if (dark > color)
		dark = color;
	return (dark);
}

int					ft_check_name(char *s)
{
	if (ft_strnstr(s, ".cub", ft_strlen(s)) == NULL)
		return (1);
	else
		return (0);
}

int					ft_check_for_error(char *s, int m_index)
{
	int i;

	i = 1;
	while (s[i] != '\0')
	{
		if (s[i] == ' ')
		{
			if (g_data.map[m_index - 1][i] == ' ' ||
			g_data.map[m_index + 1][i] == ' '
			|| g_data.map[m_index][i - 1] == ' '
			|| g_data.map[m_index][i + 1] == ' ')
				return (-1);
		}
		i++;
	}
	return (1);
}

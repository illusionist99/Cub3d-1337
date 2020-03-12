/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shadow.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 14:13:11 by malaoui           #+#    #+#             */
/*   Updated: 2020/03/13 00:30:40 by malaoui          ###   ########.fr       */
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

int					ft_check_str(char *s)
{
	int i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != ' ' && s[i] != '0' && s[i] != '1' &&
		s[i] != 'N' && s[i] != 'S' && s[i] != 'E'
		&& s[i] != 'W' && s[i] != '2')
			return (-1);
		else
			i++;
	}
	return (1);
}

int					ft_check_name(char *s)
{
	if (ft_strnstr(s, ".cub", ft_strlen(s)) == NULL)
		return (1);
	else
		return (0);
}

int					ft_hasspace(int m_index)
{
	if (g_data.map[m_index][0] != ' ')
		return (1);
	return (0);
}

int					ft_check_for_error(char *s, int m_index)
{
	int i;
	int m_index_len;

	i = 1;
	m_index_len = ft_strlen(g_data.map[m_index]);
	while (s[i] != '\0' && ft_hasspace(m_index))
	{
		if (s[i] == ' ' && m_index < g_data.nb_of_rows)
		{
			if (g_data.map[m_index - 1][i] == ' ' ||
			g_data.map[m_index + 1][i] == ' '
			|| g_data.map[m_index][i - 1] == ' '
			|| g_data.map[m_index][i + 1] == ' ')
				return (-1);
		}
		if (s[i] == '0')
		{
			if (g_data.map[m_index - 1][i] == ' ' ||
			g_data.map[m_index + 1][i] == ' ')
				return (-1);
		}
		i++;
	}
	return (1);
}

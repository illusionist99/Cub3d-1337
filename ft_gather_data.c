/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gather_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 17:06:06 by malaoui           #+#    #+#             */
/*   Updated: 2020/03/08 10:16:21 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcub3d.h"

void		ft_resolution(char *str)
{
	int		i;

	i = 0;
	if (str[i] == 'R')
	{
		i++;
		while (str[i] == ' ')
			i++;
		g_data.width = atoi(&str[i]);
		while (ft_isdigit(str[i]))
			i++;
		while (str[i] == ' ')
			i++;
		g_data.height = atoi(&str[i]);
	}
	if (g_data.height <= 0 || g_data.width <= 0)
	{
		ft_printf("\033[31mInvalid Resolution!\033[0m\n");
		exit(1);
	}
	g_data.height = (g_data.height > 1440) ? 1440 : g_data.height;
	g_data.width = (g_data.width > 2560) ? 2560 : g_data.width;
}

void		ft_sprite_path(char *str)
{
	int		i;

	i = 0;
	if (str[i] == 'S')
	{
		i++;
		while (str[i] == ' ' || str[i] == '/' || str[i] == '.')
			i++;
		g_data.path.sprite = ft_strdup(str + i);
	}
}

int			ft_get_map(char *str)
{
	g_data.map[g_data.index] = ft_check_map(str);
	g_data.index++;
	return (1);
}

int			ft_analyse(char *str)
{
	int		i;

	i = 0;
	if (str[i] == 'R')
		ft_resolution(str + i);
	else if (str[i] == 'F')
		ft_floor(str + i + 1);
	else if (str[i] == 'C')
		ft_c(str + i + 1);
	else if (ft_memcmp(str, "NO", 2) == 0)
		g_data.path.north = ft_substr(str, 5, ft_strlen(str + 3));
	else if (ft_memcmp(str, "SO", 2) == 0)
		g_data.path.south = ft_substr(str, 5, ft_strlen(str + 3));
	else if (ft_memcmp(str, "WE", 2) == 0)
		g_data.path.west = ft_substr(str, 5, ft_strlen(str + 3));
	else if (ft_memcmp(str, "EA", 2) == 0)
		g_data.path.east = ft_substr(str, 5, ft_strlen(str + 3));
	else if (str[i] == 'S')
		ft_sprite_path(str + i);
	else if (ft_isdigit(str[i]) || str[i] == ' ')
		if (ft_get_map(str) != 1)
			return (EXIT_FAILURE);
	if (g_data.width == 0 || g_data.height == 0)
		return (0);
	return (1);
}

int			ft_read_map(char **str)
{
	int		fd;
	char	*line;

	line = NULL;
	if (ft_strnstr(*str, ".cub", ft_strlen(*str)) != NULL)
		fd = open(str[0], O_RDONLY);
	else
		return (0);
	while ((get_next_line(fd, &line) == 1))
		ft_analyse(line);
	g_data.cols = ft_strlen(g_data.map[0]);
	free(line);
	g_data.map[g_data.index + 1] = NULL;
	return (1);
}

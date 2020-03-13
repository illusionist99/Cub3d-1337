/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gather_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 17:06:06 by malaoui           #+#    #+#             */
/*   Updated: 2020/03/13 14:31:07 by malaoui          ###   ########.fr       */
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
		while (ft_isdigit(str[i]))
			i++;
		while (str[i] == ' ')
			i++;
		if (ft_isdigit(str[i]))
			ft_free(-1, "INVALID RESOLUTION");
	}
	if (g_data.height <= 0 || g_data.width <= 0)
		ft_free(0, "Invalid Resolution !");
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
	if (ft_isdigit(str[0]) || str[0] == ' ')
	{
		if (ft_check_str(str) == 1)
		{
			g_data.map[g_data.index] = ft_strdup(str);
			g_data.index++;
		}
		else
			ft_free(g_data.index, "INVALID CHAR AT MAP");
	}
	else
	{
		g_data.map[g_data.index] = ft_strdup(str);
		g_data.index++;
	}
	return (1);
}

int			ft_analyse(char *str)
{
	if (str[0] == 'R' && !g_order)
		ft_resolution(str);
	else if (str[0] == 'F' && str[1] == ' ' && !g_order)
		ft_floor(str + 1);
	else if (str[0] == 'C' && str[1] == ' ' && !g_order)
		ft_c(str + 1);
	else if ((ft_memcmp(str, "NO", 2) == 0) && !g_order)
		g_data.path.north = ft_substr(str, 5, ft_strlen(str + 3));
	else if ((ft_memcmp(str, "SO", 2) == 0) && !g_order)
		g_data.path.south = ft_substr(str, 5, ft_strlen(str + 3));
	else if ((ft_memcmp(str, "WE", 2) == 0) && !g_order)
		g_data.path.west = ft_substr(str, 5, ft_strlen(str + 3));
	else if ((ft_memcmp(str, "EA", 2) == 0) && !g_order)
		g_data.path.east = ft_substr(str, 5, ft_strlen(str + 3));
	else if (str[0] == 'S' && str[1] == ' ' && !g_order)
		ft_sprite_path(str);
	else if (ft_isdigit(str[0]) || str[0] == ' ')
	{
		g_order = 1;
		if (ft_get_map(str) != 1)
			return (-1);
	}
	else if (ft_isalpha(*str))
		ft_free(-1, ft_strjoin("Invalid Argument in file --> ", str));
	return (1);
}

int			ft_read_map(char **str)
{
	int		fd;
	char	*line;

	line = NULL;
	if (ft_strnstr(*str, ".cub", ft_strlen(*str)) != NULL)
	{
		fd = open(str[0], O_RDONLY);
		if (fd == -1)
			ft_free(-1, "FILE NOT VALID");
		if (ft_check_name(ft_strtrim(str[0], ".cub")) != 1)
			ft_free(-1, "NOT A VALID FILE");
	}
	else
		return (0);
	while ((get_next_line(fd, &line) == 1))
	{
		ft_analyse(line);
		free(line);
	}
	g_data.cols = ft_strlen(g_data.map[0]);
	free(line);
	g_data.map[g_data.index + 1] = NULL;
	ft_check_maze();
	return (1);
}

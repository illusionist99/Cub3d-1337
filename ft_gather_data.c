/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gather_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 17:06:06 by malaoui           #+#    #+#             */
/*   Updated: 2020/03/08 07:04:04 by malaoui          ###   ########.fr       */
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
		data.Width = atoi(&str[i]);
		while (ft_isdigit(str[i]))
			i++;
		while (str[i] == ' ')
			i++;
		data.Height = atoi(&str[i]);
	}
	if (data.Height <= 0 || data.Width <= 0)
	{
		ft_printf("\033[31mInvalid Resolution!\033[0m\n");
		exit(1);
	}
	data.Height = (data.Height > 1440) ? 1440 : data.Height;
	data.Width = (data.Width > 2560) ? 2560 : data.Width;
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
		data.Path.sprite = ft_strdup(str + i);
	}
}

void		ft_floor(char *str)
{
	int		i;

	i = 0;
	while (str[i] == ' ')
		i++;
	data.floor.r = ft_atoi(str + i);
	while (ft_isdigit(str[i]) || str[i] == ' ')
		i++;
	while (str[i] == ',')
		i++;
	data.floor.g = ft_atoi(str + i);
	while (ft_isdigit(str[i]) || str[i] == ' ')
		i++;
	while (str[i] == ',')
		i++;
	data.floor.b = ft_atoi(str + i);
	if ((data.floor.r < 0 || data.floor.r > 256)
	&& (data.floor.g < 0 || data.floor.g > 256) &&
		(data.floor.b < 0 || data.floor.b > 256))
	{
		ft_printf("\033[31mInvalid floor RGB Color !\033[0m\n");
		exit(1);
	}
	else
		data.floor.color = rgb_to_int(data.floor.r, data.floor.g, data.floor.b);
}

void		ft_ceilling(char *str)
{
	int		i;

	i = 0;
	while (str[i] == ' ')
		i++;
	data.c.r = ft_atoi(str + i);
	while (ft_isdigit(str[i]) || str[i] == ' ')
		i++;
	if (str[i] == ',')
		i++;
	data.c.g = ft_atoi(str + i);
	while (ft_isdigit(str[i]) || str[i] == ' ')
		i++;
	if (str[i] == ',')
		i++;
	data.c.b = ft_atoi(str + i);
	if ((data.c.r < 0 || data.c.r > 256)
	&& (data.c.g < 0 || data.c.g > 256) &&
		(data.c.b < 0 || data.c.b > 256))
	{
		ft_printf("\033[31mInvalid c RGB Color !\033[0m\n");
		exit(1);
	}
	else
		data.c.color = rgb_to_int(data.c.r, data.c.g, data.c.b);
}

char		*ft_check_map(char *str)
{
	int		i;
	int		cpt;
	char	*s;
	int		o;

	cpt = 0;
	i = 0;
	o = 0;
	s = NULL;
	while (str[i] != '\0')
		i++;
	s = (char *)malloc(sizeof(char ) * i + 1);
	i = 0;
	while (str[i] != '\0')
	{
		s[o] = str[i];
		o++;
		i++;
	}
	s[o] = '\0';
	return (s);
}

int			ft_get_map(char *str)
{
	data.map[data.index] = ft_check_map(str);
	data.index++;
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
		data.Path.north = ft_substr(str, 5, ft_strlen(str + 3));
	else if (ft_memcmp(str, "SO", 2) == 0)
		data.Path.south = ft_substr(str, 5, ft_strlen(str + 3));
	else if (ft_memcmp(str, "WE", 2) == 0)
		data.Path.west = ft_substr(str, 5, ft_strlen(str + 3));
	else if (ft_memcmp(str, "EA", 2) == 0)
		data.Path.east = ft_substr(str, 5, ft_strlen(str + 3));
	else if (str[i] == 'S')
		ft_sprite_path(str + i);
	else if (ft_isdigit(str[i]) || str[i] == ' ')
		if (ft_get_map(str) != 1)
			return (EXIT_FAILURE);
	if (data.Width == 0 || data.Height == 0)
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
	data.cols = ft_strlen(data.map[0]);
	free(line);
	data.map[data.index + 1] = NULL;
	return (1);
}

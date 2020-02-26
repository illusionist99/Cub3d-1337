/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gather_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 17:06:06 by malaoui           #+#    #+#             */
/*   Updated: 2020/02/26 16:18:45 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcub3d.h"

void    ft_resolution(char *str)
{
    int i;

    i = 0;
    if (str[i] == 'R')
    {
        i++;
        data.Width = atoi(&str[i]);
        i++;
        data.Height = atoi(&str[i]);
    }
}

void    ft_sprite_path(char *str)
{
    int i;

    i = 0;
    if (str[i] == 'S')
    {
        i++;
        data.Path.sprite = ft_strdup(str + i);
    }
}

void    ft_floor(char *str)
{
    int i;

    i = 0;
    data.floor.r = ft_atoi(str + i);
    while (ft_isdigit(str[i]) || str[i] == ' ')
        i++;
    if (str[i] == ',')
        i++;
    data.floor.g = ft_atoi(str + i);
    while (ft_isdigit(str[i]) || str[i] == ' ')
        i++;
    if (str[i] == ',')
        i++;
    data.floor.b = ft_atoi(str + i);
    data.floor.color = rgb_to_int(data.floor.r, data.floor.g, data.floor.b);
}

void    ft_ceilling(char *str)
{
    int i;

    i = 0;
    data.ceilling.r = ft_atoi(str + i);
    while (ft_isdigit(str[i]) || str[i] == ' ')
        i++;
    if (str[i] == ',')
        i++;
    data.ceilling.g = ft_atoi(str + i);
    while (ft_isdigit(str[i]) || str[i] == ' ')
        i++;
    if (str[i] == ',')
        i++;
    data.ceilling.b = ft_atoi(str + i);
    data.ceilling.color = rgb_to_int(data.ceilling.r, data.ceilling.g, data.ceilling.b);
}

char    *ft_check_map(char *str)
{
    int i;
    int cpt;
    char *s;
    int o;

    cpt  = 0;
    i = 0;
    o = 0;
    s = NULL;
    while (str[i] != '\0')
    {
        if (str[i] == ' ')
            i++;
        else
        {    cpt++;
            i++;
        }
    }
    i = 0;
    s = (char *)malloc(sizeof(char ) * cpt + 1);
    while (str[i] != '\0')
    {
        if (str[i] == ' ')
            i++;
        else
        {
            s[o] = str[i];
            o++;
            i++;
        }
    }
    s[o] = '\0';
    return (s);
}

int   ft_get_map(char *str)
{
    data.map[data.index] = ft_check_map(str);
    data.index++;
    return (1);
}

int     ft_analyse(char *str)
{
    int i;

    i = 0;
    if (str[i] == 'R')
        ft_resolution(str + i);
    else if (str[i] == 'S')
        ft_sprite_path(str + i);
    else if (str[i] == 'F')
        ft_floor(str + i + 1);
    else if (str[i] == 'C')
        ft_ceilling(str + i + 1);
    else if (ft_memcmp(str, "NO", 2) == 0)
        data.Path.north = ft_substr(str, 3, ft_strlen(str));
    else if (ft_memcmp(str, "SO", 2) == 0)
        data.Path.sprite = ft_substr(str, 3, ft_strlen(str));
    else if (ft_memcmp(str, "WE", 2) == 0)
        data.Path.west = ft_substr(str, 3, ft_strlen(str));
    else if (ft_memcmp(str, "EA", 2) == 0)
        data.Path.east = ft_substr(str, 3, ft_strlen(str));
    else if (ft_isdigit(str[i]))
        if (ft_get_map(str) != 1)
            return (EXIT_FAILURE);   
    if (data.Width == 0 || data.Height == 0)
        return (0);
    return (1);
}

int    ft_read_map(char **str)
{
    int     fd;
    char    *line;

    line = NULL;
    fd = open(str[0], O_RDONLY);
    while ((get_next_line(fd, &line) == 1))
        ft_analyse(line);
    data.cols = ft_strlen(data.map[0]);
    free(line);
    data.map[data.index + 1] = NULL;
    return (1);
}

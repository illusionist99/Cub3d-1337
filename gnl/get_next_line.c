/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 18:35:20 by malaoui           #+#    #+#             */
/*   Updated: 2019/10/30 10:04:23 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_dojobandfree(char **str, char **line)
{
	char	*tmp;

	if (*str)
		if (ft_checkin(*str, line, ft_strlen(*str)) == 1)
		{
			tmp = *str;
			tmp = ft_store(*str);
			free(*str);
			*str = tmp;
			return (1);
		}
	return (0);
}

static int	ft_dojobfree(char **buff, char **line, char **str, int rd)
{
	if (ft_checkin(*buff, line, rd) == 1)
	{
		*str = ft_store(*buff);
		free(*buff);
		return (1);
	}
	return (0);
}

int			get_next_line(int fd, char **line)
{
	static char	*str;
	char		*buff;
	int			rd;

	*line = ft_add(NULL, NULL, 0);
	if (ft_checkerror(fd, line, &buff) == -1)
		return (-1);
	if (str)
		if (ft_dojobandfree(&str, line) == 1)
		{
			free(buff);
			return (1);
		}
	free(str);
	str = NULL;
	while ((rd = read(fd, buff, BUFFER_SIZE)))
	{
		if (rd == -1)
			return (-1);
		if (ft_dojobfree(&buff, line, &str, rd) == 1)
			return (1);
	}
	free(buff);
	return (0);
}

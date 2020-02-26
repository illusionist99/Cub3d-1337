/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 18:36:49 by malaoui           #+#    #+#             */
/*   Updated: 2019/10/30 10:04:28 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int			ft_checkerror(int fd, char **line, char **buff)
{
	if (fd < 0 || line == NULL || BUFFER_SIZE > 2147483647
			|| BUFFER_SIZE < 1)
		return (-1);
	if (!(*buff = (char *)malloc(sizeof(char *) * (BUFFER_SIZE + 1))))
		return (-1);
	return (0);
}

size_t		ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char		*ft_add(char *s1, char *s2, int len)
{
	char	*str;
	size_t	s1_l;
	size_t	i;

	i = 0;
	if (s1 != NULL)
		s1_l = ft_strlen(s1);
	else
		s1_l = 0;
	if (!(str = (char *)malloc(sizeof(char) * (s1_l + len + 1))))
		return (NULL);
	while (i < s1_l)
	{
		str[i] = s1[i];
		i++;
	}
	if (s1)
		free(s1);
	while (i < len + s1_l)
	{
		str[i] = s2[i - s1_l];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int			ft_checkin(char *s, char **line, int rd)
{
	int		i;

	i = 0;
	if (s != NULL)
	{
		s[rd] = '\0';
		while (s[i] != '\n' && s[i] != '\0')
			i++;
		if (s[i] == '\0')
		{
			*line = ft_add(*line, s, i);
		}
		if (s[i] == '\n')
		{
			*line = ft_add(*line, s, i);
			return (1);
		}
	}
	return (0);
}

char		*ft_store(char *s)
{
	int		i;

	i = 0;
	if (s != NULL)
	{
		while (s[i] != '\n' && s[i] != '\0')
			i++;
		if (s[i] == '\n')
		{
			s = ft_add(NULL, s + i + 1, ft_strlen(s + i + 1));
			return (s);
		}
	}
	return (NULL);
}

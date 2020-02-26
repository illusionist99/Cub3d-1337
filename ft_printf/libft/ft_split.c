/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 19:49:15 by malaoui           #+#    #+#             */
/*   Updated: 2019/10/21 20:43:16 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t		ft_countw(char *s, char c)
{
	size_t i;
	size_t flag;
	size_t cpt;

	flag = 1;
	i = 0;
	cpt = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			flag = 1;
		else if (flag == 1)
		{
			flag = 0;
			cpt++;
		}
		i++;
	}
	return (cpt);
}

static size_t		ft_wlen(char *s, char c)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (s[i] != c && s[i] != '\0')
	{
		i++;
		len++;
	}
	return (len);
}

static char			**ft_free(char **f, size_t j)
{
	size_t i;

	i = 0;
	while (i < j)
		free(f[i++]);
	free(f);
	return (NULL);
}

char				**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	countw;
	char	**p;
	size_t	j;
	size_t	l_count;

	i = 0;
	j = 0;
	l_count = 0;
	countw = ft_countw((char *)s, c);
	if (!(p = (char **)malloc(sizeof(char *) * (countw + 1))))
		return (NULL);
	while (i < countw)
	{
		while (s[j] == c)
			j++;
		l_count = ft_wlen((char *)s + j, c);
		p[i] = ft_substr(s, j, l_count);
		if (!p)
			return (ft_free(p, i));
		i++;
		j += l_count + 1;
	}
	p[countw] = NULL;
	return (p);
}

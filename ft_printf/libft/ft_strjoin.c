/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 00:47:23 by malaoui           #+#    #+#             */
/*   Updated: 2019/10/11 16:46:12 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	size_t	s1_l;
	size_t	set_l;
	char	*str;

	i = 0;
	j = 0;
	s1_l = ft_strlen(s1);
	set_l = ft_strlen(set);
	if (!(str = (char *)malloc(sizeof(char) * (s1_l + set_l + 1))))
		return (NULL);
	while (i < s1_l)
	{
		str[i] = s1[i];
		i++;
	}
	while (j < set_l)
	{
		str[i + j] = set[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

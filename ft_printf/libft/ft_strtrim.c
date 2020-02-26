/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 00:41:05 by malaoui           #+#    #+#             */
/*   Updated: 2019/10/21 17:20:32 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_trimmedalloc(char *s, char const *set)
{
	size_t	v_left;
	size_t	v_right;
	size_t	len;
	char	*p;
	size_t	d;

	d = 0;
	v_left = 0;
	len = 0;
	p = NULL;
	while (s[v_left] != '\0' && ft_strchr(set, s[v_left]))
		v_left++;
	v_right = ft_strlen(s);
	while (v_right > v_left && ft_strchr(set, s[v_right]))
		v_right--;
	len = v_right - v_left + 1;
	if (!(p = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (v_left <= v_right)
	{
		p[d++] = s[v_left++];
	}
	p[d] = '\0';
	return (p);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	char	*trimmed;

	i = 0;
	trimmed = ft_trimmedalloc((char *)s1, set);
	return (trimmed);
}

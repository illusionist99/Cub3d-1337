/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 18:56:46 by malaoui           #+#    #+#             */
/*   Updated: 2019/10/13 23:04:43 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	dest_l;
	size_t	src_l;

	i = 0;
	dest_l = ft_strlen(dest);
	src_l = ft_strlen(src);
	if (dest_l < n)
	{
		while (i < n - dest_l - 1 && i < src_l)
		{
			dest[dest_l + i] = src[i];
			i++;
		}
		dest[dest_l + i] = '\0';
		return (dest_l + src_l);
	}
	return (n + src_l);
}

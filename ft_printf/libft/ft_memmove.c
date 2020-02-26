/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 15:48:28 by malaoui           #+#    #+#             */
/*   Updated: 2019/10/17 17:00:10 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*p1;
	char		*p2;

	i = 0;
	p1 = (char *)dest;
	p2 = (char *)src;
	if (p2 < p1)
	{
		while (n--)
			p1[n] = p2[n];
	}
	else
		ft_memcpy(dest, src, n);
	return (dest);
}

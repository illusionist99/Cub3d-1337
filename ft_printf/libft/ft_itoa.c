/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 22:02:23 by malaoui           #+#    #+#             */
/*   Updated: 2019/11/23 21:57:06 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static char				*ft_strrev(char *str)
{
	size_t	i;
	char	temp;
	size_t	str_len;

	i = 0;
	str_len = ft_strlen(str);
	while (i < (str_len / 2))
	{
		temp = str[i];
		str[i] = str[str_len - i - 1];
		str[str_len - i - 1] = temp;
		i++;
	}
	return (str);
}

size_t					ft_msize(long long nb)
{
	size_t			ms;
	unsigned int	nbr;

	ms = 0;
	nbr = 0;
	if (nb < 0)
		nbr = -nb;
	else
		nbr = nb;
	while (nbr)
	{
		nbr /= 10;
		ms++;
	}
	return (ms);
}

static char				*ft_size(long long nb)
{
	size_t			len;
	char			*str;
	size_t			addl;

	addl = 0;
	len = ft_msize(nb);
	if (nb <= 0)
		addl++;
	if (!(str = (char *)malloc(sizeof(char) * (len + 1 + addl))))
		return (NULL);
	return (str);
}

static char				*ft_cpy(char *str, long long nb)
{
	size_t			i;
	unsigned int	nbr;
	size_t			len;

	len = ft_msize(nb);
	i = 0;
	nbr = (nb > 0) ? nb : (nb * (-1));
	if (nb == 0)
		len++;
	while (i < len)
	{
		str[i] = (nbr % 10) + '0';
		nbr /= 10;
		i++;
	}
	if (nb < 0)
	{
		str[i] = '-';
		str[i + 1] = '\0';
	}
	else
		str[i] = '\0';
	return (ft_strrev(str));
}

char					*ft_itoa(long long n)
{
	char		*str;

	str = ft_size(n);
	if (!str)
		return (NULL);
	return (ft_cpy(str, n));
}

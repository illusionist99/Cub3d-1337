/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_//printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 15:19:51 by malaoui           #+#    #+#             */
/*   Updated: 2019/11/24 00:57:16 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void		ft_handle_percent(int *i, int *cpt)
{
	ft_putchar_fd('%', 1);
	*i += 2;
	*cpt += 1;
}

void		ft_handle_printable(int *cpt, char text)
{
	ft_putchar_fd(text, 1);
	*cpt += 1;
}

int			ft_printf(const char *s, ...)
{
	int		i;
	va_list	list;
	int		cpt;
	int		j;

	va_start(list, s);
	i = 0;
	j = 0;
	cpt = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '%' && s[i + 1] == '%')
			ft_handle_percent(&i, &cpt);
		else if (s[i] == '%')
		{
			i++;
			cpt += ft_manage((char *)(s + i), &i, list);
		}
		else
			ft_handle_printable(&cpt, s[i++]);
	}
	va_end(list);
	return (cpt);
}

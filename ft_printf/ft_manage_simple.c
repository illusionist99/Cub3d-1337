/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_simple.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 22:27:58 by malaoui           #+#    #+#             */
/*   Updated: 2020/03/04 17:23:54 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

extern char g_conv;

char		ft_search_conv(const char *s)
{
	int i;

	i = 0;
	while ((ft_isdigit(s[i]) || s[i] == 42 || s[i] == '.' ||
				s[i] == '0' || s[i] == '-') && s[i] != '\0')
		i++;
	return (s[i]);
}

int			ft_rem(t_combo *foo, char *p, int len)
{
	if (foo->width == 0 && foo->precision == 0 && p[0] == '0')
		return (0);
	else
		ft_putstr_fd(p, 1);
	return (len);
}

int			ft_manage_simple(va_list list)
{
	if (g_conv == 'c')
		return (ft_manage_simple_c(list));
	else if (g_conv == 'p')
		return (ft_manage_simple_p(list));
	else if (g_conv == 's')
		return (ft_manage_simple_s(list));
	else if (g_conv == 'd' || g_conv == 'i')
		return (ft_manage_simple_di(list));
	else if (g_conv == 'x')
		return (ft_manage_simple_x(list));
	else if (g_conv == 'X')
		return (ft_manage_simple_xx(list));
	else if (g_conv == 'u')
		return (ft_manage_simple_u(list));
	return (0);
}

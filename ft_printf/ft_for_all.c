/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_for_all.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 16:29:07 by malaoui           #+#    #+#             */
/*   Updated: 2020/03/04 17:23:54 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char g_conv;

int			ft_for_else(char *s, int *pos, t_combo *foo, va_list list)
{
	int j;

	j = ft_calcul_width_precision(s, foo, list);
	*pos += j + 1;
	if (foo->width < 0)
	{
		foo->width *= -1;
		return (ft_flag_minus(foo, list));
	}
	else if (foo->flag == 1 && foo->precision == 0)
		return (ft_no_flag(foo, list));
	else
		return (ft_flag_zero(foo, list));
	return (0);
}

int			ft_for_norm(char *s, int *pos, t_combo *foo, va_list list)
{
	int j;

	j = ft_calcul_width_precision(s, foo, list);
	*pos += j + 1;
	if (foo->width < 0)
	{
		foo->width *= -1;
		return (ft_flag_minus(foo, list));
	}
	else
		return (ft_no_flag(foo, list));
	return (0);
}

int			ft_simple_conv(va_list list, int *pos)
{
	*pos += 1;
	return (ft_manage_simple(list));
}

int			ft_return(char *s, va_list list, int *pos, t_combo *foo)
{
	int i;

	i = 0;
	while (s[i] == '0' && s[i] != '\0')
		i++;
	if (s[i] == '-')
	{
		i--;
		return (ft_for_minus((char *)s + i, list, foo, pos));
	}
	else
	{
		*pos += i;
		return (ft_for_else((char *)s + i, pos, foo, list));
	}
	return (0);
}

int			ft_manage(const char *s, int *pos, va_list list)
{
	int		i;
	t_combo	foo;

	i = 0;
	g_conv = ft_search_conv(s);
	ft_init(&foo);
	if (s[i] == '-' && g_conv != '%')
		return (ft_for_minus((char *)s + i, list, &foo, pos));
	else if (s[i] == '0' && g_conv != '%')
		return (ft_return((char *)s + i, list, pos, &foo));
	else if (((ft_isdigit(s[i]) || s[i] == 42 || s[i] == '.')) && g_conv != '%')
		return (ft_for_norm((char *)s + i, pos, &foo, list));
	else if (g_conv == '%')
		return (ft_percent_return((char *)s + i, pos, &foo, list));
	else if (g_conv == 'c' || g_conv == 's' || g_conv == 'p' || g_conv == 'x'
			|| g_conv == 'X' || g_conv == 'u' || g_conv == 'd' || g_conv == 'i')
		return (ft_simple_conv(list, pos));
	return (0);
}

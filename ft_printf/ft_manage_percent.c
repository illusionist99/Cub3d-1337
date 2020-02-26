/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_percent.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 16:24:50 by malaoui           #+#    #+#             */
/*   Updated: 2019/11/23 18:33:42 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

extern char g_conv;

int			ft_percent_minus(char *s, int *pos, t_combo *foo, va_list list)
{
	int		i;
	int		j;
	int		f;

	f = 0;
	i = 0;
	j = ft_calcul_width_precision(s + i, foo, list);
	if (foo->width < 0)
		foo->width *= -1;
	if (s[i] == '.' && s[i] != '\0')
		i++;
	if (s[i] == '%')
	{
		ft_putchar_fd('%', 1);
		*pos += i + 1;
		return (1);
	}
	ft_putchar_fd('%', 1);
	while (++f < foo->width)
		ft_putchar_fd(' ', 1);
	*pos += i + j + 1;
	return (f);
}

int			ft_percent_digit(char *s, int *pos, t_combo *foo, va_list list)
{
	int		i;
	int		j;
	int		f;

	f = 0;
	i = 0;
	j = ft_calcul_width_precision(s + i, foo, list);
	if (foo->width < 0)
		f = ft_handle_nwidth(foo, pos, i, j);
	else if (s[i] == '%')
	{
		ft_putchar_fd('%', 1);
		*pos += i + 1;
		f = 1;
	}
	else
	{
		while (++f < foo->width)
			ft_putchar_fd(' ', 1);
		ft_putchar_fd('%', 1);
		*pos += i + j + 1;
	}
	return (f);
}

int			ft_percent_zero(char *s, int *pos, t_combo *foo, va_list list)
{
	int		i;
	int		j;
	int		f;

	f = 0;
	i = 0;
	j = ft_calcul_width_precision(s + i, foo, list);
	if (foo->width < 0)
		return (ft_handle_nwidth(foo, pos, i, j));
	if (s[i] == '%')
	{
		ft_putchar_fd('%', 1);
		*pos += i + 1;
		return (1);
	}
	while (++f < foo->width)
		ft_putchar_fd('0', 1);
	ft_putchar_fd('%', 1);
	*pos += i + j + 1;
	return (f);
}

int			ft_percent_else(char *s, int *pos, t_combo *foo, va_list list)
{
	int		i;
	int		j;
	int		f;

	f = 0;
	i = 0;
	j = ft_calcul_width_precision(s + i, foo, list);
	if (foo->width < 0)
		foo->width *= -1;
	if (s[i] == '.' && s[i] != '\0')
		i++;
	if (s[i] == '%')
	{
		ft_putchar_fd('%', 1);
		*pos += i + 1;
		return (1);
	}
	ft_putchar_fd('%', 1);
	while (++f < foo->width)
		ft_putchar_fd(' ', 1);
	*pos += i + j;
	return (f);
}

int			ft_percent_return(char *s, int *pos, t_combo *foo, va_list list)
{
	int		i;

	i = 0;
	g_conv = 'c';
	if (s[i] == '-')
		return (ft_percent_minus((char *)s + 1, pos, foo, list));
	else if (s[i] == '0')
		return (ft_percent_zero((char *)s + 1, pos, foo, list));
	else if (ft_isdigit(s[i]) || s[i] == 42)
		return (ft_percent_digit((char *)s, pos, foo, list));
	else
		return (ft_percent_else((char *)s, pos, foo, list));
	return (0);
}

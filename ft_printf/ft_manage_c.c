/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_c.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 04:21:21 by malaoui           #+#    #+#             */
/*   Updated: 2019/11/21 04:51:03 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		ft_manage_minus_c(t_combo *foo, va_list list)
{
	int i;

	i = 0;
	if ((foo->cc) == 1)
		ft_putchar_fd('%', 1);
	else
		ft_putchar_fd(va_arg(list, int), 1);
	while (--(foo->width) > 0)
	{
		i++;
		ft_putchar_fd(' ', 1);
	}
	return (i + 1);
}

int		ft_manage_zero_c(t_combo *foo, va_list list)
{
	int i;

	i = 0;
	while (--(foo->width) > 0)
	{
		ft_putchar_fd('0', 1);
		i++;
	}
	if ((foo->cc) != 1)
		ft_putchar_fd(va_arg(list, int), 1);
	else
		ft_putchar_fd('%', 1);
	return (i + 1);
}

int		ft_manage_norm_c(t_combo *foo, va_list list)
{
	int i;

	i = 0;
	while (--(foo->width) > 0)
	{
		i++;
		ft_putchar_fd(' ', 1);
	}
	if ((foo->cc) != 1)
		ft_putchar_fd(va_arg(list, int), 1);
	else
		ft_putchar_fd('%', 1);
	return (i + 1);
}

int		ft_manage_simple_c(va_list list)
{
	ft_putchar_fd(va_arg(list, int), 1);
	return (1);
}

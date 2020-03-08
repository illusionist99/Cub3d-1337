/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_x_extended.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 05:46:06 by malaoui           #+#    #+#             */
/*   Updated: 2020/03/08 10:15:45 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	ft_manage_mx(t_combo *foo, char *p, int len)
{
	int j;

	j = 0;
	if (foo->width == 0 && len == 1)
		return (ft_rem(foo, p, len));
	while ((foo->width)-- > len)
	{
		j++;
		ft_putchar_fd(' ', 1);
	}
	while ((foo->precision)-- > len)
	{
		j++;
		ft_putchar_fd('0', 1);
	}
	if (foo->flag == 1 && p[0] == '0' && len == 1)
		ft_putchar_fd(' ', 1);
	else
		ft_putstr_fd(p, 1);
	free(p);
	return (j + len);
}

static int	ft_manage_mxp(t_combo *foo, char *p, int len)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (len > foo->precision)
		j = len;
	else
		j = foo->precision;
	while ((foo->width)-- > j)
	{
		i++;
		ft_putchar_fd(' ', 1);
	}
	while ((foo->precision)-- > len)
	{
		i++;
		ft_putchar_fd('0', 1);
	}
	if (((foo->flag) == 0) || ((ft_atoi(p) != 0)))
		ft_putstr_fd(p, 1);
	else if ((foo->width) != 0 && (foo->flag) == 1 && ft_atoi(p) == 0)
		ft_putchar_fd(' ', 1);
	free(p);
	return (i + len);
}

int			ft_manage_norm_x(t_combo *foo, va_list list)
{
	char	*p;
	int		i;
	int		j;
	int		len;

	j = 0;
	i = 0;
	p = ft_hex(va_arg(list, unsigned int));
	len = ft_strlen(p);
	if ((foo->precision) == 0)
		return (ft_manage_mx(foo, p, len));
	else
		return (ft_manage_mxp(foo, p, len));
	free(p);
	return (0);
}

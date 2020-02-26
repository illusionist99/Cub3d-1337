/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_uutils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 06:45:46 by malaoui           #+#    #+#             */
/*   Updated: 2019/11/24 00:58:19 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	ft_checku(t_combo *foo, char *p, int len)
{
	int		j;

	j = 0;
	if (foo->width == 0 && len == 1 && ft_atoi(p) == 0)
		return (0);
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
	if (((foo->flag) == 0) || ((ft_atoi(p) != 0)))
		ft_putstr_fd(p, 1);
	else if ((foo->flag == 1 && foo->flag == 1 && ft_atoi(p) == 0))
		ft_putchar_fd(' ', 1);
	free(p);
	return (j + len);
}

static int	ft_checkup(t_combo *foo, char *p, int len)
{
	int		j;
	int		i;

	j = 0;
	i = 0;
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

int			ft_manage_norm_u(t_combo *foo, va_list list)
{
	char	*p;
	int		len;

	p = ft_itoa(va_arg(list, unsigned int));
	len = ft_strlen(p);
	if ((foo->precision) == 0)
		return (ft_checku(foo, p, len));
	else
		return (ft_checkup(foo, p, len));
	free(p);
	return (0);
}

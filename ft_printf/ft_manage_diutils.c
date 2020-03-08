/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_diutils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 07:34:47 by malaoui           #+#    #+#             */
/*   Updated: 2020/03/08 10:15:45 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void		ft_checkz(t_combo *foo, int *i, int len, char *p)
{
	if (foo->precision == -1)
		foo->precision = 0;
	if ((foo->precision) == 0)
	{
		while (len < (foo->width))
		{
			ft_putchar_fd('0', 1);
			*i += 1;
			(foo->width)--;
		}
	}
	else
	{
		while (len < (foo->precision))
		{
			ft_putchar_fd('0', 1);
			*i += 1;
			(foo->precision)--;
		}
	}
	if (ft_atoi(p) != 0)
		ft_putstr_fd(p, 1);
	else
		ft_putchar_fd('0', 1);
}

int			ft_manage_zero_di(t_combo *foo, va_list list)
{
	char	*p;
	int		i;
	int		j;
	int		len;
	int		flag;

	flag = 0;
	j = 0;
	i = 0;
	p = ft_itoa(va_arg(list, int));
	len = ft_strlen(p);
	if (p[0] == '-')
	{
		ft_putchar_fd('-', 1);
		p = p + 1;
		i++;
		flag = -1;
	}
	ft_checkz(foo, &i, len, p);
	if (flag < 0)
		return (i + len - 1);
	else
		return (i + len);
}

static int	ft_checkndi(t_combo *foo, char *p, int len)
{
	int		i;
	int		j;

	i = 0;
	j = (foo->width);
	if (j == 0 && p[0] == '0' && len == 1 &&
foo->precision == 0 && foo->flag == 1)
		return (0);
	while (j-- > len)
	{
		ft_putchar_fd(' ', 1);
		i++;
	}
	if (p[0] == '-')
	{
		ft_putchar_fd('-', 1);
		p = p + 1;
	}
	if (((foo->flag) == 0) || ((ft_atoi(p) != 0) || (foo->precision != 0)))
		ft_putstr_fd(p, 1);
	else if (((foo->flag) == 1 || (ft_atoi(p) != 0)) && j != 0)
		i--;
	if ((foo->width) != 0 && (foo->flag) == 1 && ft_atoi(p) == 0)
		ft_putchar_fd(' ', 1);
	return (i + len);
}

int			ft_checknpdi(t_combo *foo, int *i, int j, char *p)
{
	int len;

	len = ft_strlen(p);
	while (foo->width-- > j)
	{
		*i += 1;
		ft_putchar_fd(' ', 1);
	}
	if (p[0] == '-')
		ft_handle_negative(foo, i, &p, &len);
	while ((foo->precision)-- > len)
	{
		ft_putchar_fd('0', 1);
		*i += 1;
	}
	if ((foo->flag) == 0)
		ft_putstr_fd(p, 1);
	else if ((foo->precision) > 0)
		ft_putchar_fd('0', 1);
	return (len);
}

int			ft_manage_norm_di(t_combo *foo, va_list list)
{
	char	*p;
	int		i;
	int		j;
	int		len;

	j = 0;
	i = 0;
	p = ft_itoa(va_arg(list, int));
	len = ft_strlen(p);
	if ((foo->precision) == 0 || foo->precision == -1)
		return (ft_checkndi(foo, p, len));
	else
	{
		if (len > foo->precision)
			j = len;
		else
			j = foo->precision;
		if (p[0] == '-' && len < foo->precision)
			j++;
		len = ft_checknpdi(foo, &i, j, p);
		return (i + len);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_di.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 04:31:48 by malaoui           #+#    #+#             */
/*   Updated: 2019/11/24 06:27:08 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	ft_checkmdi(t_combo *foo, char *p, int len)
{
	int		j;
	int		i;

	i = 0;
	j = (foo->width);
	if (p[0] == '-')
	{
		ft_putchar_fd('-', 1);
		p = p + 1;
	}
	ft_checkprint(foo, p, &i, j);
	if ((foo->width) != 0 && (foo->precision) == 0 &&
foo->flag == 1 && ft_atoi(p) == 0)
	{
		ft_putchar_fd(' ', 1);
		i++;
	}
	while (j-- > len)
	{
		ft_putchar_fd(' ', 1);
		i++;
	}
	return (i + len);
}

void		ft_checkm(t_combo *foo, char **p, int *len, int *i)
{
	int		j;

	j = 0;
	ft_putchar_fd('-', 1);
	*p = *p + 1;
	if ((foo->precision) < (foo->width))
	{
		(foo->precision)++;
		*i -= 1;
	}
	else
		*len -= 1;
	*i += 1;
}

static int	ft_checkmpdi(t_combo *foo, char *p, int len)
{
	int j;
	int i;

	i = 0;
	j = (foo->width);
	if ((foo->precision) < len)
		(foo->precision)++;
	if (p[0] == '-')
		ft_checkm(foo, &p, &len, &i);
	while ((foo->precision)-- > len)
		ft_add_to_print(&i, &j);
	ft_checkprint(foo, p, &i, j);
	if ((foo->width) != 0 && (foo->flag) == 1 && ft_atoi(p) == 0)
	{
		ft_putchar_fd(' ', 1);
		i--;
	}
	if (foo->precision == -1)
		return (ft_negprecision(&p, i, len));
	while (--j > (foo->precision))
	{
		i++;
		ft_putchar_fd(' ', 1);
	}
	return (i + len);
}

int			ft_manage_minus_di(t_combo *foo, va_list list)
{
	char	*p;
	int		len;
	int		j;

	j = 0;
	p = ft_itoa(va_arg(list, int));
	len = ft_strlen(p);
	if ((foo->precision) == 0 || foo->precision == -1)
		j = ft_checkmdi(foo, p, len);
	else
		j = ft_checkmpdi(foo, p, len);
	free(p);
	return (j);
}

int			ft_manage_simple_di(va_list list)
{
	char	*p;
	int		len;

	p = ft_itoa(va_arg(list, int));
	len = ft_strlen(p);
	ft_putstr_fd(p, 1);
	free(p);
	return (len);
}

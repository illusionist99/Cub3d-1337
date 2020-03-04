/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_s.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 04:25:25 by malaoui           #+#    #+#             */
/*   Updated: 2020/03/04 17:23:54 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	ft_checkminus(t_combo *foo, char *p, int len)
{
	int i;
	int j;

	i = 0;
	j = len;
	if ((foo->width) == 0 && foo->precision == 0 && foo->flag == 1)
		return (0);
	if (foo->precision == -1)
		foo->precision = 0;
	if ((foo->flag) == 1)
		j = 0;
	if ((foo->flag) != 1)
	{
		i += len;
		ft_putstr_fd(p, 1);
	}
	while (j < (foo->width))
	{
		ft_putchar_fd(' ', 1);
		i++;
		(foo->width)--;
	}
	return (i);
}

static int	ft_checkminusp(t_combo *foo, char *p, int len)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if ((foo->precision) > len && (foo->precision) != -1)
		(foo->precision) = len;
	if ((foo->precision) < len && (foo->precision) != -1)
		len = (foo->precision);
	if (len > (foo->precision) && (foo->flag) == 0)
		ft_putstr_fd(p, 1);
	while (j < (foo->precision))
		ft_putchar_fd(p[j++], 1);
	while (len < (foo->width)--)
	{
		ft_putchar_fd(' ', 1);
		i++;
	}
	return (i + j);
}

static int	ft_checkminuslast(t_combo *foo, char *p, int len)
{
	int i;

	i = 0;
	ft_putstr_fd(p, 1);
	while ((foo->width)-- > len)
	{
		ft_putchar_fd(' ', 1);
		i++;
	}
	return (len + i);
}

int			ft_manage_minus_s(t_combo *foo, va_list list)
{
	char	*p;
	int		i;
	int		len;

	i = 0;
	p = va_arg(list, char *);
	if (p != NULL)
		len = ft_strlen(p);
	else if (p == NULL)
	{
		p = ft_strdup("(null)");
		len = ft_strlen(p);
	}
	else
		len = -1;
	if (foo->precision == 0 || foo->precision == -1)
		return (ft_checkminus(foo, p, len));
	else if (foo->precision > 0)
		return (ft_checkminusp(foo, p, len));
	else
		return (ft_checkminuslast(foo, p, len));
	free(p);
	return (0);
}

int			ft_manage_simple_s(va_list list)
{
	char	*p;
	int		len;

	p = va_arg(list, char *);
	if (p == NULL)
		p = ft_strdup("(null)");
	len = ft_strlen(p);
	ft_putstr_fd(p, 1);
	return (len);
}

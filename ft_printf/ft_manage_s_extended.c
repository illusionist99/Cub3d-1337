/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_s_extended.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 05:23:49 by malaoui           #+#    #+#             */
/*   Updated: 2020/03/08 10:15:45 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	ft_checknorm(t_combo *foo, char *p, int len)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if ((foo->width) == 0 && foo->precision == 0)
		return (0);
	if ((foo->flag) == 1)
		j = 0;
	else
		j = len;
	while (j < (foo->width))
	{
		ft_putchar_fd(' ', 1);
		i++;
		(foo->width)--;
	}
	if ((foo->flag) != 1)
	{
		i += len;
		ft_putstr_fd(p, 1);
	}
	return (i);
}

static int	ft_checknormp(t_combo *foo, char *p, int len)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	j = 0;
	if (foo->precision == -1)
		foo->precision = 0;
	if ((foo->precision) > len && (foo->precision) != -1)
		(foo->precision) = len;
	if ((foo->precision) < len && (foo->precision) != -1)
		len = (foo->precision);
	while (len < (foo->width)--)
	{
		ft_putchar_fd(' ', 1);
		i++;
	}
	if (len > (foo->precision) && (foo->flag) == 0)
		ft_putstr_fd(p, 1);
	s = ft_substr(p, 0, foo->precision);
	while (j < (foo->precision))
		ft_putchar_fd(s[j++], 1);
	free(s);
	return (i + j);
}

static int	ft_checknormlast(char *p, int len)
{
	ft_putstr_fd(p, 1);
	return (len);
}

int			ft_manage_norm_s(t_combo *foo, va_list list)
{
	char	*p;
	int		len;

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
	if ((foo->precision) == 0 || foo->precision == -1)
		return (ft_checknorm(foo, p, len));
	else if ((foo->precision > 0))
		return (ft_checknormp(foo, p, len));
	else
		return (ft_checknormlast(p, len));
	return (0);
}

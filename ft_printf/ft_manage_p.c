/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 04:28:41 by malaoui           #+#    #+#             */
/*   Updated: 2019/11/25 15:11:14 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int			ft_manage_minus_p(t_combo *foo, va_list list)
{
	int			i;
	int			len;
	char		*p;
	long long	l;
	char		*s;

	i = 0;
	l = (size_t)va_arg(list, unsigned long long);
	s = ft_hex(l);
	if (l == 0 && foo->flag == 1)
		p = ft_strdup("0x");
	else
		p = ft_strjoin("0x", s);
	ft_putstr_fd(p, 1);
	len = ft_strlen(p);
	i = len;
	while ((foo->width) > len)
	{
		ft_putchar_fd(' ', 1);
		(foo->width)--;
		i++;
	}
	free(p);
	free(s);
	return (i);
}

int			ft_manage_zero_p(t_combo *foo, va_list list)
{
	int		i;
	char	*p;
	char	*s;

	s = ft_hex((size_t)va_arg(list, unsigned long long));
	p = ft_strjoin("0x", s);
	i = ft_strlen(p);
	while (i < (foo->width))
	{
		ft_putchar_fd('0', 1);
		i++;
	}
	ft_putstr_fd(p, 1);
	free(p);
	free(s);
	return (i);
}

int			ft_nullp(char **p, char *s)
{
	int		i;

	i = 0;
	*p = ft_strjoin("0x", s);
	ft_putstr_fd(*p, 1);
	i = ft_strlen(*p);
	return (i);
}

int			ft_manage_norm_p(t_combo *foo, va_list list)
{
	int			i;
	char		*p;
	long long	l;
	char		*s;

	i = 0;
	p = NULL;
	l = (size_t)va_arg(list, unsigned long long);
	s = ft_hex(l);
	if (l == 0 && foo->flag == 1)
		p = ft_strdup("0x");
	else if (!foo->width && !foo->precision)
		return (ft_nullp(&p, s));
	else
		ft_notnull(&p, s);
	i = ft_strlen(p);
	while (i < (foo->width))
	{
		ft_putchar_fd(' ', 1);
		i++;
	}
	ft_putstr_fd(p, 1);
	free(p);
	return (i);
}

int			ft_manage_simple_p(va_list list)
{
	char	*p;
	int		len;
	char	*s;

	p = NULL;
	s = ft_hex((size_t)va_arg(list, unsigned long long));
	if (s == NULL)
		p = ft_strdup("0x0");
	else
		p = ft_strjoin("0x", s);
	len = ft_strlen(p);
	ft_putstr_fd(p, 1);
	free(p);
	free(s);
	return (len);
}

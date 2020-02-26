/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_value.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 05:05:27 by malaoui           #+#    #+#             */
/*   Updated: 2019/11/23 17:25:21 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void		ft_init(t_combo *foo)
{
	(foo->precision) = 0;
	(foo->width) = 0;
	(foo->flag) = 0;
	(foo->cc) = 0;
}

void		ft_assign_width_value(const char *s, va_list list,
int *i, t_combo *foo)
{
	if (s[*i] == 42)
		(foo->width) = va_arg(list, int);
	else
		(foo->width) = ft_atoi((char *)s + *i);
	while ((ft_isdigit(s[*i]) || (s[*i] == 42)) && (s[*i] != '\0'))
		*i += 1;
}

void		ft_assign_precision_value(const char *s, va_list list,
int *i, t_combo *foo)
{
	if (s[*i] == 42)
	{
		(foo->precision) = va_arg(list, int);
		if ((foo->precision) == 0)
			(foo->flag) = 1;
		else
			(foo->flag) = 0;
	}
	else if (ft_isdigit(s[*i]))
	{
		(foo->precision) = ft_atoi((char *)s + *i);
		if ((foo->precision) == 0)
			(foo->flag) = 1;
		else
			(foo->flag) = 0;
	}
	if ((foo->precision) < 0)
		foo->precision = -1;
	while ((ft_isdigit(s[*i]) || (s[*i] == 42) ||
s[*i] == '.') && (s[*i] != '\0'))
		*i += 1;
}

int			ft_calcul_width_precision(const char *s, t_combo *foo, va_list list)
{
	int	i;

	i = 0;
	if (ft_isdigit(s[i]) || s[i] == 42 || s[i] == '.')
	{
		ft_assign_width_value(s, list, &i, foo);
		if (s[i] == '.')
		{
			i++;
			(foo->flag) = 1;
		}
		ft_assign_precision_value(s, list, &i, foo);
	}
	return (i);
}

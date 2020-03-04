/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag_minus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 16:19:58 by malaoui           #+#    #+#             */
/*   Updated: 2020/03/04 17:23:54 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

extern char g_conv;

void	ft_handle_negative(t_combo *foo, int *i, char **p, int *len)
{
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

int		ft_minus(char *s, va_list list, t_combo *foo, int *pos)
{
	int j;

	j = 0;
	*pos += 1;
	while ((s[*pos] == '-') && s[*pos] != '\0')
		*pos += 1;
	j = ft_calcul_width_precision(s + *pos, foo, list);
	*pos += 1;
	*pos += j;
	if (foo->width < 0)
		foo->width *= -1;
	return (ft_flag_minus(foo, list));
}

int		ft_for_minus(char *s, va_list list, t_combo *foo, int *pos)
{
	int i;
	int cpt;

	cpt = 0;
	i = 0;
	cpt = ft_minus((char *)s, list, foo, &i);
	*pos += i;
	return (cpt);
}

int		ft_flag_minus(t_combo *foo, va_list list)
{
	if (g_conv == 'c')
		return (ft_manage_minus_c(foo, list));
	else if (g_conv == 'p')
		return (ft_manage_minus_p(foo, list));
	else if (g_conv == 's')
		return (ft_manage_minus_s(foo, list));
	else if (g_conv == 'd' || g_conv == 'i')
		return (ft_manage_minus_di(foo, list));
	else if (g_conv == 'x')
		return (ft_manage_minus_x(foo, list));
	else if (g_conv == 'X')
		return (ft_manage_minus_xx(foo, list));
	else if (g_conv == 'u')
		return (ft_manage_minus_u(foo, list));
	return (0);
}

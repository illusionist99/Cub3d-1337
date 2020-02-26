/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag_zero.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 20:46:45 by malaoui           #+#    #+#             */
/*   Updated: 2019/11/24 05:07:21 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

extern char g_conv;

void		ft_notnull(char **p, char *s)
{
	*p = ft_strjoin("0x", s);
	free(s);
}

int			ft_negprecision(char **p, int i, int len)
{
	free(*p);
	return (i + len);
}

static int	ft_redirection(t_combo *foo, va_list list)
{
	if (g_conv == 'c')
		return (ft_manage_zero_c(foo, list));
	else if (g_conv == 'p')
		return (ft_manage_zero_p(foo, list));
	else if (g_conv == 'd' || g_conv == 'i')
		return (ft_manage_zero_di(foo, list));
	else if (g_conv == 'x')
		return (ft_manage_zero_x(foo, list));
	else if (g_conv == 'X')
		return (ft_manage_zero_xx(foo, list));
	else if (g_conv == 'u')
		return (ft_manage_zero_u(foo, list));
	return (0);
}

int			ft_flag_zero(t_combo *foo, va_list list)
{
	if (foo->precision == 0 || foo->precision == -1)
		return (ft_redirection(foo, list));
	else
	{
		if (g_conv == 'c')
			return (ft_manage_norm_c(foo, list));
		else if (g_conv == 'p')
			return (ft_manage_norm_p(foo, list));
		else if (g_conv == 'd' || g_conv == 'i')
			return (ft_manage_norm_di(foo, list));
		else if (g_conv == 'x')
			return (ft_manage_norm_x(foo, list));
		else if (g_conv == 'X')
			return (ft_manage_norm_xx(foo, list));
		else if (g_conv == 'u')
			return (ft_manage_norm_u(foo, list));
	}
	return (0);
}

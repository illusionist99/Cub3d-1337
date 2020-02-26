/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 18:04:31 by malaoui           #+#    #+#             */
/*   Updated: 2019/11/25 15:01:32 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include "libft/libft.h"
# include <stdarg.h>
# include <stdio.h>

typedef	struct	s_combo
{
	int width;
	int precision;
	int flag;
	int cc;
	int star;
}				t_combo;

char			*ft_strrev(char *str);
int				ft_len(unsigned long long nb);
char			*ft_upper(char *str);
char			*ft_hex(unsigned long long nb);
int				ft_printf(const char *s, ...);
int				ft_flag_minus(t_combo *foo, va_list list);
int				ft_flag_zero(t_combo *foo, va_list list);
int				ft_no_flag(t_combo *foo, va_list list);
int				ft_manage_simple(va_list list);
char			ft_search_conv(const char *s);
int				ft_manage_minus_c(t_combo *foo, va_list list);
int				ft_manage_zero_c(t_combo *foo, va_list list);
int				ft_manage_norm_c(t_combo *foo, va_list list);
int				ft_manage_simple_c(va_list list);
int				ft_manage_minus_s(t_combo *foo, va_list list);
int				ft_manage_norm_s(t_combo *foo, va_list list);
int				ft_manage_simple_s(va_list list);
int				ft_manage_minus_p(t_combo *foo, va_list list);
int				ft_manage_zero_p(t_combo *foo, va_list list);
int				ft_manage_norm_p(t_combo *foo, va_list list);
int				ft_manage_simple_p(va_list list);
int				ft_manage_minus_di(t_combo *foo, va_list list);
int				ft_manage_zero_di(t_combo *foo, va_list list);
int				ft_manage_norm_di(t_combo *foo, va_list list);
int				ft_manage_simple_di(va_list list);
int				ft_manage_minus_x(t_combo *foo, va_list list);
int				ft_manage_zero_x(t_combo *foo, va_list list);
int				ft_manage_norm_x(t_combo *foo, va_list list);
int				ft_manage_simple_x(va_list list);
int				ft_manage_minus_xx(t_combo *foo, va_list list);
int				ft_manage_zero_xx(t_combo *foo, va_list list);
int				ft_manage_norm_xx(t_combo *foo, va_list list);
int				ft_manage_simple_xx(va_list list);
int				ft_manage_minus_u(t_combo *foo, va_list list);
int				ft_manage_zero_u(t_combo *foo, va_list list);
int				ft_manage_norm_u(t_combo *foo, va_list list);
int				ft_manage_simple_u(va_list list);
int				ft_calcul_width_precision(const char *s, t_combo *foo,
va_list list);
void			ft_init(t_combo *foo);
int				ft_percent_minus(char *s, int *pos, t_combo *foo, va_list list);
int				ft_percent_digit(char *s, int *pos, t_combo *foo, va_list list);
int				ft_percent_zero(char *s, int *pos, t_combo *foo, va_list list);
int				ft_percent_else(char *s, int *pos, t_combo *foo, va_list list);
int				ft_percent_return(char *s, int *pos, t_combo *foo,
va_list list);
int				ft_minus(char *s, va_list list, t_combo *foo, int *pos);
int				ft_for_minus(char *s, va_list list, t_combo *foo, int *pos);
int				ft_for_else(char *s, int *pos, t_combo *foo, va_list list);
int				ft_for_norm(char *s, int *pos, t_combo *foo, va_list list);
int				ft_manage(const char *s, int *pos, va_list list);
int				ft_return(char *s, va_list list, int *pos, t_combo *foo);
int				ft_rem(t_combo *foo, char *p, int len);
void			ft_checkprint(t_combo *foo, char *p, int *i, int j);
void			ft_add_to_print(int *i, int *j);
void			ft_handle_negative(t_combo *foo, int *i, char **p, int *len);
int				ft_handle_nwidth(t_combo *foo, int *pos, int i, int j);
int				ft_minus(char *s, va_list list, t_combo *foo, int *pos);
int				ft_for_minus(char *s, va_list list, t_combo *foo, int *pos);
void			ft_setstring(char **str, size_t *i);
void			ft_notnull(char **p, char *s);
int				ft_negprecision(char **p, int i, int len);
#endif

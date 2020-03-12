/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_maze.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 10:30:18 by malaoui           #+#    #+#             */
/*   Updated: 2020/03/13 00:34:18 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcub3d.h"

void	ft_free_map(int n, char *error_msg)
{
	int i;

	i = 0;
	while (i < n && g_data.map[i] != '\0')
	{
		free(g_data.map[i]);
		i++;
	}
	ft_printf("\033[0;32m [!] %s \033[0m!\n", error_msg);
}

int		ft_check_valid(char *s, int m_index)
{
	int		i;
	char	*trim;

	i = -1;
	trim = ft_strtrim(s, " ");
	if (m_index == 0)
	{
		while (trim[++i] != '\0')
			if (trim[i] != '1')
				return (-1);
	}
	else if (m_index > 0 && m_index <= g_data.index - 1)
	{
		if (trim[0] != '1' || trim[ft_strlen(trim) - 1] != '1')
			return (-1);
		if (ft_check_for_error(trim, m_index) != 1)
		{
			ft_free(g_data.nb_of_cols, "INVALID MAP");
			return (-1);
		}
	}
	else if (m_index == g_data.index)
	{
		while (trim[++i] != '\0')
			if (trim[i] != '1')
				return (-1);
	}
	return (1);
}

void	ft_free_struct(t_image *ptr)
{
	free(ptr->ptr);
	free(ptr->data);
}

void	ft_free_sprites(t_texture *ptr)
{
	if (ptr->east)
		free(ptr->east);
	if (ptr->north)
		free(ptr->north);
	if (ptr->south)
		free(ptr->south);
	if (ptr->west)
		free(ptr->west);
}

int		ft_check_final(char *s, int m_index)
{
	int i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '0')
		{
			if (g_data.map[m_index + 1][i] == ' ' ||
			g_data.map[m_index - 1][i] == ' ')
				return (-1);
		}
		i++;
	}
	return (1);
}

int		ft_check_maze(void)
{
	int i;

	i = 0;
	while (g_data.map[i] != '\0')
	{
		if (ft_check_valid(g_data.map[i], i) != 1)
			ft_free(i, "Map is invalid");
		if (ft_check_final(g_data.map[i], i) != 1)
			ft_free(i, "Map is invalid");
		i++;
	}
	ft_printf("\033[0;32m *** Map is Valid loading ...\033[0m!\n");
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bmp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 20:38:31 by malaoui           #+#    #+#             */
/*   Updated: 2020/03/08 10:15:57 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcub3d.h"

unsigned char	g_bmpfileheader[14];
unsigned char	g_bmpinfoheader[40];
int				g_fd;
int				g_filesize;

void			ft_set_header(void)
{
	int			i;

	i = 2;
	g_bmpfileheader[0] = 'B';
	g_bmpfileheader[1] = 'M';
	while (i < 10)
		g_bmpfileheader[i++] = 0;
	g_bmpfileheader[i++] = 54;
	while (i < 14)
		g_bmpfileheader[i++] = 0;
}

void			ft_set_infoheader(void)
{
	int			i;

	i = 0;
	g_bmpinfoheader[i++] = 40;
	while (i < 12)
		g_bmpinfoheader[i++] = 0;
	g_bmpinfoheader[i++] = 1;
	g_bmpinfoheader[i++] = 0;
	g_bmpinfoheader[i++] = 24;
	g_bmpinfoheader[i] = 0;
}

void			ft_right_shift(void)
{
	g_fd = open("file.bmp", O_CREAT | O_RDWR, 0644);
	g_filesize = 54 + 3 * (g_data.width * g_data.height);
	g_bmpfileheader[2] = (unsigned char)g_filesize;
	g_bmpfileheader[3] = (unsigned char)(g_filesize >> 8);
	g_bmpfileheader[4] = (unsigned char)(g_filesize >> 16);
	g_bmpfileheader[5] = (unsigned char)(g_filesize >> 24);
	g_bmpinfoheader[4] = (unsigned char)(g_data.width);
	g_bmpinfoheader[5] = (unsigned char)(g_data.width >> 8);
	g_bmpinfoheader[6] = (unsigned char)(g_data.width >> 16);
	g_bmpinfoheader[7] = (unsigned char)(g_data.width >> 24);
	g_bmpinfoheader[8] = (unsigned char)(g_data.height);
	g_bmpinfoheader[9] = (unsigned char)(g_data.height >> 8);
	g_bmpinfoheader[10] = (unsigned char)(g_data.height >> 16);
	g_bmpinfoheader[11] = (unsigned char)(g_data.height >> 24);
	write(g_fd, g_bmpfileheader, 14);
	write(g_fd, g_bmpinfoheader, 40);
}

void			ft_to_bmp(void)
{
	int			i;
	int			j;
	int			num;

	i = 0;
	j = 0;
	num = 0;
	while (i < g_data.height)
	{
		num = (g_data.height - i - 1) * g_data.width;
		j = 0;
		while (j < g_data.width)
		{
			write(g_fd, &g_image.data[num + j], 3);
			j++;
		}
		i++;
	}
	close(g_fd);
}

void			ft_handle_bmp(void)
{
	ft_set_header();
	ft_set_infoheader();
	ft_right_shift();
	ft_to_bmp();
	system(ft_strjoin("kill ", ft_itoa(g_child)));
	exit(1);
}

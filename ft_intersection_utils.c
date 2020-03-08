/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intersection_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 06:31:37 by malaoui           #+#    #+#             */
/*   Updated: 2020/03/08 14:13:04 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcub3d.h"

void		ft_draw_texture(t_image ptr, int col,
float offset, float wallstripheight)
{
	float	start;
	float	end;
	float	texture_y;
	float	step;

	start = g_data.height / 2 - wallstripheight / 2 + g_look;
	end = g_data.height / 2 + wallstripheight / 2 + g_look;
	texture_y = 0;
	step = (float)(ptr.height / (end - start));
	while (start <= end)
	{
		if ((int)(texture_y) * ptr.height +
		(int)offset < ptr.height * ptr.width)
			ft_pixel_put(col, start, shadow(ptr.data[(int)(texture_y)
			* ptr.height + (int)offset], col));
		texture_y += step;
		start++;
	}
}

void		ft_horz_inc(t_run *mdr)
{
	while ((mdr->nexthorztouchx >= 0 &&
	mdr->nexthorztouchx < 35 * TILE_SIZE) &&
	(mdr->nexthorztouchy >= 0 && mdr->nexthorztouchy < 14 * TILE_SIZE))
	{
		if (!ft_haswall(mdr->nexthorztouchx, mdr->nexthorztouchy))
		{
			mdr->foundhorzwallhit = TRUE;
			mdr->horzwallhitx = mdr->nexthorztouchx;
			mdr->horzwallhity = mdr->nexthorztouchy;
			break ;
		}
		else
		{
			mdr->nexthorztouchx += mdr->xstep;
			mdr->nexthorztouchy += mdr->ystep;
		}
	}
}

t_run		*ft_horz(t_run *mdr, float rayangle)
{
	mdr->foundhorzwallhit = FALSE;
	mdr->horzwallhitx = 0;
	mdr->horzwallhity = 0;
	rayfacing(rayangle);
	mdr->yintercept = floor(g_player.y / TILE_SIZE) * TILE_SIZE;
	mdr->yintercept += g_ray.down ? TILE_SIZE : -0.0001;
	mdr->xintercept = g_player.x +
	(mdr->yintercept - g_player.y) / tan(rayangle);
	mdr->ystep = TILE_SIZE;
	mdr->ystep *= g_ray.up ? -1 : 1;
	mdr->xstep = TILE_SIZE / tan(rayangle);
	mdr->xstep *= (g_ray.left && mdr->xstep > 0) ? -1 : 1;
	mdr->xstep *= (g_ray.right && mdr->xstep < 0) ? -1 : 1;
	mdr->nexthorztouchx = mdr->xintercept;
	mdr->nexthorztouchy = mdr->yintercept;
	ft_horz_inc(mdr);
	return (mdr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intersection_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 06:31:37 by malaoui           #+#    #+#             */
/*   Updated: 2020/03/08 06:32:55 by malaoui          ###   ########.fr       */
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

	start = data.Height / 2 - wallstripheight / 2 + g_look;
	end = data.Height / 2 + wallstripheight / 2 + g_look;
	texture_y = 0;
	step = (float)(ptr.height / (end - start));
	while (start <= end)
	{
		if ((int)(texture_y) * ptr.height +
		(int)offset < ptr.height * ptr.width)
			ft_pixel_put(col, start, ptr.data[(int)(texture_y) * ptr.height
			+ (int)offset]);
		texture_y += step;
		start++;
	}
}

void		ft_horz_inc(t_run *mdr)
{
	while ((mdr->nextHorzTouchX >= 0 &&
	mdr->nextHorzTouchX < 35 * TILE_SIZE) &&
	(mdr->nextHorzTouchY >= 0 && mdr->nextHorzTouchY < 14 * TILE_SIZE))
	{
		if (!ft_hasWall(mdr->nextHorzTouchX, mdr->nextHorzTouchY))
		{
			mdr->foundHorzwallHit = TRUE;
			mdr->horzWallHitX = mdr->nextHorzTouchX;
			mdr->horzWallHitY = mdr->nextHorzTouchY;
			break ;
		}
		else
		{
			mdr->nextHorzTouchX += mdr->xstep;
			mdr->nextHorzTouchY += mdr->ystep;
		}
	}
}

t_run		*ft_horz(t_run *mdr, float rayangle)
{
	mdr->foundHorzwallHit = FALSE;
	mdr->horzWallHitX = 0;
	mdr->horzWallHitY = 0;
	rayfacing(rayangle);
	mdr->yintercept = floor(player.y / TILE_SIZE) * TILE_SIZE;
	mdr->yintercept += ray.down ? TILE_SIZE : -0.0001;
	mdr->xintercept = player.x + (mdr->yintercept - player.y) / tan(rayangle);
	mdr->ystep = TILE_SIZE;
	mdr->ystep *= ray.up ? -1 : 1;
	mdr->xstep = TILE_SIZE / tan(rayangle);
	mdr->xstep *= (ray.left && mdr->xstep > 0) ? -1 : 1;
	mdr->xstep *= (ray.right && mdr->xstep < 0) ? -1 : 1;
	mdr->nextHorzTouchX = mdr->xintercept;
	mdr->nextHorzTouchY = mdr->yintercept;
	ft_horz_inc(mdr);
	return (mdr);
}

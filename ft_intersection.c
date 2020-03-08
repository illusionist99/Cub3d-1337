/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intersection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 10:45:22 by malaoui           #+#    #+#             */
/*   Updated: 2020/03/08 06:32:09 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcub3d.h"

void		ft_vert_inc(t_run *mdr)
{
	while ((mdr->nextVertTouchX >= 0 &&
	mdr->nextVertTouchX < 35 * TILE_SIZE) &&
	(mdr->nextVertTouchY >= 0 && mdr->nextVertTouchY < 14 * TILE_SIZE))
	{
		if (!ft_hasWall(mdr->nextVertTouchX, mdr->nextVertTouchY))
		{
			mdr->foundVertwallHit = TRUE;
			mdr->vertWallHitX = mdr->nextVertTouchX;
			mdr->vertWallHitY = mdr->nextVertTouchY;
			break ;
		}
		else
		{
			mdr->nextVertTouchX += mdr->xstep;
			mdr->nextVertTouchY += mdr->ystep;
		}
	}
}

t_run		*ft_vert(t_run *mdr, float rayangle)
{
	mdr->foundVertwallHit = FALSE;
	mdr->vertWallHitX = 0;
	mdr->vertWallHitY = 0;
	rayfacing(rayangle);
	mdr->xintercept = floor(player.x / TILE_SIZE) * TILE_SIZE;
	mdr->xintercept += ray.right ? TILE_SIZE : -0.0001;
	mdr->yintercept = player.y + (mdr->xintercept - player.x) * tan(rayangle);
	mdr->xstep = TILE_SIZE;
	mdr->xstep *= ray.left ? -1 : 1;
	mdr->ystep = TILE_SIZE * tan(rayangle);
	mdr->ystep *= (ray.up && mdr->ystep > 0) ? -1 : 1;
	mdr->ystep *= (ray.down && mdr->ystep < 0) ? -1 : 1;
	mdr->nextVertTouchX = mdr->xintercept;
	mdr->nextVertTouchY = mdr->yintercept;
	ft_vert_inc(mdr);
	return (mdr);
}

void		ft_draw_fc_mini(int col, float wallstripheight)
{
	ft_draw_line(col, 0, col,
		data.Height / 2 - wallstripheight / 2 + g_look, data.ceilling.color);
	ft_draw_line(col, data.Height / 2 + wallstripheight / 2 + g_look,
		col, data.Height, data.floor.color);
	ft_draw_line(player.x * MINIMAP_SCALE, player.y * MINIMAP_SCALE,
		wallhit.x * MINIMAP_SCALE, wallhit.y * MINIMAP_SCALE, WHITE);
}

void		ft_empty_trash(float rayangle, int col)
{
	float	distanceprojplane;
	float	raydist;
	float	an;
	float	wallstripheight;
	float	offset;

	an = rayangle - player.dirangle;
	raydist = wallhit.distance * cos(an);
	distanceprojplane = (data.Width / 2) / tan(player.fov / 2);
	wallstripheight = (TILE_SIZE / raydist) * distanceprojplane;
	offset = ((wallhit.wasHitVertical == 0) ?
	fmod(wallhit.x, TILE_SIZE) : fmod(wallhit.y, TILE_SIZE));
	if (ray.down && !wallhit.wasHitVertical)
		ft_draw_texture(west, col, offset, wallstripheight);
	else if (ray.left && wallhit.wasHitVertical)
		ft_draw_texture(east, col, offset, wallstripheight);
	else if (ray.right && wallhit.wasHitVertical)
		ft_draw_texture(south, col, offset, wallstripheight);
	else if (ray.up && !wallhit.wasHitVertical)
		ft_draw_texture(north, col, offset, wallstripheight);
	ft_draw_fc_mini(col, wallstripheight);
}

void		ft_wall_hit(int col, float rayangle)
{
	t_run	mdr;

	mdr.foundHorzwallHit = FALSE;
	mdr.foundVertwallHit = FALSE;
	ft_horz(&mdr, rayangle);
	ft_vert(&mdr, rayangle);
	mdr.horzHitDistance = (mdr.foundHorzwallHit)
	? ft_distancebetweenpoints(player.x, player.y,
	mdr.horzWallHitX, mdr.horzWallHitY) : INT_MAX;
	mdr.vertHitDistance = (mdr.foundVertwallHit) ?
	ft_distancebetweenpoints(player.x, player.y,
	mdr.vertWallHitX, mdr.vertWallHitY) : INT_MAX;
	wallhit.x = (mdr.horzHitDistance < mdr.vertHitDistance)
	? mdr.horzWallHitX : mdr.vertWallHitX;
	wallhit.y = (mdr.horzHitDistance < mdr.vertHitDistance)
	? mdr.horzWallHitY : mdr.vertWallHitY;
	wallhit.distance = (mdr.horzHitDistance < mdr.vertHitDistance)
	? mdr.horzHitDistance : mdr.vertHitDistance;
	wallhit.wasHitVertical = (mdr.vertHitDistance < mdr.horzHitDistance);
	ray_distance[col] = wallhit.distance;
	ft_empty_trash(rayangle, col);
}

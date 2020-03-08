
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intersection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 10:45:22 by malaoui           #+#    #+#             */
/*   Updated: 2020/03/05 10:58:24 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcub3d.h"

void	ft_draw_texture(t_image ptr, int col, float offset, float wallstripheight)
{
	float start = data.Height /2 - wallstripheight/2 + g_look;
	float end = data.Height /2 + wallstripheight/2 + g_look;
	float texture_y = 0;
	float step = (float )(ptr.height/(end - start));

	while (start <= end)
	{
		if ((int)(texture_y) * ptr.height + (int)offset < ptr.height*ptr.width)
			ft_pixel_put(col, start, ptr.data[(int)(texture_y) * ptr.height + (int)offset]);
		texture_y += step;
		start++;
	}
}

// void	ft_handle_text(int col, float rayangle)
// {
// 	float distanceProjPlane;
//     float raydist;  
//     float an;
//     float wallStripHeight;

//     an = rayangle - player.dirangle;
//     raydist  = wallhit.distance * cos(an);
//     distanceProjPlane = (data.Width/2) / tan(player.fov/2);
//     wallStripHeight = (TILE_SIZE/raydist) * distanceProjPlane;
	
//     float offset = ((wallhit.wasHitVertical == 0) ? fmod(wallhit.x , TILE_SIZE) : fmod(wallhit.y, TILE_SIZE));

// 		float start = data.Height /2 - wallStripHeight/2 + g_look;
// 		float end = data.Height /2 + wallStripHeight/2 + g_look;
	
// 		if (ray.down && !wallhit.wasHitVertical)
// 			ft_draw_texture(west, col, offset, wallStripHeight);
// 		else if (ray.left && wallhit.wasHitVertical)
// 			ft_draw_texture(east, col, offset, wallStripHeight);
// 		else if (ray.right && wallhit.wasHitVertical)
// 			ft_draw_texture(south, col, offset, wallStripHeight);
// 		else if (ray.up && !wallhit.wasHitVertical)
// 			ft_draw_texture(north, col, offset, wallStripHeight);
// 		ft_draw_line(col , 0, col, data.Height/2 - wallStripHeight/2 + g_look, data.ceilling.color);
// 		ft_draw_line(col , data.Height/2 + wallStripHeight/2 + g_look, col, data.Height, data.floor.color);
//     	ft_draw_line(player.x * MINIMAP_SCALE, player.y * MINIMAP_SCALE, wallhit.x * MINIMAP_SCALE , wallhit.y * MINIMAP_SCALE, WHITE);
// }

// void	ft_get_distance(int col, t_dir horzwallhit, t_dir vertwallhit)
// {
// 	float horzHitDistance = (mdr->foundHorzwallHit) ? ft_distancebetweenpoints(player.x, player.y, horzwallhit.x, horzwallhit.y)
// 	 : INT_MAX;
//     float vertHitDistance = (mdr->foundVertwallHit) ? ft_distancebetweenpoints(player.x, player.y, vertwallhit.x, vertwallhit.y)
// 	 : INT_MAX;

// 	wallhit.x = (horzHitDistance < vertHitDistance) ? horzwallhit.x : vertwallhit.x;
// 	wallhit.y = (horzHitDistance < vertHitDistance) ? horzwallhit.y : vertwallhit.y;
// 	wallhit.distance = (horzHitDistance < vertHitDistance) ? horzHitDistance : vertHitDistance;
// 	wallhit.wasHitVertical = (vertHitDistance < horzHitDistance);
// 	ray_distance[col] = wallhit.distance;
// }



t_run 	*ft_horz(t_run *mdr, float rayangle)
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

	while (mdr->nextHorzTouchX >= 0 && mdr->nextHorzTouchX < 35 * TILE_SIZE && mdr->nextHorzTouchY >= 0 && mdr->nextHorzTouchY < 14 * TILE_SIZE)
	{
		if (!ft_hasWall(mdr->nextHorzTouchX, mdr->nextHorzTouchY))
		{
			mdr->foundHorzwallHit = TRUE;
			mdr->horzWallHitX = mdr->nextHorzTouchX;
			mdr->horzWallHitY = mdr->nextHorzTouchY;
			break;
		}
		else
		{
			mdr->nextHorzTouchX += mdr->xstep;
			mdr->nextHorzTouchY += mdr->ystep;
		}
	}
	return (mdr);
}

t_run	*ft_vert(t_run *mdr, float rayangle)
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

	while ((mdr->nextVertTouchX >= 0 && mdr->nextVertTouchX <  35 * TILE_SIZE) && (mdr->nextVertTouchY >= 0  && mdr->nextVertTouchY < 14 * TILE_SIZE))
	{
		if (!ft_hasWall(mdr->nextVertTouchX, mdr->nextVertTouchY))
		{
			mdr->foundVertwallHit = TRUE;
			mdr->vertWallHitX = mdr->nextVertTouchX;
			mdr->vertWallHitY = mdr->nextVertTouchY;
			break;
		}
		else
		{
			mdr->nextVertTouchX += mdr->xstep;
			mdr->nextVertTouchY += mdr->ystep;
		}
	}
	return (mdr);
}

void		ft_empty_trash(float rayangle, int col)
{
	float distanceProjPlane;
	float raydist;  
	float an;
	float wallStripHeight;
	float offset;

	an = rayangle - player.dirangle;
	raydist  = wallhit.distance * cos(an);
	distanceProjPlane = (data.Width/2) / tan(player.fov/2);
	wallStripHeight = (TILE_SIZE/raydist) * distanceProjPlane;
	offset = ((wallhit.wasHitVertical == 0) ? fmod(wallhit.x , TILE_SIZE) : fmod(wallhit.y, TILE_SIZE));
	if (ray.down && !wallhit.wasHitVertical)
		ft_draw_texture(west, col, offset, wallStripHeight);
	else if (ray.left && wallhit.wasHitVertical)
		ft_draw_texture(east, col, offset, wallStripHeight);
	else if (ray.right && wallhit.wasHitVertical)
		ft_draw_texture(south, col, offset, wallStripHeight);
	else if (ray.up && !wallhit.wasHitVertical)
		ft_draw_texture(north, col, offset, wallStripHeight);
	ft_draw_line(col , 0, col, data.Height/2 - wallStripHeight/2 + g_look, data.ceilling.color);
	ft_draw_line(col , data.Height/2 + wallStripHeight/2 + g_look, col, data.Height, data.floor.color);
	ft_draw_line(player.x * MINIMAP_SCALE, player.y * MINIMAP_SCALE, wallhit.x * MINIMAP_SCALE , wallhit.y * MINIMAP_SCALE, WHITE);
}


void    	ft_wall_hit(int col, float rayangle)
{
	t_run mdr;

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

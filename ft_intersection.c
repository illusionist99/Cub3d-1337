/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intersection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 10:45:22 by malaoui           #+#    #+#             */
/*   Updated: 2020/02/29 01:39:58 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcub3d.h"


void    init_ray()
{
	ray.down = 0;
	ray.up = 0;
	ray.right = 0;
	ray.left = 0;
}

void    RayFacing(float angle)
{
	init_ray();
	ray.down = (angle > 0 && angle < M_PI);
	ray.up = !ray.down;
	ray.right = (angle < 0.5 * M_PI || angle > 1.5 * M_PI);
	ray.left = !ray.right;
}


float   ft_distanceBetweenPoints(float x1, float y1, float x2, float y2) 
{ 
    return sqrt(pow(x2 - x1, 2) +  pow(y2 - y1, 2)); 
} 

float    ft_Wall_Hit(int col, float rayAngle)
{
	float xintercept, yintercept;
	float xstep, ystep;

	float foundHorzWallHit = FALSE;
	float horzWallHitX = 0;
	float horzWallHitY = 0;
	
	RayFacing(rayAngle);
	yintercept = floor(player.y / TILE_SIZE) * TILE_SIZE;
	yintercept += ray.down ? TILE_SIZE : 0;

	xintercept = player.x + (yintercept - player.y) / tan(rayAngle);

	ystep = TILE_SIZE;
	ystep *= ray.up ? -1 : 1;

	xstep = TILE_SIZE / tan(rayAngle);
	xstep *= (ray.left && xstep > 0) ? -1 : 1;
	xstep *= (ray.right && xstep < 0) ? -1 : 1;

	float nextHorzTouchX = xintercept;
	float nextHorzTouchY = yintercept;

	if (ray.up)
		nextHorzTouchY--;

	while (nextHorzTouchX >= 0 && nextHorzTouchX <= data.Width && nextHorzTouchY >= 0 && nextHorzTouchY <= data.Height) {
		if (!ft_hasWall(nextHorzTouchX, nextHorzTouchY))
		{
			foundHorzWallHit = TRUE;
			horzWallHitX = nextHorzTouchX;
			horzWallHitY = nextHorzTouchY;
			break;
		}
		else
		{
			nextHorzTouchX += xstep;
			nextHorzTouchY += ystep;
		}
	}

	float foundVertWallHit = FALSE;
	float vertWallHitX = 0;
	float vertWallHitY = 0;

	xintercept = floor(player.x / TILE_SIZE) * TILE_SIZE;
	xintercept += ray.right ? TILE_SIZE : 0;

	yintercept = player.y + (xintercept - player.x) * tan(rayAngle);

	xstep = TILE_SIZE;
	xstep *= ray.left ? -1 : 1;

	ystep = TILE_SIZE * tan(rayAngle);
	ystep *= (ray.up && ystep > 0) ? -1 : 1;
	ystep *= (ray.down && ystep < 0) ? -1 : 1;

	float nextVertTouchX = xintercept;
	float nextVertTouchY = yintercept;

	if (ray.left)
		nextVertTouchX--;

	while ((nextVertTouchX >= 0 && nextVertTouchX <= data.Width) && (nextVertTouchY >= 0  && nextVertTouchY <= data.Height)) {
		if (!ft_hasWall(nextVertTouchX, nextVertTouchY))
		{
			foundVertWallHit = TRUE;
			vertWallHitX = nextVertTouchX;
			vertWallHitY = nextVertTouchY;
			break;
		}
		else
		{
			nextVertTouchX += xstep;
			nextVertTouchY += ystep;
		}
	}

	float horzHitDistance = ft_distanceBetweenPoints(player.x, player.y, horzWallHitX, horzWallHitY);
    float vertHitDistance = ft_distanceBetweenPoints(player.x, player.y, vertWallHitX, vertWallHitY);

	float wallHitX = (horzHitDistance < vertHitDistance) ? horzWallHitX : vertWallHitX;
	float wallHitY = (horzHitDistance < vertHitDistance) ? horzWallHitY : vertWallHitY;
	float distance = (horzHitDistance < vertHitDistance) ? horzHitDistance : vertHitDistance;
	float wasHitVertical = (vertHitDistance < horzHitDistance);
	
	float distanceProjPlane;
    float raydist;  
    float an;
    float wallStripHeight;

    an = rayAngle - player.dirangle;
    ft_normalizeAngle(&an);
    raydist  = distance * cos(an);
    distanceProjPlane = (data.Width/2) / tan(player.fov/2);
    wallStripHeight = (TILE_SIZE/raydist) * distanceProjPlane;

    float offset = ((wasHitVertical == 0) ? fmod(wallHitX , TILE_SIZE) : fmod(wallHitY, TILE_SIZE));

    ft_draw_line(col, data.Height/2 - wallStripHeight/2,  col, data.Height/2 + wallStripHeight/2);

    // CEILLING
    //ft_draw_line(col , 0, col, data.Height/2 - wallStripHeight/2);
    // FLOOR
    //ft_draw_line(col , data.Height/2 + wallStripHeight/2, col, data.Height);
    //ft_draw_line(player.x, player.y, wallHitX , wallHitY);
    return (distance);
}

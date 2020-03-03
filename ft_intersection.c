/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intersection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 10:45:22 by malaoui           #+#    #+#             */
/*   Updated: 2020/03/03 18:29:40 by malaoui          ###   ########.fr       */
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

int        ft_handle_texture(int col, float offset, float start, float end, float wallStripHeight)
{
    float texture_y = 0;
    float step = (float )(west.height/(end - start));

    while (start < end)
    {
			//printf("col : %d | Sttart %f \n", col, start);
        ft_pixel_put(col, start, west.data[(int)(texture_y) * west.height + (int)offset]);
        texture_y += step;
        start++;
    }
    return (0);
}

void	ft_drawmap()
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (data.map[i] != '\0')
    {
        j = 0;
        while (data.map[i][j] != '\0')
        {
            if (data.map[i][j] == '1')
                ft_draw_cube(j * TILE_SIZE , i * TILE_SIZE);
			j++;
		}
		i++;
	}
}

void    ft_Wall_Hit(int col, float rayAngle)
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

	int Width = data.nb_of_rows * TILE_SIZE;
	int Height = data.nb_of_cols * TILE_SIZE;
	while (nextHorzTouchX >= 0 && nextHorzTouchX <= Width && nextHorzTouchY >= 0 && nextHorzTouchY <= Height)
	{
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

	while ((nextVertTouchX >= 0 && nextVertTouchX <= Width) && (nextVertTouchY >= 0  && nextVertTouchY <= Height)) {
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

	float horzHitDistance = (foundHorzWallHit) ? ft_distanceBetweenPoints(player.x, player.y, horzWallHitX, horzWallHitY)
	 : INT_MAX;
    float vertHitDistance = (foundVertWallHit) ? ft_distanceBetweenPoints(player.x, player.y, vertWallHitX, vertWallHitY)
	 : INT_MAX;

	wallhit.x = (horzHitDistance < vertHitDistance) ? horzWallHitX : vertWallHitX;
	wallhit.y = (horzHitDistance < vertHitDistance) ? horzWallHitY : vertWallHitY;
	wallhit.distance = (horzHitDistance < vertHitDistance) ? horzHitDistance : vertHitDistance;
	wallhit.wasHitVertical = (vertHitDistance < horzHitDistance);
	
	float distanceProjPlane;
    float raydist;  
    float an;
    float wallStripHeight;

    an = rayAngle - player.dirangle;
    raydist  = wallhit.distance * cos(an);
	ray_distance[col] = raydist;
    distanceProjPlane = (data.Width/2) / tan(player.fov/2);
    wallStripHeight = (TILE_SIZE/raydist) * distanceProjPlane;
	
    float offset = ((wallhit.wasHitVertical == 0) ? fmod(wallhit.x , TILE_SIZE) : fmod(wallhit.y, TILE_SIZE));

		float start = data.Height /2 - wallStripHeight/2;
		float end = data.Height /2 + wallStripHeight/2;
	
		if (ray.down && !wallhit.wasHitVertical)
		{
			float texture_y = 0;
			float step = (float )(west.height/(end - start));

			while (start <= end)
			{
				if ((int)(texture_y) * west.height + (int)offset < 64*64)
					ft_pixel_put(col, start, west.data[(int)(texture_y) * west.height + (int)offset]);
				texture_y += step;
				start++;
			}	
		}
		else if (ray.left && wallhit.wasHitVertical)
		{
			float texture_y = 0;
			float step = (float )(east.height/(end - start));

			while (start <= end)
			{
				if ((int)(texture_y) * east.height + (int)offset < 64*64)
					ft_pixel_put(col, start, east.data[(int)(texture_y) * east.height + (int)offset]);
				texture_y += step;
				start++;
			}	
			
		}
		else if (ray.right && wallhit.wasHitVertical)
		{
			float texture_y = 0;
			float step = (float )(south.height/(end - start));

			while (start <= end)
			{
				if ((int)(texture_y) * south.height + (int)offset < 64*64)
					ft_pixel_put(col, start, south.data[(int)(texture_y) * south.height + (int)offset]);
				texture_y += step;
				start++;
			}	

		}
		else if (ray.up && !wallhit.wasHitVertical)
		{
			float texture_y = 0;
			float step = (float )(north.height/(end - start));

			while (start <= end)
			{
				if ((int)(texture_y) * north.height + (int)offset < 64*64)
					ft_pixel_put(col, start, north.data[(int)(texture_y) * north.height + (int)offset]);
				texture_y += step;
				start++;
			}	
			
		}
		ft_draw_line(col , 0, col, data.Height/2 - wallStripHeight/2, data.ceilling.color);
		ft_draw_line(col , data.Height/2 + wallStripHeight/2, col, data.Height, data.floor.color);
    	ft_draw_line(player.x * MINIMAP_SCALE, player.y * MINIMAP_SCALE, wallhit.x * MINIMAP_SCALE , wallhit.y * MINIMAP_SCALE, WHITE);
}

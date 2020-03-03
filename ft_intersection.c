/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intersection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 10:45:22 by malaoui           #+#    #+#             */
/*   Updated: 2020/03/03 23:57:16 by malaoui          ###   ########.fr       */
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

void    RayFacing(double angle)
{
	init_ray();
	ray.down = (angle > 0 && angle < M_PI);
	ray.up = !ray.down;
	ray.right = (angle < 0.5 * M_PI || angle > 1.5 * M_PI);
	ray.left = !ray.right;
}


double   ft_distanceBetweenPoints(double x1, double y1, double x2, double y2) 
{ 
    return sqrt(pow(x2 - x1, 2) +  pow(y2 - y1, 2)); 
} 

int        ft_handle_texture(int col, double offset, double start, double end, double wallStripHeight)
{
    double texture_y = 0;
    double step = (double )(west.height/(end - start));

    while (start < end)
    {
		if ((int)(texture_y) * west.height + (int)offset < 64 * 64)
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

void    ft_Wall_Hit(int col, double rayAngle)
{
	double xintercept, yintercept;
	double xstep, ystep;

	double foundHorzWallHit = FALSE;
	double horzWallHitX = 0;
	double horzWallHitY = 0;
	
	RayFacing(rayAngle);
	yintercept = floor(player.y / TILE_SIZE) * TILE_SIZE;
	yintercept += ray.down ? TILE_SIZE : -0.00001;

	xintercept = player.x + (yintercept - player.y) / tan(rayAngle);

	ystep = TILE_SIZE;
	ystep *= ray.up ? -1 : 1;

	xstep = TILE_SIZE / tan(rayAngle);
	xstep *= (ray.left && xstep > 0) ? -1 : 1;
	xstep *= (ray.right && xstep < 0) ? -1 : 1;

	double nextHorzTouchX = xintercept;
	double nextHorzTouchY = yintercept;

	int Width = data.nb_of_rows * TILE_SIZE;
	int Height = data.nb_of_cols * TILE_SIZE;
	while (nextHorzTouchX >= 0 && nextHorzTouchX < Width && nextHorzTouchY >= 0 && nextHorzTouchY < Height)
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

	double foundVertWallHit = FALSE;
	double vertWallHitX = 0;
	double vertWallHitY = 0;

	RayFacing(rayAngle);
	xintercept = floor(player.x / TILE_SIZE) * TILE_SIZE;
	xintercept += ray.right ? TILE_SIZE : -0.00001;

	yintercept = player.y + (xintercept - player.x) * tan(rayAngle);

	xstep = TILE_SIZE;
	xstep *= ray.left ? -1 : 1;

	ystep = TILE_SIZE * tan(rayAngle);
	ystep *= (ray.up && ystep > 0) ? -1 : 1;
	ystep *= (ray.down && ystep < 0) ? -1 : 1;

	double nextVertTouchX = xintercept;
	double nextVertTouchY = yintercept;


	while ((nextVertTouchX >= 0 && nextVertTouchX < Width) && (nextVertTouchY >= 0  && nextVertTouchY < Height)) {
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

	double horzHitDistance = (foundHorzWallHit) ? ft_distanceBetweenPoints(player.x, player.y, horzWallHitX, horzWallHitY)
	 : INT_MAX;
    double vertHitDistance = (foundVertWallHit) ? ft_distanceBetweenPoints(player.x, player.y, vertWallHitX, vertWallHitY)
	 : INT_MAX;

	wallhit.x = (horzHitDistance < vertHitDistance) ? horzWallHitX : vertWallHitX;
	wallhit.y = (horzHitDistance < vertHitDistance) ? horzWallHitY : vertWallHitY;
	wallhit.distance = (horzHitDistance < vertHitDistance) ? horzHitDistance : vertHitDistance;
	wallhit.wasHitVertical = (vertHitDistance < horzHitDistance);
	ray_distance[col] = wallhit.distance;
	double distanceProjPlane;
    double raydist;  
    double an;
    double wallStripHeight;

    an = rayAngle - player.dirangle;
    raydist  = wallhit.distance * cos(an);
    distanceProjPlane = (data.Width/2) / tan(player.fov/2);
    wallStripHeight = (TILE_SIZE/raydist) * distanceProjPlane;
	
    double offset = ((wallhit.wasHitVertical == 0) ? fmod(wallhit.x , TILE_SIZE) : fmod(wallhit.y, TILE_SIZE));

		double start = data.Height /2 - wallStripHeight/2;
		double end = data.Height /2 + wallStripHeight/2;
	
		if (ray.down && !wallhit.wasHitVertical)
		{
			double texture_y = 0;
			double step = (double )(west.height/(end - start));

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
			double texture_y = 0;
			double step = (double )(east.height/(end - start));

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
			double texture_y = 0;
			double step = (double )(south.height/(end - start));

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
			double texture_y = 0;
			double step = (double )(north.height/(end - start));

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

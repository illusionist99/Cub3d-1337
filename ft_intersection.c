/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intersection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 10:45:22 by malaoui           #+#    #+#             */
/*   Updated: 2020/03/09 17:39:23 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcub3d.h"

void		ft_vert_inc(t_run *mdr)
{
	while ((mdr->nextverttouchx >= 0 &&
	mdr->nextverttouchx < g_data.nb_of_cols * TILE_SIZE) &&
	(mdr->nextverttouchy >= 0 && mdr->nextverttouchy <
	g_data.nb_of_rows * TILE_SIZE))
	{
		if (!ft_haswall(mdr->nextverttouchx, mdr->nextverttouchy))
		{
			mdr->foundvertwallhit = TRUE;
			mdr->vertwallhitx = mdr->nextverttouchx;
			mdr->vertwallhity = mdr->nextverttouchy;
			break ;
		}
		else
		{
			mdr->nextverttouchx += mdr->xstep;
			mdr->nextverttouchy += mdr->ystep;
		}
	}
}

t_run		*ft_vert(t_run *mdr, float rayangle)
{
	mdr->foundvertwallhit = FALSE;
	mdr->vertwallhitx = 0;
	mdr->vertwallhity = 0;
	rayfacing(rayangle);
	mdr->xintercept = floor(g_player.x / TILE_SIZE) * TILE_SIZE;
	mdr->xintercept += g_ray.right ? TILE_SIZE : -0.0001;
	mdr->yintercept = g_player.y + (mdr->xintercept -
	g_player.x) * tan(rayangle);
	mdr->xstep = TILE_SIZE;
	mdr->xstep *= g_ray.left ? -1 : 1;
	mdr->ystep = TILE_SIZE * tan(rayangle);
	mdr->ystep *= (g_ray.up && mdr->ystep > 0) ? -1 : 1;
	mdr->ystep *= (g_ray.down && mdr->ystep < 0) ? -1 : 1;
	mdr->nextverttouchx = mdr->xintercept;
	mdr->nextverttouchy = mdr->yintercept;
	ft_vert_inc(mdr);
	return (mdr);
}

void		ft_draw_fc_mini(int col, float wallstripheight)
{
	t_line line;

	line.x0 = col;
	line.y0 = 0;
	line.x1 = col;
	line.y1 = g_data.height / 2 - wallstripheight / 2 + 50 * g_look;
	ft_draw_line(line, g_data.c.color);
	line.x0 = col;
	line.y0 = g_data.height / 2 + wallstripheight / 2 + 50 * g_look;
	line.x1 = col;
	line.y1 = g_data.height;
	ft_draw_line(line, g_data.floor.color);
	line.x0 = g_player.x * MINIMAP_SCALE;
	line.y0 = g_player.y * MINIMAP_SCALE;
	line.x1 = g_wallhit.x * MINIMAP_SCALE;
	line.y1 = g_wallhit.y * MINIMAP_SCALE;
	ft_draw_line(line, WHITE);
}

void		ft_empty_trash(float rayangle, int col)
{
	float	distanceprojplane;
	float	raydist;
	float	an;
	float	wallstripheight;
	float	offset;

	an = rayangle - g_player.dirangle;
	raydist = g_wallhit.distance * cos(an);
	distanceprojplane = (g_data.width / 2) / tan(g_player.fov / 2);
	wallstripheight = (TILE_SIZE / raydist) * distanceprojplane;
	offset = ((g_wallhit.washitvertical == 0) ?
	fmod(g_wallhit.x, TILE_SIZE) : fmod(g_wallhit.y, TILE_SIZE));
	if (g_ray.down && !g_wallhit.washitvertical)
		ft_draw_texture(g_west, col, offset, wallstripheight);
	else if (g_ray.left && g_wallhit.washitvertical)
		ft_draw_texture(g_east, col, offset, wallstripheight);
	else if (g_ray.right && g_wallhit.washitvertical)
		ft_draw_texture(g_south, col, offset, wallstripheight);
	else if (g_ray.up && !g_wallhit.washitvertical)
		ft_draw_texture(g_north, col, offset, wallstripheight);
	ft_draw_fc_mini(col, wallstripheight);
}

void		ft_wall_hit(int col, float rayangle)
{
	t_run	mdr;

	mdr.foundhorzwallhit = FALSE;
	mdr.foundvertwallhit = FALSE;
	ft_horz(&mdr, rayangle);
	ft_vert(&mdr, rayangle);
	mdr.horzhitdistance = (mdr.foundhorzwallhit)
	? ft_distancebetweenpoints(g_player.x, g_player.y,
	mdr.horzwallhitx, mdr.horzwallhity) : INT_MAX;
	mdr.verthitdistance = (mdr.foundvertwallhit) ?
	ft_distancebetweenpoints(g_player.x, g_player.y,
	mdr.vertwallhitx, mdr.vertwallhity) : INT_MAX;
	g_wallhit.x = (mdr.horzhitdistance < mdr.verthitdistance)
	? mdr.horzwallhitx : mdr.vertwallhitx;
	g_wallhit.y = (mdr.horzhitdistance < mdr.verthitdistance)
	? mdr.horzwallhity : mdr.vertwallhity;
	g_wallhit.distance = (mdr.horzhitdistance < mdr.verthitdistance)
	? mdr.horzhitdistance : mdr.verthitdistance;
	g_wallhit.washitvertical = (mdr.verthitdistance < mdr.horzhitdistance);
	g_ray_distance[col] = g_wallhit.distance;
	ft_empty_trash(rayangle, col);
}

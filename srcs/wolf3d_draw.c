/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 19:59:03 by lfabbro           #+#    #+#             */
/*   Updated: 2016/11/13 20:24:08 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		wolf3d_flat(t_env *e, int pxl, int land)
{
	if (land == SKY1)
	{
		e->im.data[pxl] = SKY1;
		e->im.data[++pxl] = SKY2;
		e->im.data[++pxl] = SKY3;
	}
	else if (land == GROUND1)
	{
		e->im.data[pxl] = GROUND1;
		e->im.data[++pxl] = GROUND2;
		e->im.data[++pxl] = GROUND3;
	}
	else
	{
		e->im.data[pxl] = 0x55;
		e->im.data[++pxl] = 0x99;
		e->im.data[++pxl] = 0xff;
	}
}

static void		wolf3d_draw_loop(t_env *e, t_draw d, int x, int side)
{
	while (d.y < WIN_Y)
	{
		d.pxl = (x * 4) + (d.y * e->im.s_line);
		if (d.y == WIN_Y / 2)
			wolf3d_flat(e, d.pxl, 0);
		else
		{
			if (x == WIN_X / 2)
				wolf3d_flat(e, d.pxl, 0);
			else if (d.y >= d.lim_top && d.y <= d.lim_bot)
				wolf3d_draw_textr_column(e, d, side);
			else if (d.y < d.lim_top)
				wolf3d_flat(e, d.pxl, SKY1);
			else if (d.y > d.lim_bot)
				wolf3d_flat(e, d.pxl, GROUND1);
		}
		++d.y;
	}
}

static void		wolf3d_draw_column(t_env *e, double dist, int x, int side)
{
	t_draw	d;

	d.y = 0;
	d.x = x;
	d.w_height = (int)(WIN_Y / dist);
	d.lim_top = WIN_Y / 2 - d.w_height / 2;
	d.lim_top = (d.lim_top < 0) ? 0 : d.lim_top;
	d.lim_bot = WIN_Y / 2 + d.w_height / 2;
	d.lim_bot = (d.lim_bot > WIN_Y) ? WIN_Y - 1 : d.lim_bot;
	if (side == 1)
		d.wallx = e->ray.pos.y + dist * e->ray.dir.y;
	else
		d.wallx = e->ray.pos.x + dist * e->ray.dir.x;
	d.wallx -= floor((d.wallx));
	d.text_x = (int)(d.wallx * 64);
	if (side == 1 && e->ray.dir.x > 0)
		d.text_x = 64 - d.text_x - 1;
	if (side == 2 && e->ray.dir.y < 0)
		d.text_x = 64 - d.text_x - 1;
	wolf3d_draw_loop(e, d, x, side);
}

void			wolf3d_draw(t_env *e)
{
	int		x;
	int		side;
	double	dist;

	x = 0;
	while (x < WIN_X)
	{
		wolf3d_set(e, x);
		side = wolf3d_raycast(e);
		dist = wolf3d_wall_dist(e, side);
		wolf3d_draw_column(e, dist, x, side);
		++x;
	}
}

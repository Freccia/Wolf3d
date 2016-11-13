/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 20:08:33 by lfabbro           #+#    #+#             */
/*   Updated: 2016/11/13 20:24:11 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		wolf3d_change_lvl(t_env *e, int ev)
{
	if (ev == 4)
	{
		e->pl.pos.x = 2;
		e->pl.pos.y = 2;
		e->map = &e->maps.lvl2;
	}
	else if (ev == 3)
	{
		e->pl.pos.x = 2;
		e->pl.pos.y = 2;
		e->map = &e->maps.lvl1;
	}
}

static void		wolf3d_apply_moovements2(t_env *e)
{
	int		mv_x;
	int		mv_y;
	int		ev;

	mv_x = (int)(e->pl.pos.x - e->pl.dir.x * SPEED);
	mv_y = (int)(e->pl.pos.y - e->pl.dir.y * SPEED);
	if (!(ev = wolf3d_map(e->map, mv_x, e->pl.pos.y)) || ev > 2)
		e->pl.pos.x -= e->pl.dir.x * SPEED;
	if (!(ev = wolf3d_map(e->map, e->pl.pos.x, mv_y)) || ev > 2)
		e->pl.pos.y -= e->pl.dir.y * SPEED;
	if ((ev = wolf3d_map(e->map, e->pl.pos.x, e->pl.pos.y)) > 2)
		wolf3d_change_lvl(e, ev);
	wolf3d_new_img(e);
}

static void		wolf3d_apply_moovements(t_env *e)
{
	int		mv_x;
	int		mv_y;
	int		ev;

	if (e->event.mv < 0)
	{
		mv_x = (int)(e->pl.pos.x + e->pl.dir.x * SPEED);
		mv_y = (int)(e->pl.pos.y + e->pl.dir.y * SPEED);
		if (!(ev = wolf3d_map(e->map, mv_x, e->pl.pos.y)) || ev > 2)
			e->pl.pos.x += e->pl.dir.x * SPEED;
		if (!(ev = wolf3d_map(e->map, e->pl.pos.x, mv_y)) || ev > 2)
			e->pl.pos.y += e->pl.dir.y * SPEED;
		if ((ev = wolf3d_map(e->map, e->pl.pos.x, e->pl.pos.y)) > 2)
			wolf3d_change_lvl(e, ev);
		wolf3d_new_img(e);
	}
	else if (e->event.mv > 0)
	{
		wolf3d_apply_moovements2(e);
	}
}

static void		wolf3d_apply_rotation(t_env *e)
{
	double		dirx_tmp;
	double		planex_tmp;

	if (e->event.rot > 0)
	{
		dirx_tmp = e->pl.dir.x;
		e->pl.dir.x = e->pl.dir.x * cos(ANGLE) - e->pl.dir.y * sin(ANGLE);
		e->pl.dir.y = dirx_tmp * sin(ANGLE) + e->pl.dir.y * cos(ANGLE);
		planex_tmp = e->plane.x;
		e->plane.x = e->plane.x * cos(ANGLE) - e->plane.y * sin(ANGLE);
		e->plane.y = planex_tmp * sin(ANGLE) + e->plane.y * cos(ANGLE);
		wolf3d_new_img(e);
	}
	else if (e->event.rot < 0)
	{
		dirx_tmp = e->pl.dir.x;
		e->pl.dir.x = e->pl.dir.x * cos(-ANGLE) - e->pl.dir.y * sin(-ANGLE);
		e->pl.dir.y = dirx_tmp * sin(-ANGLE) + e->pl.dir.y * cos(-ANGLE);
		planex_tmp = e->plane.x;
		e->plane.x = e->plane.x * cos(-ANGLE) - e->plane.y * sin(-ANGLE);
		e->plane.y = planex_tmp * sin(-ANGLE) + e->plane.y * cos(-ANGLE);
		wolf3d_new_img(e);
	}
}

int				wolf3d_apply_event(t_env *e)
{
	wolf3d_apply_moovements(e);
	wolf3d_apply_rotation(e);
	return (0);
}

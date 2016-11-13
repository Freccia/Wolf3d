/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d_draw2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 20:08:16 by lfabbro           #+#    #+#             */
/*   Updated: 2016/11/13 20:24:09 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static double	wolf3d_set_delta(double v1, double v2)
{
	return (sqrt(1 + (v1 * v1) / (v2 * v2)));
}

static void		wolf3d_set_rays(t_env *e)
{
	if (e->ray.dir.x < 0)
	{
		e->step.x = -1;
		e->side.x = (e->ray.pos.x - (double)(e->p_map.x)) * e->delta.x;
	}
	else
	{
		e->step.x = 1;
		e->side.x = ((double)(e->p_map.x) + 1.0 - e->ray.pos.x) * e->delta.x;
	}
	if (e->ray.dir.y < 0)
	{
		e->step.y = -1;
		e->side.y = (e->ray.pos.y - (double)(e->p_map.y)) * e->delta.y;
	}
	else
	{
		e->step.y = 1;
		e->side.y = ((double)(e->p_map.y) + 1.0 - e->ray.pos.y) * e->delta.y;
	}
}

void			wolf3d_set(t_env *e, int x)
{
	e->ray.angle = 2 * x / (double)(WIN_X) - 1;
	e->ray.pos.x = e->pl.pos.x;
	e->ray.pos.y = e->pl.pos.y;
	e->ray.dir.x = e->pl.dir.x + e->plane.x * e->ray.angle;
	e->ray.dir.y = e->pl.dir.y + e->plane.y * e->ray.angle;
	e->p_map.x = (int)(e->ray.pos.x);
	e->p_map.y = (int)(e->ray.pos.y);
	e->delta.x = wolf3d_set_delta(e->ray.dir.y, e->ray.dir.x);
	e->delta.y = wolf3d_set_delta(e->ray.dir.x, e->ray.dir.y);
	wolf3d_set_rays(e);
}

double			wolf3d_wall_dist(t_env *e, int side)
{
	if (side == 1)
		return ((e->p_map.x - e->ray.pos.x + \
					(1 - e->step.x) / 2) / e->ray.dir.x);
	else
		return ((e->p_map.y - e->ray.pos.y + \
					(1 - e->step.y) / 2) / e->ray.dir.y);
}

int				wolf3d_raycast(t_env *e)
{
	int		hit;
	int		side;

	hit = 1;
	side = 1;
	while (1)
	{
		if (e->side.x < e->side.y)
		{
			e->side.x += e->delta.x;
			e->p_map.x += e->step.x;
			side = 1;
		}
		else
		{
			e->side.y += e->delta.y;
			e->p_map.y += e->step.y;
			side = 2;
		}
		if ((e->w_txt = wolf3d_map(e->map, e->p_map.x, e->p_map.y)))
			return (side);
	}
	return (side);
}

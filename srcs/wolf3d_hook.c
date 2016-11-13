/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <lfabbro@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 11:10:16 by lfabbro           #+#    #+#             */
/*   Updated: 2016/10/31 09:58:46 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int				wolf3d_quit(t_env *e)
{
	mlx_destroy_window(e->xx.ptr, e->xx.win);
	exit(0);
	return (0);
}

int				wolf3d_keyrelease(int keycode, t_env *e)
{
	if (keycode == DOWN)
	{
		e->event.mv = 0;
	}
	if (keycode == UP)
	{
		e->event.mv = 0;
	}
	if (keycode == RIGHT)
	{
		e->event.rot = 0;
	}
	if (keycode == LEFT)
	{
		e->event.rot = 0;
	}
	return (0);
}

int				wolf3d_keypress(int keycode, t_env *e)
{
	if (keycode == ESC_KEY)
	{
		wolf3d_quit(e);
	}
	if (keycode == DOWN)
	{
		e->event.mv = -1;
	}
	else if (keycode == UP)
	{
		e->event.mv = 1;
	}
	if (keycode == RIGHT)
	{
		e->event.rot = 1;
	}
	else if (keycode == LEFT)
	{
		e->event.rot = -1;
	}
	return (0);
}

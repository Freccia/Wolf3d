/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <lfabbro@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 23:37:49 by lfabbro           #+#    #+#             */
/*   Updated: 2016/11/13 19:56:44 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			wolf3d_new_img(t_env *e)
{
	e->im.ptr = mlx_new_image(e->xx.ptr, WIN_X + 5, WIN_Y + 5);
	e->im.data = mlx_get_data_addr(e->im.ptr, &e->im.bxp, &e->im.s_line, \
			&e->im.en);
	wolf3d_draw(e);
	mlx_put_image_to_window(e->xx.ptr, e->xx.win, e->im.ptr, 0, 0);
	mlx_destroy_image(e->xx.ptr, e->im.ptr);
}

static int		wolf3d_init_mlx(t_mlx *xx)
{
	if (!(xx->ptr = mlx_init()))
		return (1);
	if (!(xx->win = mlx_new_window(xx->ptr, WIN_X, WIN_Y, "Wolf3D")))
		return (1);
	return (0);
}

static int		wolf3d_init_env(t_env *e)
{
	if (wolf3d_init_mlx(&e->xx))
		return (1);
	e->pl.pos.x = 12;
	e->pl.pos.y = 12;
	e->pl.dir.x = 1;
	e->pl.dir.y = 0;
	e->plane.x = 0;
	e->plane.y = 0.66;
	e->event.mv = 0;
	e->event.rot = 0;
	wolf3d_set_map(&e->maps.lvl1, "maps/lvl01.map");
	wolf3d_set_map(&e->maps.lvl2, "maps/lvl02.map");
	e->map = &e->maps.lvl1;
	wolf3d_set_textures(e);
	return (0);
}

int				main(void)
{
	t_env	e;

	if (wolf3d_init_env(&e))
		return (-1);
	wolf3d_new_img(&e);
	mlx_hook(e.xx.win, KEY_PRESS, KEY_PRESS_MASK, wolf3d_keypress, &e);
	mlx_hook(e.xx.win, KEY_RELEASE, KEY_RELEASE_MASK, wolf3d_keyrelease, &e);
	mlx_hook(e.xx.win, DESTROYNOTIFY, STRUCTNOTIFY_MASK, wolf3d_quit, &e);
	mlx_loop_hook(e.xx.ptr, wolf3d_apply_event, &e);
	mlx_loop(e.xx.ptr);
	return (0);
}

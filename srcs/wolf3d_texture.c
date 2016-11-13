/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <lfabbro@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/01 19:04:27 by lfabbro           #+#    #+#             */
/*   Updated: 2016/11/13 19:58:52 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			wolf3d_draw_textr_column(t_env *e, t_draw d, int side)
{
	int		k;
	int		text_y;
	int		color;
	int		tx;

	tx = e->w_txt - 1;
	k = d.y * 256 - WIN_Y * 128 + d.w_height * 128;
	text_y = ((k * e->textr[tx].h) / d.w_height) / 256;
	color = e->textr[tx].data[e->textr[tx].s_line * text_y + \
			d.text_x * e->textr[tx].bxp / 8];
	if (side == 2)
		color = (color >> 1) & 0x7F7F7F;
	e->im.data[d.pxl] = color;
	e->im.data[++d.pxl] = color;
	e->im.data[++d.pxl] = color;
}

static void		wolf3d_charge_texture(t_env *e, t_textr *t, char *name)
{
	if (!(t->ptr = mlx_xpm_file_to_image(e->xx.ptr, name, &(t->w), &(t->h))))
	{
		ft_printf("Texture %s not found.\n", name);
		exit(1);
	}
	t->data = mlx_get_data_addr(t->ptr, &(t->bxp), &(t->s_line), &(t->en));
}

void			wolf3d_set_textures(t_env *e)
{
	wolf3d_charge_texture(e, &(e->textr[0]), "img/sci-fi.xpm");
	wolf3d_charge_texture(e, &(e->textr[1]), "img/brick.xpm");
	wolf3d_charge_texture(e, &(e->textr[2]), "img/door.xpm");
	wolf3d_charge_texture(e, &(e->textr[3]), "img/door.xpm");
}

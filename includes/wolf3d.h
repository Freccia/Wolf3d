/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/18 13:31:45 by lfabbro           #+#    #+#             */
/*   Updated: 2016/11/13 20:29:10 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

/*
**	INCLUDES
*/
# include "libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>

/*
**	ENVIRONMENT MACROS
*/
# define WIN_X		1280
# define WIN_Y		800
# define ANGLE		0.07
# define SPEED		0.18
# define MAP_X		24
# define MAP_Y		24

/*
**	COLORS
*/
# define SKY1				0xaa
# define SKY2				0x5a
# define SKY3				0x00
# define GROUND1			0x44
# define GROUND2			0x44
# define GROUND3			0x44

/*
**		KEYS
*/
# define ESC_KEY			53
# define LEFT				123
# define RIGHT				124
# define UP					125
# define DOWN				126

/*
**	MLX MACROS (X11)
*/
# define DESTROYNOTIFY 		17
# define STRUCTNOTIFY_MASK	(1L<<17)
# define KEY_PRESS_MASK 	(1L<<0)
# define KEY_RELEASE_MASK 	(1L<<1)
# define KEY_PRESS			2
# define KEY_RELEASE 		3

typedef struct		s_mlx
{
	void			*ptr;
	void			*win;
}					t_mlx;

typedef struct		s_img
{
	void			*ptr;
	char			*data;
	int				bxp;
	int				s_line;
	int				en;
}					t_img;

typedef struct		s_point
{
	int				x;
	int				y;
}					t_point;

typedef struct		s_podbl
{
	double			x;
	double			y;
}					t_podbl;

typedef struct		s_event
{
	int				mv;
	int				rot;
}					t_event;

typedef struct		s_ray
{
	double			angle;
	t_podbl			pos;
	t_podbl			dir;
}					t_ray;

typedef struct		s_player
{
	t_podbl			pos;
	t_podbl			dir;
}					t_player;

typedef struct		s_textr
{
	void			*ptr;
	char			*data;
	int				bxp;
	int				s_line;
	int				en;
	int				w;
	int				h;
}					t_textr;

typedef struct		s_draw
{
	int				y;
	int				x;
	int				pxl;
	int				lim_top;
	int				lim_bot;
	int				w_height;
	double			wallx;
	int				text_x;
}					t_draw;

typedef struct		s_maps
{
	int				lvl1[24][24];
	int				lvl2[24][24];
}					t_maps;

typedef struct		s_env
{
	t_mlx			xx;
	t_img			im;
	t_player		pl;
	t_ray			ray;
	t_textr			textr[5];
	t_event			event;
	t_podbl			plane;
	t_podbl			side;
	t_podbl			delta;
	t_point			step;
	t_point			p_map;
	t_point			map_size;
	t_maps			maps;
	int				(*map)[24][24];
	int				w_txt;
}					t_env;

void				wolf3d_new_img(t_env *e);
void				wolf3d_set_map(int (*map)[24][24], char *file);
int					wolf3d_map(int (*map)[24][24], int x, int y);
int					wolf3d_keypress(int keycode, t_env *e);
int					wolf3d_keyrelease(int keycode, t_env *e);
int					wolf3d_apply_event(t_env *e);
int					wolf3d_quit(t_env *e);
void				wolf3d_draw(t_env *e);
void				wolf3d_draw_textr_column(t_env *e, t_draw d, int side);
void				wolf3d_draw_textr_floor(t_env *e, t_draw d);
void				wolf3d_set_textures(t_env *e);
void				wolf3d_set(t_env *e, int x);
int					wolf3d_raycast(t_env *e);
double				wolf3d_wall_dist(t_env *e, int side);

#endif

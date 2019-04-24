/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   incwol.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlemahie <jlemahie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 23:25:44 by jlemahie          #+#    #+#             */
/*   Updated: 2018/11/23 17:22:16 by jlemahie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCWOL_H
# define INCWOL_H

# include "../lib/include/inclib.h"
# include "../minilibx_macos/mlx.h"
# include <math.h>
# include <fcntl.h>

typedef struct	s_text
{
	int		bpp;
	int		s_l;
	int		end;
	void	*text[12];
	char	*tex[12];
}				t_text;

typedef struct	s_image
{
	void	*img;
	char	*pxl;
	int		bpp;
	int		s_l;
	int		end;
}				t_image;

typedef struct	s_point
{
	double	x;
	double	y;
}				t_point;

typedef struct	s_wall
{
	double	height;
	int		type;
	int		c;
	int		o;
	int		orientation;
}				t_wall;

typedef struct	s_mlx
{
	int		width;
	int		height;
	int		**worldmap;
	void	*mlx;
	int		lv;
	int		id;
	void	*win;
	double	angle;
	char	*tepath;
	char	*mapath;
	int		op;
	int		key;
	t_image	map;
	t_image	world;
	t_image menu;
	t_image sky;
	t_image lsky;
	t_image lmenu;
	int		men;
	t_point	pos;
	double	cosangle;
	t_text	texture;
}				t_mlx;

int				ft_catoi(const char *nptr);
void			ft_ac(t_mlx *mlx);
t_wall			ft_checkwall(t_mlx *mlx, t_point a, int xinc, int yinc);
void			ft_mv(t_mlx *mlx, int key);
int				ft_door(t_mlx *mlx);
int				clwin(t_mlx *mlx);
void			render_map(t_mlx *mlx);
void			ft_clrtext(t_mlx *mlx, char *err);
void			ft_clrscl(t_mlx *mlx, char *err);
void			ft_clrscn(t_mlx *mlx, char *err);
void			ft_exit(t_mlx *mlx, char *err);
void			ft_initlvl(t_mlx *mlx);
void			ft_init(t_mlx *mlx, char *path, char *start);
int				deal_butt(int button, int x, int y, t_mlx *mlx);
void			ft_drawmenu(t_mlx *mlx);
void			ft_upscalesky(t_mlx *mlx, int o);
void			ft_free_worldmap(t_mlx *mlx);
void			ray_cone(t_mlx *mlx);
void			parse(char *filename, t_mlx *mlx);
void			render(t_mlx *mlx);
int				deal_key(int key, t_mlx *mlx);
int				mouse_pos(int x, int y, t_mlx *mlx);
void			ft_drawline(t_mlx *mlx, t_wall wall, int i, int j);
void			ft_initskmn(t_mlx *mlx);
#endif

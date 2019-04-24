/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlemahie <jlemahie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 20:20:26 by jlemahie          #+#    #+#             */
/*   Updated: 2018/11/23 16:45:12 by rchevass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/incwol.h"

static void	ft_pathmap(t_mlx *mlx, char *str)
{
	int len;

	len = ft_strlen(str);
	if ((mlx->mapath = ft_strnew(len - 1)) == NULL)
	{
		mlx_destroy_image(mlx->mlx, mlx->map.img);
		mlx_destroy_image(mlx->mlx, mlx->world.img);
		ft_clrscl(mlx, "Erreur malloc");
	}
	mlx->mapath = ft_strncpy(mlx->mapath, str, len - 6);
	mlx->mapath = ft_strcat(mlx->mapath, "maps/");
}

static void	ft_pathext(t_mlx *mlx, char *str)
{
	int len;

	len = ft_strlen(str);
	if ((mlx->tepath = ft_strnew(len + 3)) == NULL)
		exit(0);
	mlx->tepath = ft_strncpy(mlx->tepath, str, len - 6);
	mlx->tepath = ft_strcat(mlx->tepath, "textures/");
}

static int	ft_initpos(t_mlx *mlx)
{
	int i;
	int j;

	j = 1;
	while (j < mlx->height - 1)
	{
		i = 1;
		while (i < mlx->width - 1)
		{
			if (mlx->worldmap[j][i] == 0)
			{
				mlx->pos.x = j * 32 + 16;
				mlx->pos.y = i * 32 + 16;
				return (1);
			}
			i++;
		}
		j++;
	}
	ft_exit(mlx, "Erreur pas de pos");
	return (0);
}

void		ft_initlvl(t_mlx *mlx)
{
	char *s;
	char *l;

	if (mlx->lv == 4)
		ft_exit(mlx, "Fin du jeu");
	else
	{
		if (!(l = ft_itoa(mlx->lv)))
			ft_exit(mlx, "Malloc error");
		s = ft_strjoin("lvl", l);
		ft_strdel(&l);
		if (s == NULL)
			ft_exit(mlx, "Malloc error");
	}
	mlx->key = 0;
	ft_free_worldmap(mlx);
	if (!(l = ft_strjoin(mlx->mapath, s)))
		ft_exit(mlx, "Malloc error");
	ft_strdel(&s);
	parse(l, mlx);
	ft_initpos(mlx);
	mlx_mouse_hide();
	mlx->men = 0;
	render(mlx);
}

void		ft_init(t_mlx *mlx, char *path, char *start)
{
	mlx->key = 0;
	ft_pathext(mlx, path);
	ft_initskmn(mlx);
	ft_drawmenu(mlx);
	ft_upscalesky(mlx, 0);
	if ((mlx->map.img = mlx_new_image(mlx->mlx, 240, 240)) == NULL)
		ft_clrscl(mlx, "Erreur alloc map");
	mlx->map.pxl = mlx_get_data_addr(mlx->map.img, &mlx->map.bpp,
				&mlx->map.s_l, &mlx->map.end);
	if ((mlx->world.img = mlx_new_image(mlx->mlx, 1920, 1080)) == NULL)
	{
		mlx_destroy_image(mlx->mlx, mlx->map.img);
		ft_clrscl(mlx, "Erreur alloc world");
	}
	mlx->world.pxl = mlx_get_data_addr(mlx->world.img, &mlx->world.bpp,
				&mlx->world.s_l, &mlx->world.end);
	ft_pathmap(mlx, path);
	if (ft_strcmp(start, "lvl1") == 0)
		parse(ft_strjoin(mlx->mapath, start), mlx);
	else
		parse(ft_strdup(start), mlx);
	ft_initpos(mlx);
	mlx->win = mlx_new_window(mlx->mlx, 1920, 1080, "wolf3d");
}

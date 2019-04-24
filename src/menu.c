/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlemahie <jlemahie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 01:40:48 by jlemahie          #+#    #+#             */
/*   Updated: 2018/09/14 08:04:41 by jlemahie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/incwol.h"

static void	ft_pixelmenu(t_mlx *mlx, int x, int y, int o)
{
	int i;

	i = (y * (mlx->menu.s_l)) + (x * (mlx->menu.bpp / 8));
	mlx->menu.pxl[i] = mlx->lmenu.pxl[o];
	mlx->menu.pxl[i + 1] = mlx->lmenu.pxl[o + 1];
	mlx->menu.pxl[i + 2] = mlx->lmenu.pxl[o + 2];
}

static void	scalemenu(int x, int y, t_mlx *mlx, int o)
{
	int i;
	int j;

	i = 0;
	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			ft_pixelmenu(mlx, 10 * x + i, 10 * y + j, o);
			j++;
		}
		i++;
	}
}

void		ft_drawmenu(t_mlx *mlx)
{
	int x;
	int y;
	int o;

	x = 0;
	y = 0;
	if ((mlx->menu.img = mlx_new_image(mlx->mlx, 1920, 1080)) == NULL)
	{
		mlx_destroy_image(mlx->mlx, mlx->lmenu.img);
		ft_clrtext(mlx, "Erreur alloc menu");
	}
	mlx->menu.pxl = mlx_get_data_addr(mlx->menu.img, &mlx->menu.bpp,
				&mlx->menu.s_l, &mlx->menu.end);
	while (y < 108)
	{
		x = 0;
		while (x < 192)
		{
			o = (y * (mlx->lmenu.s_l)) + (x * (mlx->lmenu.bpp / 8));
			scalemenu(x, y, mlx, o);
			x++;
		}
		y++;
	}
	mlx_destroy_image(mlx->mlx, mlx->lmenu.img);
}

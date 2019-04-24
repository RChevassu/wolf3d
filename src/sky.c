/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sky.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlemahie <jlemahie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 01:40:48 by jlemahie          #+#    #+#             */
/*   Updated: 2018/09/14 08:00:52 by jlemahie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/incwol.h"

static void	ft_pixelsky(t_mlx *mlx, int x, int y, int o)
{
	int i;

	i = (y * (mlx->sky.s_l)) + (x * (mlx->sky.bpp / 8));
	mlx->sky.pxl[i] = mlx->lsky.pxl[o];
	mlx->sky.pxl[i + 1] = mlx->lsky.pxl[o + 1];
	mlx->sky.pxl[i + 2] = mlx->lsky.pxl[o + 2];
}

static void	scalesky(int x, int y, t_mlx *mlx, int o)
{
	int i;
	int j;

	i = 0;
	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			ft_pixelsky(mlx, 10 * x + i, 10 * y + j, o);
			j++;
		}
		i++;
	}
}

void		ft_upscalesky(t_mlx *mlx, int o)
{
	int x;
	int y;

	x = 0;
	y = 0;
	mlx->sky.img = mlx_new_image(mlx->mlx, 2160, 540);
	mlx_destroy_image(mlx->mlx, mlx->lsky.img);
	if (mlx->sky.img == NULL)
	{
		mlx_destroy_image(mlx->mlx, mlx->menu.img);
		ft_clrtext(mlx, "Erreur alloc sky");
	}
	mlx->sky.pxl = mlx_get_data_addr(mlx->sky.img, &mlx->sky.bpp,
				&mlx->sky.s_l, &mlx->sky.end);
	while (y < 54)
	{
		x = 0;
		while (x < 216)
		{
			o = (y * (mlx->lsky.s_l)) + (x * (mlx->lsky.bpp / 8));
			scalesky(x, y, mlx, o);
			x++;
		}
		y++;
	}
}

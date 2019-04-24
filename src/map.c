/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlemahie <jlemahie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/14 07:41:44 by jlemahie          #+#    #+#             */
/*   Updated: 2018/09/16 07:05:46 by jlemahie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/incwol.h"

static void	ft_pospl(t_mlx *mlx, int x, int y)
{
	int i;
	int x1;
	int y1;

	x1 = x - 1;
	while (x1 < x + 1)
	{
		y1 = y - 1;
		while (y1 < y + 1)
		{
			if (x1 < 240 && y1 < 240 && x1 >= 0 && y1 >= 0)
			{
				i = (y1 * (mlx->map.s_l)) + (x1 * (mlx->map.bpp / 8));
				mlx->map.pxl[i] = (char)255;
				mlx->map.pxl[i + 1] = (char)255;
				mlx->map.pxl[i + 2] = (char)255;
			}
			y1++;
		}
		x1++;
	}
}

static void	ft_poswl(int x, int y, t_mlx *mlx, int type)
{
	int i;
	int j;
	int m;
	int o;

	i = 0;
	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			m = (y * 10 + j) * (mlx->map.s_l) +
				(x * 10 + i) * (mlx->map.bpp / 8);
			o = i * 3 * mlx->texture.s_l + j * 3 * mlx->texture.bpp / 8;
			mlx->map.pxl[m] = (type == 0) ? 0 : mlx->texture.tex[type][o];
			mlx->map.pxl[m + 1] = (type == 0) ? 0 :
				mlx->texture.tex[type][o + 1];
			mlx->map.pxl[m + 2] = (type == 0) ? 0 :
				mlx->texture.tex[type][o + 2];
			j++;
		}
		i++;
	}
}

static void	ft_drmap(t_mlx *mlx, int startx, int starty)
{
	int x;
	int y;

	x = 0;
	while (x < 24)
	{
		y = 0;
		while (y < 24)
		{
			if (x + startx >= mlx->width || y + starty >= mlx->height)
				ft_poswl(x, y, mlx, 0);
			else
				ft_poswl(x, y, mlx, mlx->worldmap[y + starty][x + startx]);
			y++;
		}
		x++;
	}
}

void		render_map(t_mlx *mlx)
{
	int startx;
	int starty;

	starty = (mlx->pos.x / 32) - 12;
	startx = (mlx->pos.y / 32) - 12;
	if (starty < 0)
		starty = 0;
	else if (starty + 24 >= mlx->height && starty + 24 > 24)
		starty = ((mlx->height - 24) < 0) ? 0 : mlx->height - 24;
	if (startx < 0)
		startx = 0;
	else if (startx + 24 > mlx->width && startx + 24 > 24)
		startx = ((mlx->width - 24) < 0) ? 0 : mlx->width - 24;
	ft_drmap(mlx, startx, starty);
	ft_pospl(mlx, (mlx->pos.y / 3.2) - (startx * 10), (mlx->pos.x / 3.2) -
		(starty * 10));
}

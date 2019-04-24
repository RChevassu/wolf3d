/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlemahie <jlemahie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 19:48:38 by jlemahie          #+#    #+#             */
/*   Updated: 2018/11/21 16:02:41 by rchevass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/incwol.h"

static void	ft_lat(t_mlx *mlx, double dir)
{
	int	x;
	int	y;

	x = (int)(mlx->pos.x - 7 * cos(mlx->angle + dir)) / 32;
	y = (int)(mlx->pos.y - 7 * sin(mlx->angle + dir)) / 32;
	if (x < mlx->height - 1 && x > 0 && y < mlx->width - 1 && y > 0)
	{
		if (mlx->worldmap[x][y] == 0)
		{
			mlx->pos.x -= 7 * cos(mlx->angle + dir);
			mlx->pos.y -= 7 * sin(mlx->angle + dir);
			render(mlx);
		}
	}
}

static void	ft_frt(t_mlx *mlx, double dir)
{
	int	x;
	int	y;

	x = (int)(mlx->pos.x + (dir * 7 * cos(mlx->angle))) / 32;
	y = (int)(mlx->pos.y + (dir * 7 * sin(mlx->angle))) / 32;
	if (x < mlx->height - 1 && x > 0 && y < mlx->width - 1 && y > 0)
	{
		if (mlx->worldmap[x][y] == 0)
		{
			mlx->pos.x += dir * 7 * cos(mlx->angle);
			mlx->pos.y += dir * 7 * sin(mlx->angle);
			render(mlx);
		}
	}
}

void		ft_mv(t_mlx *mlx, int key)
{
	if (key == 123)
		ft_lat(mlx, -1.67);
	else if (key == 124)
		ft_lat(mlx, 1.67);
	else if (key == 125)
		ft_frt(mlx, -1);
	else if (key == 126)
		ft_frt(mlx, 1);
}

void		ft_ac(t_mlx *mlx)
{
	int x;
	int y;

	x = (int)(mlx->pos.x + (45 * cos(mlx->angle))) / 32;
	y = (int)(mlx->pos.y + (45 * sin(mlx->angle))) / 32;
	if (mlx->worldmap[x][y] == 5)
	{
		mlx->lv++;
		mlx_mouse_show();
		ft_initlvl(mlx);
	}
	else if (mlx->worldmap[x][y] == 6)
	{
		mlx->worldmap[x][y] = 7;
		mlx->op++;
	}
	else if (mlx->worldmap[x][y] == 8 && mlx->key++ == 1)
		render(mlx);
	else if (mlx->worldmap[x][y] == 4 && mlx->key > 0)
	{
		mlx->worldmap[x][y] = 7;
		mlx->op++;
	}
}

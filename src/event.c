/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlemahie <jlemahie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/14 07:35:49 by jlemahie          #+#    #+#             */
/*   Updated: 2018/09/16 03:10:33 by jlemahie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/incwol.h"

int	ft_door(t_mlx *mlx)
{
	if (mlx->op != 0)
	{
		mlx->op++;
		if (mlx->op == 32)
		{
			mlx->worldmap[(int)(mlx->pos.x + (45 *
				cos(mlx->angle))) / 32][(int)(mlx->pos.y +
					(45 * sin(mlx->angle))) / 32] = 0;
			mlx->op = 0;
		}
		render(mlx);
	}
	return (0);
}

int	clwin(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->win);
	mlx->win = NULL;
	ft_exit(mlx, "");
	return (0);
}

int	deal_key(int key, t_mlx *mlx)
{
	if (key == 53)
		ft_exit(mlx, "");
	if (mlx->men == 0 && mlx->op == 0)
	{
		if (key == 123 || key == 124 || key == 125 || key == 126)
			ft_mv(mlx, key);
		else if (key == 49)
			ft_ac(mlx);
		else if (key == 36)
		{
			mlx_mouse_show();
			mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->menu.img, 0, 0);
			mlx->men = 1;
		}
	}
	else if (mlx->men == 1 && key == 36)
	{
		mlx_mouse_hide();
		mlx->men = 0;
		render(mlx);
	}
	return (0);
}

int	mouse_pos(int x, int y, t_mlx *mlx)
{
	if (mlx->men == 0 && mlx->op == 0)
	{
		if (x < 960)
			mlx->angle += 0.1;
		else if (x > 960)
			mlx->angle -= 0.1;
		y = 0;
		mlx_mouse_move(mlx->win, 960, 540);
		render(mlx);
	}
	return (0);
}

int	deal_butt(int button, int x, int y, t_mlx *mlx)
{
	if (mlx->men == 1)
	{
		if (x >= 1810 && x <= 1890 && y >= 40 && y <= 120)
			ft_exit(mlx, "");
		if (x >= 40 && x <= 280 && y >= 40 && y <= 160)
			deal_key(36, mlx);
		if (x >= 570 && x <= 1350 && y >= 540 && y <= 660)
		{
			mlx->lv = 1;
			ft_initlvl(mlx);
		}
		if (x >= 570 && x <= 1350 && y >= 700 && y <= 820)
		{
			mlx->lv = 2;
			ft_initlvl(mlx);
		}
		if (x >= 570 && x <= 1350 && y >= 860 && y <= 980)
		{
			mlx->lv = 3;
			ft_initlvl(mlx);
		}
	}
	return (button);
}

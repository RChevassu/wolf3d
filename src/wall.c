/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlemahie <jlemahie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/14 08:19:05 by jlemahie          #+#    #+#             */
/*   Updated: 2018/09/24 21:50:24 by rchevass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/incwol.h"

static int	ft_get_orientation(int xinc, int yinc, t_wall wall)
{
	if (wall.type != 8)
		return (0);
	if (xinc == 0 && yinc > 0)
		return (1);
	else if (xinc == 0 && yinc < 0)
		return (3);
	else if (yinc == 0 && xinc > 0)
		return (0);
	else if (yinc == 0 && xinc < 0)
		return (2);
	return (0);
}

static void	ft_getwall(t_point a, t_wall *wall, t_mlx *mlx)
{
	double height;
	double coef;

	height = sqrt((double)(pow((a.x - mlx->pos.x), 2))
		+ (double)(pow((a.y - mlx->pos.y), 2)));
	coef = (double)1662 * 32 / height;
	wall->height = coef;
}

static int	ft_trens(t_mlx *mlx, t_wall wall, int mapx, int mapy)
{
	wall.type = mlx->worldmap[mapx][mapy];
	if (wall.type == 7 && wall.c % 32 + mlx->op >= 32)
		return (0);
	return (wall.type);
}

t_wall		ft_checkwall(t_mlx *mlx, t_point a, int xinc, int yinc)
{
	t_wall	wall;
	int		mapx;
	int		mapy;
	int		xi;
	int		yi;

	wall.height = 0;
	wall.type = -1;
	if ((a.x <= 0 || a.x >= 32 * mlx->height) ||
		(a.y <= 0 || a.y >= 32 * mlx->width))
		return (wall);
	wall.c = (xinc == 0) ? a.x : a.y;
	xi = (xinc > 0) ? 0 : xinc;
	yi = (yinc > 0) ? 0 : yinc;
	mapx = (int)(a.x / 32) + xi;
	mapy = (int)(a.y / 32) + yi;
	wall.type = ft_trens(mlx, wall, mapx, mapy);
	if (wall.type != 0)
	{
		wall.orientation = ft_get_orientation(xinc, yinc, wall);
		ft_getwall(a, &wall, mlx);
	}
	return (wall);
}

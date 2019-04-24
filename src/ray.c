/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchevass <rchevass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 15:47:05 by rchevass          #+#    #+#             */
/*   Updated: 2018/11/23 16:41:58 by rchevass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/incwol.h"
#include <pthread.h>

static t_wall	ft_horizontal(t_point a, t_point b, t_mlx *mlx, t_point coef)
{
	int		yinc;
	int		xinc;
	t_point	intersection;

	yinc = (b.y > 0) ? 1 : -1;
	xinc = (b.x > 0) ? 1 : -1;
	if (yinc > 0)
		intersection.y = (int)(a.y / 32) * 32 + 32;
	else
		intersection.y = (int)(a.y / 32) * 32;
	intersection.x = a.x + fabs(a.y - intersection.y) * coef.y * xinc;
	while (ft_checkwall(mlx, intersection, 0, yinc).type == 0)
	{
		intersection.x += 32 * coef.y * xinc;
		intersection.y += 32 * yinc;
	}
	return (ft_checkwall(mlx, intersection, 0, yinc));
}

static t_wall	ft_vertical(t_point a, t_point b, t_mlx *mlx, t_point coef)
{
	int		xinc;
	int		yinc;
	t_point	intersection;

	xinc = (b.x > 0) ? 1 : -1;
	yinc = (b.y > 0) ? 1 : -1;
	if (xinc > 0)
		intersection.x = (int)(a.x / 32) * 32 + 32;
	else
		intersection.x = (int)(a.x / 32) * 32;
	intersection.y = a.y + fabs((a.x - intersection.x)) * coef.x * yinc;
	while (ft_checkwall(mlx, intersection, xinc, 0).type == 0)
	{
		intersection.x += 32 * xinc;
		intersection.y += 32 * coef.x * yinc;
	}
	return (ft_checkwall(mlx, intersection, xinc, 0));
}

static void		ft_bresenham(t_point a, t_point b, t_mlx *mlx, int i)
{
	t_wall	v;
	t_wall	h;
	t_point	coef;

	b.x = b.x - a.x;
	b.y = b.y - a.y;
	coef.x = fabs(b.y / b.x);
	coef.y = fabs(b.x / b.y);
	if (b.x == 0)
		coef.y = 0.0001;
	if (b.y == 0)
		coef.x = 0.0001;
	v = ft_vertical(a, b, mlx, coef);
	h = ft_horizontal(a, b, mlx, coef);
	if (h.height >= v.height)
		v = h;
	ft_drawline(mlx, v, i, 0);
}

void			*sous_fonction(void *arg)
{
	t_point	depart;
	t_point	arrivee;
	t_point	step;
	t_mlx	*mlx;
	t_point	id;

	mlx = (t_mlx *)arg;
	id.x = mlx->id;
	mlx->id++;
	depart.x = 1662 * cos(mlx->angle + 0.52) + mlx->pos.x;
	depart.y = 1662 * sin(mlx->angle + 0.52) + mlx->pos.y;
	arrivee.x = 1662 * cos(mlx->angle - 0.52) + mlx->pos.x;
	arrivee.y = 1662 * sin(mlx->angle - 0.52) + mlx->pos.y;
	step.x = (double)(arrivee.x - depart.x) / 1920;
	step.y = (double)(arrivee.y - depart.y) / 1920;
	id.y = id.x * 480;
	while (id.y < (id.x + 1) * 480)
	{
		arrivee.x = (id.y * step.x) + depart.x;
		arrivee.y = (id.y * step.y) + depart.y;
		ft_bresenham(mlx->pos, arrivee, mlx, id.y);
		id.y++;
	}
	return (NULL);
}

void			ray_cone(t_mlx *mlx)
{
	pthread_t	threads[4];
	int			i;

	mlx->id = 0;
	i = 0;
	while (i < 4)
	{
		pthread_create(&(threads[i]), NULL, sous_fonction, mlx);
		i++;
	}
	i = 0;
	while (i < 4)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}

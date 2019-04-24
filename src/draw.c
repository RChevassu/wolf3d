/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlemahie <jlemahie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 17:52:07 by jlemahie          #+#    #+#             */
/*   Updated: 2018/11/23 17:05:24 by rchevass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/incwol.h"

static void	ft_drawsky(t_mlx *mlx, int k, int i)
{
	int m;
	int j;

	j = 0;
	while (j < 1080 && j < k)
	{
		m = (j * (mlx->world.s_l)) + i;
		mlx->world.pxl[m] = (char)0;
		mlx->world.pxl[m + 1] = (char)0;
		mlx->world.pxl[m + 2] = (char)0;
		mlx->world.pxl[m + 3] = (char)255;
		j++;
	}
}

static void	ft_drawfloor(t_mlx *mlx, int j, int k, int i)
{
	int	m;

	while ((j + k) < 1080)
	{
		m = ((j + k) * (mlx->world.s_l)) + i;
		mlx->world.pxl[m] = (char)50;
		mlx->world.pxl[m + 1] = (char)50;
		mlx->world.pxl[m + 2] = (char)50;
		mlx->world.pxl[m + 3] = (char)0;
		j++;
	}
}

static void	ft_strncpyw(char *s1, char *s2, int len)
{
	int	i;

	i = 0;
	while (i != len)
	{
		s1[i] = s2[i];
		i++;
	}
}

static void	ft_pixeltex(t_mlx *mlx, t_wall wall, char *str, int m)
{
	mlx->world.pxl[m] = str[wall.o];
	mlx->world.pxl[m + 1] = str[wall.o + 1];
	mlx->world.pxl[m + 2] = str[wall.o + 2];
	mlx->world.pxl[m + 3] = 0;
}

void		ft_drawline(t_mlx *mlx, t_wall wall, int i, int j)
{
	int		k;
	int		l;
	char	str[mlx->texture.s_l];
	int		m;
	int		height;

	height = wall.height / cos(-(M_PI / 6) + (i * 0.000545415391));
	k = (height > 1080) ? 0 : 540 - (height / 2);
	l = (height > 1080) ? height / 2 - 540 : 0;
	j = 0;
	if (wall.type > 0)
		ft_strncpyw(str, &mlx->texture.tex[wall.orientation + wall.type]
			[mlx->texture.s_l * (wall.c % 32)], mlx->texture.s_l);
	i *= 4;
	ft_drawsky(mlx, k, i);
	while (j < height && j < 1080)
	{
		wall.o = ((j + l) * 32 / height * 4);
		m = ((j + k) * (mlx->world.s_l)) + i;
		ft_pixeltex(mlx, wall, str, m);
		j++;
	}
	ft_drawfloor(mlx, j, k, i);
}

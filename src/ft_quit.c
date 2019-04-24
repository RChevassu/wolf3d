/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlemahie <jlemahie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/14 06:24:49 by jlemahie          #+#    #+#             */
/*   Updated: 2018/09/16 00:47:05 by jlemahie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/incwol.h"

void	ft_free_worldmap(t_mlx *mlx)
{
	int i;

	i = 0;
	while (i < mlx->height)
	{
		free(mlx->worldmap[i]);
		i++;
	}
	free(mlx->worldmap);
}

void	ft_clrtext(t_mlx *mlx, char *err)
{
	int i;

	i = 0;
	while (i <= 11)
	{
		mlx_destroy_image(mlx->mlx, mlx->texture.text[i]);
		i++;
	}
	ft_putstr_fd(err, 2);
	if (mlx->win != NULL)
		mlx_destroy_window(mlx->mlx, mlx->win);
	exit(0);
}

void	ft_clrscl(t_mlx *mlx, char *err)
{
	mlx_destroy_image(mlx->mlx, mlx->sky.img);
	mlx_destroy_image(mlx->mlx, mlx->menu.img);
	ft_clrtext(mlx, err);
}

void	ft_clrscn(t_mlx *mlx, char *err)
{
	mlx_destroy_image(mlx->mlx, mlx->map.img);
	mlx_destroy_image(mlx->mlx, mlx->world.img);
	ft_strdel(&mlx->mapath);
	ft_clrscl(mlx, err);
}

void	ft_exit(t_mlx *mlx, char *err)
{
	ft_free_worldmap(mlx);
	ft_clrscn(mlx, err);
}

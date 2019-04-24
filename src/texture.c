/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlemahie <jlemahie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 19:36:49 by jlemahie          #+#    #+#             */
/*   Updated: 2018/11/23 16:49:26 by rchevass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/incwol.h"

static void	ft_initexture(t_mlx *mlx, int i, char *str)
{
	int h;
	int w;

	if ((mlx->texture.text[i] =
		mlx_xpm_file_to_image(mlx->mlx, str, &w, &h)) == NULL)
	{
		i--;
		ft_strdel(&str);
		while (i != -1)
		{
			mlx_destroy_image(mlx->mlx, mlx->texture.text[i]);
			i--;
		}
		mlx_destroy_image(mlx->mlx, mlx->lsky.img);
		mlx_destroy_image(mlx->mlx, mlx->lmenu.img);
		ft_strdel(&mlx->tepath);
		ft_putstr_fd("Erreur missing texture", 2);
		exit(0);
	}
	mlx->texture.tex[i] = mlx_get_data_addr(mlx->texture.text[i],
		&mlx->texture.bpp, &mlx->texture.s_l, &mlx->texture.end);
	ft_strdel(&str);
}

static void	ft_initextures(t_mlx *mlx)
{
	ft_initexture(mlx, 0, ft_strjoin(mlx->tepath, "key.xpm"));
	ft_initexture(mlx, 1, ft_strjoin(mlx->tepath, "wall1.xpm"));
	ft_initexture(mlx, 2, ft_strjoin(mlx->tepath, "wall2.xpm"));
	ft_initexture(mlx, 3, ft_strjoin(mlx->tepath, "wallbar.xpm"));
	ft_initexture(mlx, 4, ft_strjoin(mlx->tepath, "lock.xpm"));
	ft_initexture(mlx, 5, ft_strjoin(mlx->tepath, "garfield.xpm"));
	ft_initexture(mlx, 6, ft_strjoin(mlx->tepath, "door.xpm"));
	ft_initexture(mlx, 7, ft_strjoin(mlx->tepath, "doorop.xpm"));
	ft_initexture(mlx, 8, ft_strjoin(mlx->tepath, "computer.xpm"));
	ft_initexture(mlx, 9, ft_strjoin(mlx->tepath, "right.xpm"));
	ft_initexture(mlx, 10, ft_strjoin(mlx->tepath, "back.xpm"));
	ft_initexture(mlx, 11, ft_strjoin(mlx->tepath, "left.xpm"));
	mlx->lmenu.pxl = mlx_get_data_addr(mlx->lmenu.img, &mlx->lmenu.bpp,
				&mlx->lmenu.s_l, &mlx->lmenu.end);
	mlx->lsky.pxl = mlx_get_data_addr(mlx->lsky.img, &mlx->lsky.bpp,
				&mlx->lsky.s_l, &mlx->lsky.end);
	ft_strdel(&mlx->tepath);
}

void		ft_initskmn(t_mlx *mlx)
{
	int		w;
	int		h;
	char	*str;

	str = ft_strjoin(mlx->tepath, "menu.xpm");
	if ((mlx->lmenu.img = mlx_xpm_file_to_image(mlx->mlx, str, &w, &h)) == NULL)
	{
		ft_putstr_fd("Erreur missing menu", 2);
		ft_strdel(&mlx->tepath);
		ft_strdel(&str);
		exit(0);
	}
	ft_strdel(&str);
	str = ft_strjoin(mlx->tepath, "sky.xpm");
	if ((mlx->lsky.img = mlx_xpm_file_to_image(mlx->mlx, str, &w, &h)) == NULL)
	{
		ft_putstr_fd("Erreur missing sky", 2);
		mlx_destroy_image(mlx->mlx, mlx->lmenu.img);
		ft_strdel(&mlx->tepath);
		ft_strdel(&str);
		exit(0);
	}
	ft_strdel(&str);
	ft_initextures(mlx);
}

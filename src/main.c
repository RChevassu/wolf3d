/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlemahie <jlemahie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 23:25:02 by jlemahie          #+#    #+#             */
/*   Updated: 2018/11/23 17:21:55 by jlemahie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/incwol.h"

int			ft_catoi(const char *nptr)
{
	int i;

	i = 0;
	while (nptr[i])
	{
		if (ft_isdigit(nptr[i]) == 0)
			return (-1);
		i++;
	}
	return (ft_atoi(nptr));
}

static void	ft_draw_sky(t_mlx *mlx)
{
	int i;

	i = (int)((1920 * 6 * mlx->angle) / (M_PI * 2)) % 2160;
	if (i > 0)
		i -= 2160;
	while (i < 1920)
	{
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->sky.img, i, 0);
		i += 2160;
	}
}

void		render(t_mlx *mlx)
{
	mlx_clear_window(mlx->mlx, mlx->win);
	mlx->men = 0;
	render_map(mlx);
	ft_draw_sky(mlx);
	ray_cone(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->world.img, 0, 0);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->map.img, 0, 840);
	if (mlx->key > 1)
		mlx_put_image_to_window(mlx->mlx, mlx->win,
			mlx->texture.text[0], 1800, 900);
}

static int	expos(t_mlx *mlx)
{
	if (mlx->lv == 0)
		mlx->lv++;
	else if (mlx->men == 0)
		deal_key(36, mlx);
	return (mlx->op);
}

int			main(int ac, char **av)
{
	t_mlx	mlx;

	mlx.win = NULL;
	mlx.lv = (ac == 1) ? 1 : 0;
	mlx.men = 0;
	mlx.op = 0;
	mlx.angle = 0;
	if (!(mlx.mlx = mlx_init()))
		return (0);
	if (ac == 1)
		ft_init(&mlx, av[0], "lvl1");
	else
	{
		ft_init(&mlx, av[0], av[1]);
		mlx_mouse_hide();
		render(&mlx);
	}
	mlx_hook(mlx.win, 2, 0, deal_key, &mlx);
	mlx_hook(mlx.win, 4, 0, deal_butt, &mlx);
	mlx_hook(mlx.win, 6, 0, mouse_pos, &mlx);
	mlx_hook(mlx.win, 17, 0, clwin, &mlx);
	mlx_expose_hook(mlx.win, expos, &mlx);
	mlx_loop_hook(mlx.mlx, ft_door, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}

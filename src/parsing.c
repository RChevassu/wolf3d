/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchevass <rchevass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 18:36:06 by rchevass          #+#    #+#             */
/*   Updated: 2018/11/23 17:23:14 by jlemahie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/incwol.h"

static int	ft_init_map(t_mlx *mlx)
{
	int i;

	if (!(mlx->worldmap = (int **)malloc(sizeof(int *) * (mlx->height))))
		return (0);
	i = 0;
	while (i < mlx->height)
	{
		mlx->worldmap[i] = NULL;
		i++;
	}
	return (1);
}

static int	free_splitted(char ***splitted_line)
{
	int i;

	i = 0;
	while ((*splitted_line) && (*splitted_line)[i])
	{
		free((*splitted_line)[i]);
		i++;
	}
	if (*splitted_line)
		free(*splitted_line);
	return (-1);
}

static int	line_to_array(char **line, t_mlx *mlx, int y)
{
	char	**splitted_line;
	int		x;
	int		k;

	splitted_line = ft_strsplit(*line, ' ');
	free(*line);
	x = 0;
	if (y == mlx->height)
		return (free_splitted(&splitted_line));
	while (splitted_line && splitted_line[x] != NULL)
		x++;
	if (x != mlx->width)
		return (free_splitted(&splitted_line));
	if (!(mlx->worldmap[y] = (int *)malloc(sizeof(int) * mlx->width)))
		return (free_splitted(&splitted_line));
	x = 0;
	while (splitted_line[x])
	{
		if ((k = ft_catoi(splitted_line[x])) > 8 || k < 0)
			return (free_splitted(&splitted_line));
		mlx->worldmap[y][x] = k;
		x++;
	}
	free_splitted(&splitted_line);
	return (1);
}

static int	ft_set_dimensions(char **line, t_mlx *mlx)
{
	char	**splitted_line;
	int		i;

	splitted_line = ft_strsplit(*line, ' ');
	free(*line);
	i = 0;
	while (splitted_line != NULL && splitted_line[i] != NULL)
		i++;
	if (i != 4)
		return (free_splitted(&splitted_line));
	if (ft_strcmp(splitted_line[0], "w:") != 0 ||
		ft_strcmp(splitted_line[2], "h:") != 0)
		return (free_splitted(&splitted_line));
	mlx->width = ft_catoi(splitted_line[1]);
	mlx->height = ft_catoi(splitted_line[3]);
	if (mlx->width <= 0 || mlx->height <= 0)
		return (free_splitted(&splitted_line));
	free_splitted(&splitted_line);
	return (1);
}

void		parse(char *filename, t_mlx *mlx)
{
	char	*line;
	int		fd;
	int		i;

	fd = open(filename, O_RDONLY);
	ft_strdel(&filename);
	if (fd < 0)
		ft_clrscn(mlx, "Erreur missing map");
	if (get_next_line(fd, &line) <= 0)
	{
		ft_strdel(&line);
		ft_clrscn(mlx, "Erreur map");
	}
	if (ft_set_dimensions(&line, mlx) < 0)
		ft_clrscn(mlx, "Erreur map");
	if (!(ft_init_map(mlx)))
		ft_clrscn(mlx, "Erreur alloc world");
	i = 0;
	while (get_next_line(fd, &line))
		if (line_to_array(&line, mlx, i++) < 0)
			ft_exit(mlx, "Erreur map");
	ft_strdel(&line);
	if (i < mlx->height)
		ft_exit(mlx, "Erreur map");
	close(fd);
}

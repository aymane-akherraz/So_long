/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: developer <developer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 09:42:26 by aakherra          #+#    #+#             */
/*   Updated: 2025/04/17 01:12:26 by developer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	load_textures(t_data *data, int s, void **arr)
{
	int		t;
	char	d[18];

	t = TILE_SIZE;
	if (s == BG)
		ft_strlcpy(d, "textures/bg/0.xpm", 18);
	else if (s == EX)
		ft_strlcpy(d, "textures/ex/0.xpm", 18);
	else if (s == PLY)
		ft_strlcpy(d, "textures/pl/0.xpm", 18);
	else
	{
		ft_strlcpy(d, "textures/cl/6.xpm", 18);
		*arr = mlx_xpm_file_to_image(data->mlx, d, &t, &t);
		if (!(*arr))
			free_and_destroy(data, "Failed to load image");
		return ;
	}
	load_img(data, s, d, arr);
}

void	set_window(char **m, t_points *size, t_points *pl_cords, size_t *t)
{
	t_data		data;
	t_points	cords;

	data.m = m;
	init_data(&data, size, pl_cords, t);
	init_sprites(&data);
	load_textures(&data, BG, data.bg_sprites);
	load_textures(&data, 1, data.cols_sprites);
	load_textures(&data, EX, data.ex_sprites);
	load_textures(&data, PLY, data.ply_sprites);
	mlx_hook(data.win, KeyPress, KeyPressMask, &handle_input, &data);
	mlx_hook(data.win, DestroyNotify, NoEventMask, &on_destroy, &data);
	put_to_win(data.size, &data, &cords);
	mlx_loop(data.mlx);
}

void	put_to_win(t_points *size, t_data *d, t_points *c)
{
	c->y = 0;
	while (c->y < size->y)
	{
		c->x = 0;
		while (c->x < size->x)
		{
			if (d->m[c->y][c->x] == '0' || d->m[c->y][c->x] == '1')
				mlx_put_image_to_window(d->mlx,
					d->win, d->bg_sprites[d->m[c->y][c->x] - '0'],
					c->x * TILE_SIZE, c->y * TILE_SIZE);
			else if (d->m[c->y][c->x] == 'P')
				mlx_put_image_to_window(d->mlx, d->win, d->ply_sprites[d->dir],
					c->x * TILE_SIZE, c->y * TILE_SIZE);
			else if (d->m[c->y][c->x] == 'C')
				mlx_put_image_to_window(d->mlx, d->win, d->cols_sprites[0],
					c->x * TILE_SIZE, c->y * TILE_SIZE);
			else if (d->m[c->y][c->x] == 'E')
				set_exit(d, c->x * TILE_SIZE, c->y * TILE_SIZE);
			c->x++;
		}
		c->y++;
	}
}

void	helper_func(t_data *data)
{
	if (data->cols_sprites[0])
		mlx_destroy_image(data->mlx, data->cols_sprites[0]);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	free_m(data->m);
	exit(0);
}

int	on_destroy(t_data *data)
{
	int	i;

	i = 0;
	while (i < BG)
	{
		if (data->bg_sprites[i])
			mlx_destroy_image(data->mlx, data->bg_sprites[i]);
		i++;
	}
	i = 0;
	while (i < EX)
	{
		if (data->ex_sprites[i])
			mlx_destroy_image(data->mlx, data->ex_sprites[i]);
		i++;
	}
	i = 0;
	while (i < PLY)
	{
		if (data->ply_sprites[i])
			mlx_destroy_image(data->mlx, data->ply_sprites[i]);
		i++;
	}
	helper_func(data);
	return (0);
}

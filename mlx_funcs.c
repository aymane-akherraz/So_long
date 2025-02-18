/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakherra <aakherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 09:42:26 by aakherra          #+#    #+#             */
/*   Updated: 2025/02/18 08:54:24 by aakherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move_ply(t_data *data, size_t y, size_t x, int dir)
{
	t_points	cords;
	t_points	l;

	if (data->m[y][x] == 'C')
		data->coll_count++;
	else if (data->m[y][x] == 'E')
	{
		if (data->coll_count == data->total_coll)
			on_destroy(data);
		else
			data->at_exit = true;
	}
	if (data->m[y][x] != '1')
	{
		if (data->m[data->pl_cords->y][data->pl_cords->x] != 'E')
			data->m[data->pl_cords->y][data->pl_cords->x] = '0';
		else
			data->at_exit = false;
		if (data->at_exit == false)
			data->m[y][x] = 'P';
		data->dir = dir;
		check_dir(data);
		put_to_win(data->size, data, &cords, &l);
	}
}

void	load_textures(void *mlx, int s, int t, void **arr)
{
	int		i;
	char	d[18];

	if (s == BG)
		ft_strlcpy(d, "textures/bg/0.xpm", 18);
	else if (s == EX)
		ft_strlcpy(d, "textures/ex/0.xpm", 18);
	else if (s == PLY)
		ft_strlcpy(d, "textures/pl/0.xpm", 18);
	else
	{
		ft_strlcpy(d, "textures/cl/6.xpm", 18);
		*arr = mlx_xpm_file_to_image(mlx, d, &t, &t);
		return ;
	}
	i = 0;
	while (i < s)
	{
		arr[i++] = mlx_xpm_file_to_image(mlx, d, &t, &t);
		d[12]++;
	}
}

void	set_window(char **m, t_points *size, t_points *pl_cords, size_t t)
{
	t_data		data;
	t_points	cords;
	t_points	l;

	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, (size->x * TILE_SIZE),
			(size->y * TILE_SIZE), "So_long");
	load_textures(data.mlx, BG, TILE_SIZE, data.bg_sprites);
	load_textures(data.mlx, 1, TILE_SIZE, data.cols_sprites);
	load_textures(data.mlx, EX, TILE_SIZE, data.ex_sprites);
	load_textures(data.mlx, PLY, TILE_SIZE, data.ply_sprites);
	data.m = m;
	data.pl_cords = pl_cords;
	data.coll_count = 0;
	data.total_coll = t;
	data.size = size;
	data.moves = 0;
	data.at_exit = false;
	data.dir = 0;
	mlx_hook(data.win, KeyPress, KeyPressMask, &handle_input, &data);
	mlx_hook(data.win, DestroyNotify, NoEventMask, &on_destroy, &data);
	put_to_win(data.size, &data, &cords, &l);
	mlx_loop(data.mlx);
}

void	put_to_win(t_points *size, t_data *d, t_points *c, t_points *l)
{
	l->y = 0;
	c->y = 0;
	while (c->y < size->y)
	{
		c->x = 0;
		l->x = 0;
		while (c->x < size->x)
		{
			if (d->m[c->y][c->x] == '0' || d->m[c->y][c->x] == '1')
				mlx_put_image_to_window(d->mlx,
					d->win, d->bg_sprites[d->m[c->y][c->x] - '0'], l->x, l->y);
			else if (d->m[c->y][c->x] == 'P')
				mlx_put_image_to_window(d->mlx, d->win, d->ply_sprites[d->dir],
					l->x, l->y);
			else if (d->m[c->y][c->x] == 'C')
				mlx_put_image_to_window(d->mlx, d->win, d->cols_sprites[0],
					l->x, l->y);
			else if (d->m[c->y][c->x] == 'E')
				set_exit(d, l->x, l->y);
			c->x++;
			l->x += TILE_SIZE;
		}
		c->y++;
		l->y += TILE_SIZE;
	}
}

int	on_destroy(t_data *data)
{
	int	i;

	i = 0;
	while (i < BG)
		mlx_destroy_image(data->mlx, data->bg_sprites[i++]);
	i = 0;
	while (i < EX)
		mlx_destroy_image(data->mlx, data->ex_sprites[i++]);
	i = 0;
	while (i < PLY)
		mlx_destroy_image(data->mlx, data->ply_sprites[i++]);
	mlx_destroy_image(data->mlx, data->cols_sprites[0]);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	free_m(data->m);
	exit(0);
	return (0);
}

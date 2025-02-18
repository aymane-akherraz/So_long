/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_funcs_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakherra <aakherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 21:21:41 by aakherra          #+#    #+#             */
/*   Updated: 2025/02/18 09:01:00 by aakherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	render_next_frame(t_data *data)
{
	size_t	i;
	size_t	j;

	if (data->i >= COLS)
		data->i = 0;
	j = 0;
	while (j < data->size->y)
	{
		i = 0;
		while (i < data->size->x)
		{
			if (data->m[j][i] == 'C')
				mlx_put_image_to_window(data->mlx, data->win,
					data->cols_sprites[data->i], i * TILE_SIZE, j * TILE_SIZE);
			i++;
		}
		j++;
	}
	usleep(100000);
	data->i++;
	return (0);
}

void	load_textures(void *mlx, int s, int t, void **arr)
{
	int		i;
	char	d[18];

	if (s == BG)
		ft_strlcpy(d, "textures/bg/0.xpm", 18);
	else if (s == COLS)
		ft_strlcpy(d, "textures/cl/0.xpm", 18);
	else if (s == EX)
		ft_strlcpy(d, "textures/ex/0.xpm", 18);
	else if (s == PLY)
		ft_strlcpy(d, "textures/pl/0.xpm", 18);
	else
	{
		ft_strlcpy(d, "textures/en/0.xpm", 18);
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

void	put_to_win(t_points *size, t_data *d, t_points *c, t_points *l)
{
	while (c->y < size->y)
	{
		c->x = 0;
		l->x = 0;
		while (c->x < size->x)
		{
			if (d->m[c->y][c->x] == '0' || d->m[c->y][c->x] == '1')
				mlx_put_image_to_window(d->mlx, d->win,
					d->bg_sprites[d->m[c->y][c->x] - '0'], l->x, l->y);
			else if (d->m[c->y][c->x] == 'P')
				mlx_put_image_to_window(d->mlx, d->win, d->ply_sprites[d->dir],
					l->x, l->y);
			else if (d->m[c->y][c->x] == 'C')
				mlx_put_image_to_window(d->mlx, d->win, d->cols_sprites[0],
					l->x, l->y);
			else if (d->m[c->y][c->x] == 'E')
				set_exit(d, l->x, l->y);
			else if (d->m[c->y][c->x] == 'K')
				mlx_put_image_to_window(d->mlx, d->win, d->enemy, l->x, l->y);
			c->x++;
			l->x += TILE_SIZE;
		}
		c->y++;
		l->y += TILE_SIZE;
	}
}

void	set_window(char **m, t_points *size, t_points *pl_c, size_t t)
{
	t_data		data;

	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, (size->x * TILE_SIZE),
			(size->y * TILE_SIZE), "So_long");
	load_textures(data.mlx, BG, TILE_SIZE, data.bg_sprites);
	load_textures(data.mlx, COLS, TILE_SIZE, data.cols_sprites);
	load_textures(data.mlx, EX, TILE_SIZE, data.ex_sprites);
	load_textures(data.mlx, PLY, TILE_SIZE, data.ply_sprites);
	load_textures(data.mlx, 1, TILE_SIZE, &(data.enemy));
	data.m = m;
	data.pl_cords = pl_c;
	data.coll_count = 0;
	data.total_coll = t;
	data.size = size;
	data.moves = 0;
	data.at_exit = false;
	data.dir = 0;
	data.i = 0;
	mlx_hook(data.win, DestroyNotify, NoEventMask, &on_destroy, &data);
	mlx_hook(data.win, KeyPress, KeyPressMask, &handle_input, &data);
	display_win(&data);
	mlx_loop_hook(data.mlx, &render_next_frame, &data);
	mlx_loop(data.mlx);
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
	i = 0;
	while (i < COLS)
		mlx_destroy_image(data->mlx, data->cols_sprites[i++]);
	mlx_destroy_image(data->mlx, data->enemy);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	free_m(data->m);
	exit(0);
	return (0);
}

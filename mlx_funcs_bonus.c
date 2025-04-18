/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_funcs_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: developer <developer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 21:21:41 by aakherra          #+#    #+#             */
/*   Updated: 2025/04/17 01:36:12 by developer        ###   ########.fr       */
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

void	load_textures(t_data *data, int s, void **arr)
{
	int		t;
	char	d[18];

	t = TILE_SIZE;
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
		*arr = mlx_xpm_file_to_image(data->mlx, d, &t, &t);
		if (!(*arr))
			free_and_destroy(data, "Failed to load image");
		return ;
	}
	load_img(data, s, d, arr);
}

void	put_to_win(t_points *size, t_data *d, t_points *c)
{
	while (c->y < size->y)
	{
		c->x = 0;
		while (c->x < size->x)
		{
			if (d->m[c->y][c->x] == '0' || d->m[c->y][c->x] == '1')
				mlx_put_image_to_window(d->mlx, d->win,
					d->bg_sprites[d->m[c->y][c->x] - '0'],
					c->x * TILE_SIZE, c->y * TILE_SIZE);
			else if (d->m[c->y][c->x] == 'P')
				mlx_put_image_to_window(d->mlx, d->win, d->ply_sprites[d->dir],
					c->x * TILE_SIZE, c->y * TILE_SIZE);
			else if (d->m[c->y][c->x] == 'C')
				mlx_put_image_to_window(d->mlx, d->win, d->cols_sprites[0],
					c->x * TILE_SIZE, c->y * TILE_SIZE);
			else if (d->m[c->y][c->x] == 'E')
				set_exit(d, c->x * TILE_SIZE, c->y * TILE_SIZE);
			else if (d->m[c->y][c->x] == 'K')
				mlx_put_image_to_window(d->mlx, d->win, d->enemy,
					c->x * TILE_SIZE, c->y * TILE_SIZE);
			c->x++;
		}
		c->y++;
	}
}

void	set_window(char **m, t_points *size, t_points *pl_c, size_t *t)
{
	t_data		data;

	data.m = m;
	init_data(&data, size, pl_c, t);
	init_sprites(&data);
	load_textures(&data, BG, data.bg_sprites);
	load_textures(&data, COLS, data.cols_sprites);
	load_textures(&data, EX, data.ex_sprites);
	load_textures(&data, PLY, data.ply_sprites);
	load_textures(&data, 1, &(data.enemy));
	mlx_hook(data.win, DestroyNotify, NoEventMask, &on_destroy, &data);
	mlx_hook(data.win, KeyPress, KeyPressMask, &handle_input, &data);
	display_win(&data);
	mlx_loop_hook(data.mlx, &render_next_frame, &data);
	mlx_loop(data.mlx);
}

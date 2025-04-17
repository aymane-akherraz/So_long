/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: developer <developer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 00:26:51 by developer         #+#    #+#             */
/*   Updated: 2025/04/17 01:03:30 by developer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	load_img(t_data *data, int s, char *d, void **arr)
{
	int		i;
	int		t;

	t = TILE_SIZE;
	i = 0;
	while (i < s)
	{
		arr[i] = mlx_xpm_file_to_image(data->mlx, d, &t, &t);
		if (!(arr[i]))
			free_and_destroy(data, "Failed to load image");
		d[12]++;
		i++;
	}
}

void	init_data(t_data *data, t_points *size, t_points *pl_cords, size_t *t)
{
	data->mlx = mlx_init(data);
	if (!data->mlx)
		exit_with_err("mlx_init_failed", 0, data->m);
	data->win = mlx_new_window(data->mlx, (size->x * TILE_SIZE),
			(size->y * TILE_SIZE), "So_long");
	if (!data->win)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		exit_with_err("mlx_new_window_failed", 0, data->m);
	}
	data->pl_cords = pl_cords;
	data->coll_count = 0;
	data->total_coll = *t;
	data->size = size;
	data->moves = 0;
	data->at_exit = false;
	data->dir = 0;
	data->i = 0;
}

void	init_sprites(t_data *data)
{
	int	i;

	i = 0;
	while (i < BG)
		data->bg_sprites[i++] = NULL;
	i = 0;
	while (i < EX)
		data->ex_sprites[i++] = NULL;
	i = 0;
	while (i < PLY)
		data->ply_sprites[i++] = NULL;
	i = 0;
	while (i < COLS)
		data->cols_sprites[i++] = NULL;
	data->enemy = NULL;
}

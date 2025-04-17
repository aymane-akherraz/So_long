/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: developer <developer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 01:34:14 by developer         #+#    #+#             */
/*   Updated: 2025/04/17 01:34:32 by developer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	helper_func(t_data *data)
{
	int	i;

	i = 0;
	while (i < COLS)
	{
		if (data->ply_sprites[i])
			mlx_destroy_image(data->mlx, data->cols_sprites[i]);
		i++;
	}
	if (data->enemy)
		mlx_destroy_image(data->mlx, data->enemy);
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

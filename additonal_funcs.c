/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additonal_funcs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakherra <aakherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 08:57:55 by aakherra          #+#    #+#             */
/*   Updated: 2025/02/10 14:06:51 by aakherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	handle_input(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		on_destroy(data);
	else if (keycode == XK_Left || keycode == XK_a || keycode == XK_A)
		move_ply(data, data->pl_cords->y, data->pl_cords->x - 1, 1);
	else if (keycode == XK_Right || keycode == XK_d || keycode == XK_D)
		move_ply(data, data->pl_cords->y, data->pl_cords->x + 1, 0);
	else if (keycode == XK_Up || keycode == XK_w || keycode == XK_W)
		move_ply(data, data->pl_cords->y - 1, data->pl_cords->x, 3);
	else if (keycode == XK_Down || keycode == XK_s || keycode == XK_S)
		move_ply(data, data->pl_cords->y + 1, data->pl_cords->x, 2);
	return (0);
}

void	set_exit(t_data *data, int x, int y)
{
	if (data->coll_count == data->total_coll)
		mlx_put_image_to_window(data->mlx, data->win, data->ex_sprites[EX - 1],
			x, y);
	else if (data->at_exit)
		mlx_put_image_to_window(data->mlx, data->win,
			data->ex_sprites[data->dir], x, y);
	else
		mlx_put_image_to_window(data->mlx, data->win, data->ex_sprites[EX - 2],
			x, y);
}

void	helper(char **m, t_points *cords, size_t *t, t_points *pl_cords)
{
	size_t	j;

	j = 0;
	while (j < cords->x)
	{
		if (j == 0 || j == cords->x - 1)
		{
			if (m[cords->y][j] != '1')
				exit_with_err("Invalid map", 0, m);
		}
		else
		{
			if (m[cords->y][j] == 'P')
			{
				t[0]++;
				pl_cords->y = cords->y;
				pl_cords->x = j;
			}
			else
				add_check(m[cords->y][j], t, m);
		}
		j++;
	}
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	check_ext(char *s)
{
	char	*ext;

	ext = ft_strchr(s, '.');
	if (!ext || ft_strcmp(ext, ".ber"))
		exit_with_err("Invalid file extension", 0, NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakherra <aakherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 09:52:59 by aakherra          #+#    #+#             */
/*   Updated: 2025/02/18 09:01:12 by aakherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_pl_access(char **m, t_mystruct *s, size_t x, size_t y)
{
	if (x < 0 || x >= s->x || y < 0 || y >= s->y
		|| m[y][x] == 'F' || m[y][x] == '1' || m[y][x] == 'K')
		return ;
	if (m[y][x] == 'C')
		s->coll_count++;
	else if (m[y][x] == 'E')
		s->exit_ac = true;
	m[y][x] = 'F';
	check_pl_access(m, s, x, y - 1);
	check_pl_access(m, s, x, y + 1);
	check_pl_access(m, s, x + 1, y);
	check_pl_access(m, s, x - 1, y);
}

void	add_check(char c, size_t *t, char **m)
{
	if (c == 'C')
		t[1]++;
	else if (c == 'E')
		t[2]++;
	else if (c != '1' && c != '0' && c != 'K')
		exit_with_err("Invalid map", 0, m);
}

void	check_dir(t_data *data)
{
	if (data->dir == 0)
		data->pl_cords->x++;
	else if (data->dir == 1)
		data->pl_cords->x--;
	else if (data->dir == 2)
		data->pl_cords->y++;
	else
		data->pl_cords->y--;
	data->moves++;
}

void	display_win(t_data *data)
{
	char		*s;
	t_points	cords;
	t_points	location;

	cords.y = 0;
	location.y = 0;
	put_to_win(data->size, data, &cords, &location);
	s = ft_itoa((int)data->moves);
	mlx_set_font(data->mlx, data->win, "10*20");
	mlx_string_put(data->mlx, data->win, 10, 20, 0xffffff, s);
	free(s);
}

void	move_ply(t_data *data, size_t y, size_t x, int dir)
{
	if (data->m[y][x] == 'C')
		data->coll_count++;
	else if (data->m[y][x] == 'E')
	{
		if (data->coll_count == data->total_coll)
			on_destroy(data);
		else
			data->at_exit = true;
	}
	else if (data->m[y][x] == 'K')
		on_destroy(data);
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
		display_win(data);
	}
}

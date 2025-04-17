/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: developer <developer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 09:41:00 by aakherra          #+#    #+#             */
/*   Updated: 2025/04/17 01:15:48 by developer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move_ply(t_data *data, size_t y, size_t x, int dir)
{
	t_points	cords;

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
		put_to_win(data->size, data, &cords);
	}
}

void	check_pl_access(char **m, t_mystruct *s, size_t x, size_t y)
{
	if (x >= s->x || y >= s->y
		|| m[y][x] == 'F' || m[y][x] == '1')
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
	else if (c != '1' && c != '0')
		exit_with_err("Invalid map", 0, m);
}

void	ft_putnbr(size_t n)
{
	char	c;

	if (n >= 10)
		ft_putnbr((n / 10));
	c = (n % 10) + '0';
	write(1, &c, 1);
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
	ft_putnbr(data->moves);
	write(1, "\n", 1);
}

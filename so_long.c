/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakherra <aakherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 08:23:16 by aakherra          #+#    #+#             */
/*   Updated: 2025/02/18 09:46:52 by aakherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	is_valid(char **m, t_points *size, t_points *pl_cords, size_t total)
{
	t_mystruct	s;

	s.x = size->x;
	s.y = size->y;
	s.coll_count = 0;
	s.exit_ac = false;
	check_pl_access(m, &s, pl_cords->x, pl_cords->y);
	if (s.coll_count != total || s.exit_ac == false)
		exit_with_err("Invalid map", 0, m);
}

void	is_closed(char **m, t_points *size, size_t *t, t_points *pl_cords)
{
	size_t		j;
	t_points	cords;

	cords.x = size->x;
	cords.y = 0;
	t[0] = 0;
	t[1] = 0;
	t[2] = 0;
	while (m[cords.y])
	{
		if (cords.y == 0 || cords.y == size->y - 1)
		{
			j = 0;
			while (j < size->x)
			{
				if (m[cords.y][j++] != '1')
					exit_with_err("Invalid map", 0, m);
			}
		}
		else
			helper(m, &cords, t, pl_cords);
		cords.y++;
	}
	if (t[0] != 1 || !t[1] || t[2] != 1)
		exit_with_err("Invalid map", 0, m);
}

void	check_map(t_points *size, char *file, int fd)
{
	char		**m;
	size_t		t[3];
	t_points	cords;
	t_points	*pl_cords;

	close(fd);
	m = allocate(size->y, file);
	if (!m)
		exit_with_err("", 1, m);
	pl_cords = &cords;
	is_closed(m, size, t, pl_cords);
	is_valid(m, size, pl_cords, t[1]);
	free_m(m);
	m = allocate(size->y, file);
	if (!m)
		exit_with_err("", 1, m);
	set_window(m, size, pl_cords, t[1]);
}

int	main(int ac, char **av)
{
	int			fd;
	char		*s;
	t_points	size;

	if (ac > 1)
	{
		check_ext(av[1]);
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
			exit_with_err("", 1, NULL);
		s = get_next_line(fd);
		size.x = get_line_len(s);
		size.y = 0;
		while (s)
		{
			size.y++;
			free(s);
			s = get_next_line(fd);
			if (s && size.x != get_line_len(s))
				free_and_exit(fd, s);
		}
		check_map(&size, av[1], fd);
	}
	else
		ft_putstr("Usage: ./so_long map_file.ber", 1);
}

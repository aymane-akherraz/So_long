/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakherra <aakherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 10:12:22 by aakherra          #+#    #+#             */
/*   Updated: 2025/02/18 09:44:44 by aakherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_m(char **m)
{
	size_t	i;

	if (m)
	{
		i = 0;
		while (m[i])
			free(m[i++]);
		free(m);
	}
}

void	free_all(char **p, size_t j, int fd)
{
	char	*s;
	size_t	i;

	i = 0;
	while (i < j)
	{
		free(p[i]);
		i++;
	}
	free(p);
	s = get_next_line(fd);
	while (s)
	{
		free(s);
		s = get_next_line(fd);
	}
	exit(1);
}

void	exit_with_err(char *s, int f, char **m)
{
	ft_putstr("Error", 2);
	if (f)
		perror("");
	else
		ft_putstr(s, 2);
	free_m(m);
	exit(1);
}

void	free_and_exit(int fd, char *s)
{
	while (s)
	{
		free(s);
		s = get_next_line(fd);
	}
	exit_with_err("Invalid map", 0, NULL);
}

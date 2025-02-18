/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakherra <aakherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 10:35:10 by aakherra          #+#    #+#             */
/*   Updated: 2025/02/18 09:16:57 by aakherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_putstr(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
	write(fd, "\n", 1);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	if (size == 0)
		return (ft_strlen(src));
	i = 0;
	while (src[i] && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

char	*my_strdup(char *s)
{
	size_t	len;
	size_t	i;
	char	*p;

	len = ft_strlen(s);
	p = malloc(len + 1);
	if (p)
	{
		i = 0;
		while (i < len)
		{
			p[i] = s[i];
			i++;
		}
		p[i] = '\0';
	}
	free(s);
	return (p);
}

char	**allocate(size_t y, char *file)
{
	int		fd;
	char	**m;
	size_t	i;

	m = malloc(sizeof(char *) * y + sizeof(char *));
	if (m)
	{
		fd = open(file, O_RDONLY);
		i = 0;
		while (i < y)
		{
			m[i] = my_strdup(get_next_line(fd));
			if (!m[i])
			{
				ft_putstr("Error", 2);
				perror("");
				free_all(m, i, fd);
			}
			i++;
		}
		m[i] = get_next_line(fd);
		close(fd);
	}
	return (m);
}

size_t	get_line_len(char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	return (i);
}

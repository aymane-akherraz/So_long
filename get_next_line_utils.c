/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakherra <aakherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 11:13:12 by aakherra          #+#    #+#             */
/*   Updated: 2025/01/28 13:03:06 by aakherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*ft_substr(char const *s, size_t start, size_t len)
{
	size_t	i;
	size_t	sl;
	char	*p;

	if (!s)
		return (NULL);
	sl = ft_strlen(s);
	if (start >= sl)
		len = 0;
	p = malloc(len + 1);
	if (p)
	{
		i = 0;
		while (i < len && s[start])
		{
			p[i] = s[start];
			i++;
			start++;
		}
		p[i] = '\0';
	}
	return (p);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	l1;
	size_t	i;
	size_t	j;
	size_t	len;
	char	*p;

	l1 = ft_strlen(s1);
	len = l1 + ft_strlen(s2);
	p = malloc(len + 1);
	if (p)
	{
		i = 0;
		while (i < l1)
		{
			p[i] = s1[i];
			i++;
		}
		j = 0;
		while (i < len)
			p[i++] = s2[j++];
		p[i] = '\0';
	}
	return (p);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return ((char *)&s[i]);
		i++;
	}
	return (NULL);
}

char	*ft_strdup(const char *s)
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
	return (p);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

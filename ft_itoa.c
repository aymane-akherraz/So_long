/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakherra <aakherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 09:51:13 by aakherra          #+#    #+#             */
/*   Updated: 2025/02/10 09:52:23 by aakherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static char	*alloc(int n, int i)
{
	char	*s;

	if (n < 0)
		s = malloc(i + 2);
	else
		s = malloc(i + 1);
	return (s);
}

static char	*handle_zero(void)
{
	char	*s;

	s = malloc(2);
	if (s)
	{
		s[0] = '0';
		s[1] = '\0';
	}
	return (s);
}

static int	*set_int(int n, int *a, int *p)
{
	unsigned int	num;

	if (n < 0)
		num = -n;
	else
		num = n;
	while (num)
	{
		a[*p] = num % 10;
		num /= 10;
		(*p)++;
	}
	return (a);
}

char	*ft_itoa(int n)
{
	int		a[10];
	int		i;
	int		j;
	char	*s;

	if (n == 0)
		return (handle_zero());
	i = 0;
	set_int(n, a, &i);
	s = alloc(n, i);
	if (s)
	{
		j = 0;
		if (n < 0)
			s[j++] = '-';
		i--;
		while (i >= 0)
			s[j++] = a[i--] + 48;
		s[j] = '\0';
	}
	return (s);
}

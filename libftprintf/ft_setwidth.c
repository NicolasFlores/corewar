/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setwidth.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 14:17:34 by nflores           #+#    #+#             */
/*   Updated: 2016/01/25 16:54:23 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_print_width(int n, t_printf **ges)
{
	int		i;
	int		cgt;
	char	c;

	i = 0;
	cgt = (*ges)->lng;
	c = ' ';
	while (i < n)
	{
		if ((*ges)->zero && !(*ges)->minus && n - (*ges)->lng > 0)
			c = '0';
		if ((*ges)->lng > 1 && cgt)
		{
			if (cgt - 2)
				n -= cgt - 2;
			else
				n--;
			cgt = 0;
		}
		write(1, &c, 1);
		i++;
	}
	return (i - 2);
}

int			ft_setwidth(int n, t_printf **ges, char **ag)
{
	int				i;

	i = 0;
	if (*ag[0] == '-' && (*ges)->zero && !(*ges)->space)
	{
		write(1, &(*ag[0]), 1);
		*ag = ft_strdup(*ag + 1);
		(*ges)->ret++;
	}
	if ((*ges)->plus)
		n--;
	if (n > 0)
		return (ft_print_width(n, ges));
	else if ((*ges)->width)
		return (i - 1);
	return (0);
}

static int	ft_print_width_c(int n, t_printf **ges, int *i)
{
	int		cgt;
	char	c;

	cgt = (*ges)->lng;
	c = ' ';
	while (*i < n)
	{
		if ((*ges)->zero && !(*ges)->minus && n - (*ges)->lng > 0)
		{
			if ((*ges)->impl && (*ges)->width)
				(*ges)->ret++;
			c = '0';
		}
		if ((*ges)->lng > 1 && cgt)
		{
			if (cgt - 2)
				n -= cgt - 2;
			else
				n--;
			cgt = 0;
		}
		write(1, &c, 1);
		(*i)++;
	}
	return ((*i) - 2);
}

int			ft_setwidth_c(int n, t_printf **ges)
{
	int				i;
	char			c;
	int				cgt;

	i = 0;
	c = ' ';
	cgt = (*ges)->lng;
	if ((*ges)->plus)
		n--;
	if (n > 0)
		return (ft_print_width_c(n, ges, &i));
	else if ((*ges)->width)
		return (i - 1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setwidth_d.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 11:43:44 by nflores           #+#    #+#             */
/*   Updated: 2016/01/26 11:55:46 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_width_init(int *n, t_printf **ges, char **ag, int *cgt)
{
	if (*ag[0] == '-' && (*ges)->zero && !(*ges)->space)
	{
		write(1, &(*ag[0]), 1);
		*ag = ft_strdup(*ag + 1);
		(*ges)->ret++;
	}
	if ((*ges)->plus)
		(*n)--;
	if ((*ges)->width > (*ges)->lng && *cgt && !(*ges)->impl &&
		!(*ges)->minus && !(*ges)->zero)
	{
		if ((int)ft_strlen(*ag) > *cgt)
		{
			(*cgt)--;
			(*n)++;
		}
	}
}

static void	ft_print_width(int *n, t_printf **ges, int *i, int *cgt)
{
	char	c;

	c = ' ';
	while ((*i) < (*n))
	{
		if ((*ges)->zero && !(*ges)->minus && (*n) - (*ges)->lng > 0)
			c = '0';
		if ((*ges)->lng > 1 && *cgt && !(*ges)->impl)
		{
			if ((*cgt) - 2)
				(*n) -= (*cgt) - 2;
			else
				(*n)--;
			(*cgt) = 0;
			if ((*n) < 0)
			{
				(*i) += 2 + (*ges)->width;
				break ;
			}
		}
		write(1, &c, 1);
		(*i)++;
	}
}

int			ft_setwidth_d(int n, t_printf **ges, char **ag)
{
	int				i;
	int				cgt;

	i = 0;
	cgt = (*ges)->lng;
	ft_width_init(&n, ges, ag, &cgt);
	if (n > 0)
	{
		ft_print_width(&n, ges, &i, &cgt);
		return (i - 2);
	}
	else if ((*ges)->width)
		return (i - 1);
	return (0);
}

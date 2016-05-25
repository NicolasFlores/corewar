/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setwidth_o.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/22 11:38:32 by nflores           #+#    #+#             */
/*   Updated: 2016/01/26 12:03:43 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_width_init(int *n, t_printf **ges, char **ag, int cgt)
{
	if ((*ges)->plus)
		(*n)--;
	if ((*ges)->width > (*ges)->lng && cgt && !(*ges)->impl)
	{
		if ((int)ft_strlen(*ag) > cgt)
			(*ges)->impl = 1;
	}
}

static void	ft_print_width(int *n, t_printf **ges, int *i, int *cgt)
{
	char c;

	c = ' ';
	while ((*i) < (*n))
	{
		if ((*ges)->zero && !(*ges)->minus && *n - (*ges)->lng > 0)
			c = '0';
		if ((*ges)->lng > 1 && *cgt && !(*ges)->impl)
		{
			if (*cgt - 2)
				(*n) -= (*cgt) - 2;
			else
				(*n)--;
			(*cgt) = 0;
			if ((*n) < 0)
			{
				(*i) = 2 + (*ges)->width;
				break ;
			}
		}
		write(1, &c, 1);
		(*i)++;
	}
}

int			ft_setwidth_o(int n, t_printf **ges, char **ag)
{
	int	i;
	int	cgt;

	i = 0;
	cgt = (*ges)->lng;
	ft_width_init(&n, ges, ag, cgt);
	if (n > 0)
	{
		ft_print_width(&n, ges, &i, &cgt);
		return (i - 2);
	}
	else if ((*ges)->width)
		return (i - 1);
	return (0);
}

int			ft_setwidth_x(int n, t_printf **ges, char **ag)
{
	int				i;
	int				cgt;

	i = 0;
	cgt = (*ges)->lng;
	ft_width_init(&n, ges, ag, cgt);
	if (n > 0)
	{
		ft_print_width(&n, ges, &i, &cgt);
		return (i - 2);
	}
	else if ((*ges)->width)
		return (i - 1);
	return (0);
}

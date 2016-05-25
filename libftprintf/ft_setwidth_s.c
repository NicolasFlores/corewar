/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setwidth_s.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 10:09:28 by nflores           #+#    #+#             */
/*   Updated: 2016/01/26 11:18:12 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_setwidth_init(int *n, t_printf **ges, char **ag)
{
	if (ft_strlen(*ag) > (unsigned int)(*ges)->width &&
		(*ges)->width > (*ges)->lng)
		*n += ft_strlen(*ag) + (*ges)->lng - 1;
	if (!ft_strcmp(*ag, "(null)") && !(*ges)->plus && !(*ges)->space && *n)
	{
		*n -= ft_strlen(*ag);
		(*ges)->ret++;
	}
}

static int	ft_width_core(int *n, t_printf **ges, char **ag, int *cgt)
{
	if (*cgt && (*ges)->lng - 2 > 0 && (*ges)->width > (*ges)->lng &&
		(unsigned int)(*ges)->lng > ft_strlen(*ag))
	{
		(*n) += (*ges)->lng + 1;
		return (1);
	}
	else if (*cgt && (*ges)->lng - 2 > 0 && (*ges)->width > (*ges)->lng)
	{
		(*n) -= (ft_strlen(*ag) - (*ges)->lng) + 1;
		return (1);
	}
	else if ((*ges)->width > (*ges)->lng)
	{
		(*n)--;
		return (1);
	}
	else if (ft_strlen(*ag) < (unsigned int)(*ges)->width)
	{
		(*n)--;
		(*ges)->lng--;
		return (1);
	}
	return (0);
}

static void	ft_flag_minus_zero(int *n, t_printf **ges, char **ag, char *c)
{
	if ((*ges)->zero && !(*ges)->minus && (*n) - (*ges)->lng > 0)
	{
		*c = '0';
		if (ft_strcmp(*ag, "(null)"))
			(*n) -= ft_strlen(*ag) - 1;
	}
}

static void	ft_print_width(int *n, t_printf **ges, char **ag, int *i)
{
	int		cgt;
	char	c;

	cgt = 1;
	c = ' ';
	while (*i < *n)
	{
		ft_flag_minus_zero(n, ges, ag, &c);
		if ((*ges)->lng > 1)
		{
			if (!ft_width_core(n, ges, ag, &cgt))
			{
				(*i) -= (*ges)->width + 1;
				if (ft_strlen(*ag) > (unsigned int)(*ges)->lng)
					(*i) += ft_strlen(*ag) - (*ges)->lng + (*ges)->width + 1;
				break ;
			}
			cgt = 0;
		}
		if ((*ges)->impl && !(*ges)->zero)
			(*i)++;
		write(1, &c, 1);
		(*i)++;
	}
}

int			ft_setwidth_s(int n, t_printf **ges, char **ag)
{
	int		i;
	int		tmp;

	i = 0;
	tmp = (*ges)->lng;
	ft_setwidth_init(&n, ges, ag);
	if (n > 0)
	{
		ft_print_width(&n, ges, ag, &i);
		return (i - 2);
	}
	else if ((*ges)->width)
		return (i - 1);
	(*ges)->lng = tmp;
	return (0);
}

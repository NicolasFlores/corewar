/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setwidth_p.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/25 16:52:35 by nflores           #+#    #+#             */
/*   Updated: 2016/01/25 16:58:54 by nflores          ###   ########.fr       */
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
		if ((*ges)->lng > 1 && cgt && (*ges)->impl)
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

int			ft_setwidth_p(int n, t_printf **ges, char **ag)
{
	int i;
	int	cgt;

	cgt = (*ges)->lng;
	i = 0;
	if ((*ges)->plus)
		n--;
	if ((*ges)->width > (*ges)->lng && cgt && !(*ges)->impl)
	{
		(*ges)->ret++;
		if (ft_strlen(*ag) + cgt >= (unsigned int)(*ges)->width - 1)
			(*ges)->ret++;
	}
	if (n > 0)
		return (ft_print_width(n, ges));
	else if ((*ges)->width)
		return (i - 1);
	return (0);
}

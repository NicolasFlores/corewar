/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_pct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 17:11:35 by nflores           #+#    #+#             */
/*   Updated: 2016/01/25 13:16:37 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_width_pct(const char *str, unsigned int pos)
{
	unsigned int i;

	i = 0;
	while (str[pos + i + 1] == '#' || str[pos + i + 1] == '.' ||
		str[pos + i + 1] == '-' || (str[pos + i + 1] >= '0' &&
									str[pos + i + 1] <= '9'))
		i++;
	return (i);
}

int			check_pct(const char *str, unsigned int pos, t_printf **ges)
{
	unsigned int i;

	i = 0;
	if (str[pos + i] == '%')
	{
		i += ft_width_pct(str, i);
		if (str[pos + i + 1] == ' ')
			return (2);
		else if (str[pos + i + 1] != '%' && !ft_flag(str, pos + i + 1, ges))
			return (0);
	}
	return (1);
}

int			ft_printf_pct(t_printf **ges)
{
	char	c;
	char	*s;
	int		ret;

	if ((*ges)->flag == -1)
		return (0);
	(*ges)->flag = 0;
	c = '%';
	s = "%";
	ret = 0;
	ret += ft_setwidth((*ges)->width - 1, ges, &s);
	write(1, &c, 1);
	if ((*ges)->lng)
		return (ret + 2 - (*ges)->lng);
	return (ret + 1);
}

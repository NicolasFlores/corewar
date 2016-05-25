/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_u.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 10:45:27 by nflores           #+#    #+#             */
/*   Updated: 2016/01/25 15:43:04 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_prec_initret(t_printf **ges, const char *s)
{
	int ret;

	ret = 0;
	if ((*ges)->lng >= (*ges)->width && (*ges)->width &&
		(int)ft_strlen(s) <= (*ges)->lng)
	{
		ret += 2;
		if ((int)ft_strlen(s) + 1 < (*ges)->lng - (*ges)->width &&
			(int)ft_strlen(s) < (*ges)->width)
			ret += ft_strlen(s);
		else
			ret += 3;
		(*ges)->ret++;
	}
	return (ret);
}

static int	ft_prec_u(t_printf **ges, const char *s)
{
	unsigned int	i;
	int				ret;

	i = 0;
	ret = 0;
	ret += ft_prec_initret(ges, s);
	if ((*ges)->lng && ft_strlen(s) < (unsigned long)(*ges)->lng)
	{
		while (i < (*ges)->lng - ft_strlen(s))
		{
			ft_putchar('0');
			i++;
		}
	}
	else if ((*ges)->lng)
		ret -= 1 + ft_strlen(ft_itoa((*ges)->lng));
	return (ret);
}

static char	*ft_set_arg_u(t_printf **ges)
{
	unsigned int	arg;
	unsigned short	arg2;
	unsigned char	arg3;

	arg = 0;
	arg2 = 0;
	arg3 = 0;
	if ((*ges)->modif == 1)
	{
		arg3 = va_arg((*ges)->ap, unsigned int);
		return (ft_itoa_base(arg3, 10));
	}
	else if ((*ges)->modif == 2)
	{
		arg2 = va_arg((*ges)->ap, unsigned int);
		return (ft_itoa_base(arg2, 10));
	}
	arg = va_arg((*ges)->ap, unsigned int);
	return (ft_itoa_base(arg, 10));
}

int			ft_printf_u(t_printf **ges)
{
	char			*ag;
	int				ret;

	ag = ft_set_arg_u(ges);
	if (!ag)
		return (0);
	ret = 0;
	ret += ft_setwidth_d((*ges)->width - ft_strlen(ag), ges, &ag);
	ret += ft_prec_u(ges, ag);
	if (ft_atoi(ag) != 0 || !(*ges)->impl || ((*ges)->lng && (*ges)->width))
		ft_putstr(ag);
	ret += ft_strlen(ag) + (*ges)->impl;
	free(ag);
	return (ret - (*ges)->space - (*ges)->plus - (*ges)->zero - (*ges)->minus);
}

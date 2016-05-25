/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 12:57:12 by nflores           #+#    #+#             */
/*   Updated: 2016/01/26 15:39:47 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_set_arg_d(t_printf **ges)
{
	int		arg;
	short	arg2;
	char	arg3;
	char	*ret;

	arg = 0;
	arg2 = 0;
	arg3 = 0;
	if ((*ges)->modif == 1)
	{
		arg3 = va_arg((*ges)->ap, int);
		ret = ft_itoa(arg3);
		return (ret);
	}
	else if ((*ges)->modif == 2)
	{
		arg2 = va_arg((*ges)->ap, int);
		ret = ft_itoa(arg2);
		return (ret);
	}
	arg = va_arg((*ges)->ap, int);
	ret = ft_itoa(arg);
	return (ret);
}

static int	ft_flag_minus_plus(t_printf **ges, char *ag)
{
	int ret;

	ret = 0;
	if ((*ges)->minus)
	{
		ft_putstr(ag);
		if ((*ges)->zero)
			(*ges)->ret++;
	}
	if ((*ges)->plus && ag[0] >= '0' && !(*ges)->minus)
	{
		ft_putchar('+');
		if ((*ges)->zero && ft_strlen(ag) < (unsigned int)(*ges)->width - 1)
			(*ges)->ret++;
	}
	else if ((*ges)->plus)
		ret -= (*ges)->plus;
	return (ret);
}

static int	ft_flag_space(t_printf **ges, char *ag)
{
	int ret;

	ret = 0;
	if ((*ges)->space && ag[0] >= '0' && !(*ges)->plus && !(*ges)->minus)
	{
		ft_putchar(' ');
		if ((*ges)->zero)
		{
			(*ges)->width--;
			(*ges)->ret++;
		}
	}
	else if ((*ges)->space)
		ret -= (*ges)->space;
	return (ret);
}

int			ft_printf_d(t_printf **ges)
{
	char	*ag;
	int		ret;

	ag = ft_set_arg_d(ges);
	if (!ag)
		return (0);
	ret = 0;
	ret += ft_flag_minus_plus(ges, ag);
	ret += ft_flag_space(ges, ag);
	ret += ft_setwidth_d((*ges)->width - ft_strlen(ag), ges, &ag);
	ret += ft_prec_d(ges, &ag);
	if ((ft_atoi(ag) != 0 || !(*ges)->impl ||
		((*ges)->lng && (*ges)->width)) && !(*ges)->minus)
		ft_putstr(ag);
	ret += ft_strlen(ag) + (*ges)->impl;
	free(ag);
	return (ret - (*ges)->minus - (*ges)->zero);
}

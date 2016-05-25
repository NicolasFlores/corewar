/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_o.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 10:37:58 by nflores           #+#    #+#             */
/*   Updated: 2016/01/26 13:43:01 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_prec_init_ret(t_printf **ges, const char *s)
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
			ret += 2;
		(*ges)->ret++;
	}
	return (ret);
}

static int	ft_prec_o(t_printf **ges, const char *s)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	ret += ft_prec_init_ret(ges, s);
	if ((*ges)->lng && ft_strlen(s) < (unsigned long)(*ges)->lng)
	{
		while (i < (*ges)->lng - (int)ft_strlen(s) - (*ges)->sharp)
		{
			ft_putchar('0');
			i++;
		}
		if ((*ges)->sharp)
			ret--;
	}
	else if ((*ges)->lng)
		ret -= 1 + ft_strlen(ft_itoa((*ges)->lng));
	if ((*ges)->lng == 1 && (*ges)->sharp)
		ret++;
	return (ret);
}

static char	*ft_set_arg_o(t_printf **ges)
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
		return (ft_itoa_base(arg3, 8));
	}
	else if ((*ges)->modif == 2)
	{
		arg2 = va_arg((*ges)->ap, unsigned int);
		return (ft_itoa_base(arg2, 8));
	}
	arg = va_arg((*ges)->ap, unsigned int);
	return (ft_itoa_base(arg, 8));
}

static int	ft_print_ag(t_printf **ges, const char *ag)
{
	int ret;

	ret = 0;
	if ((*ges)->lng == 1)
		ret++;
	if (ft_atoi(ag) != 0 || !(*ges)->impl || ((*ges)->lng && (*ges)->width) ||
		(*ges)->sharp)
		ft_putstr(ag);
	ret += ft_strlen(ag);
	return (ret);
}

int			ft_printf_o(t_printf **ges)
{
	char			*ag;
	char			*sharp;
	int				ret;

	ag = ft_set_arg_o(ges);
	if (!ag)
		return (0);
	ret = 0;
	sharp = ft_strnew(1);
	if ((*ges)->sharp && ag[0] != '0')
		sharp = ft_strdup("0");
	if (!sharp)
		return (0);
	ft_putstr(sharp);
	ret += ft_setwidth_o((*ges)->width - ft_strlen(ag), ges, &ag);
	ret += ft_prec_o(ges, ag);
	ret += ft_print_ag(ges, ag);
	if (ft_strlen(sharp) || (*ges)->sharp)
		ret += ft_strlen(sharp) - 1;
	free(ag);
	free(sharp);
	return (ret - (*ges)->plus - (*ges)->space);
}

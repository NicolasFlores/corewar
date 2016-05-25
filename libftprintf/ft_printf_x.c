/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_x.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 10:41:10 by nflores           #+#    #+#             */
/*   Updated: 2016/01/26 13:43:23 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_prec_init_ret(t_printf **ges, const char *s)
{
	int ret;

	ret = 0;
	if ((*ges)->lng >= (*ges)->width && (*ges)->width &&
		(int)ft_strlen(s) < (*ges)->lng)
	{
		ret += 2;
		if ((int)ft_strlen(s) + 1 < (*ges)->lng - (*ges)->width &&
			(int)ft_strlen(s) < (*ges)->width)
			ret += ft_strlen(s);
		else
			ret += 2;
		if ((*ges)->flag == 11 && (int)ft_strlen(s) > (*ges)->width)
			ret += 2;
		(*ges)->ret++;
	}
	return (ret);
}

int			ft_prec_x(t_printf **ges, const char *s)
{
	unsigned int	i;
	int				ret;

	i = 0;
	ret = 0;
	ret += ft_prec_init_ret(ges, s);
	if ((*ges)->lng && ft_strlen(s) < (unsigned long)(*ges)->lng)
	{
		while (i < (*ges)->lng - ft_strlen(s))
		{
			ft_putchar('0');
			i++;
		}
		if ((*ges)->sharp)
			ret += 2;
	}
	else if ((*ges)->lng)
		ret -= 1 + ft_strlen(ft_itoa((*ges)->lng));
	if ((*ges)->lng == 1 && (*ges)->sharp)
		ret++;
	return (ret);
}

static char	*ft_set_arg_x(t_printf **ges)
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
		return (ft_itoa_base(arg3, 16));
	}
	else if ((*ges)->modif == 2)
	{
		arg2 = va_arg((*ges)->ap, unsigned int);
		return (ft_itoa_base(arg2, 16));
	}
	arg = va_arg((*ges)->ap, unsigned int);
	return (ft_itoa_base(arg, 16));
}

static void	ft_flag_modif(t_printf **ges, char *ag, char *sharp)
{
	if ((*ges)->flag == 10)
	{
		lowercase(&ag);
		lowercase(&sharp);
	}
}

int			ft_printf_x(t_printf **ges)
{
	char			*ag;
	char			*sharp;
	int				ret;

	ag = ft_set_arg_x(ges);
	ret = 0;
	sharp = ft_strnew(1);
	if ((*ges)->sharp && ag[0] != '0')
		sharp = ft_strdup("0X");
	if (!sharp || !ag)
		return (0);
	ft_flag_modif(ges, ag, sharp);
	ft_putstr(sharp);
	ret += ft_setwidth_x((*ges)->width - ft_strlen(ag), ges, &ag);
	ret += ft_prec_x(ges, ag) + ft_strlen(ag);
	if ((ft_atoi(ag) != 0 || !(*ges)->impl) || ((*ges)->lng && (*ges)->width))
		ft_putstr(ag);
	if (!((*ges)->sharp) && (*ges)->impl && !((*ges)->width))
		ret++;
	if (ft_strlen(sharp) || (*ges)->sharp)
		ret += ft_strlen(sharp) - 1;
	free(ag);
	free(sharp);
	return (ret - (*ges)->plus - (*ges)->space - (*ges)->zero);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_mo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 10:58:55 by nflores           #+#    #+#             */
/*   Updated: 2016/01/26 13:42:43 by nflores          ###   ########.fr       */
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

static int	ft_prec_mo(t_printf **ges, const char *s)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	ret += ft_prec_init_ret(ges, s);
	if ((*ges)->lng && ft_strlen(s) < (unsigned long)(*ges)->lng)
	{
		while (i < (*ges)->lng - (int)ft_strlen(s))
		{
			ft_putchar('0');
			i++;
		}
	}
	else if ((*ges)->lng)
		ret -= 1 + ft_strlen(ft_itoa((*ges)->lng));
	return (ret);
}

static int	ft_print_ag(t_printf **ges, const char *ag, const char *sharp)
{
	int ret;

	ret = 0;
	if (ft_atoi(ag) != 0 || !(*ges)->impl || ((*ges)->lng && (*ges)->width) ||
		(*ges)->sharp)
		ft_putstr(ag);
	if (!((*ges)->sharp) && (*ges)->impl && !((*ges)->width))
		ret--;
	if (ft_strlen(sharp) || (*ges)->sharp)
		ret += ft_strlen(sharp) - 1;
	return (ret);
}

int			ft_printf_mo(t_printf **ges)
{
	char				*ag;
	char				*sharp;
	int					ret;
	unsigned long int	arg;

	arg = va_arg((*ges)->ap, unsigned long int);
	ag = ft_itoa_base(arg, 8);
	ret = 0;
	sharp = ft_strnew(1);
	if ((*ges)->sharp && arg != 0)
		sharp = ft_strdup("0");
	if (!ag || !sharp)
		return (0);
	ft_putstr(sharp);
	ret += ft_setwidth_o((*ges)->width - ft_strlen(ag), ges, &ag);
	ret += ft_prec_mo(ges, ag);
	if ((*ges)->impl)
		ret = ft_strlen(ag);
	else
		ret += ft_strlen(ag);
	ret += ft_print_ag(ges, ag, sharp);
	free(ag);
	free(sharp);
	return (ret - (*ges)->plus);
}

int			ft_printf_mmo(t_printf **ges)
{
	char				*ag;
	char				*sharp;
	int					ret;
	unsigned long long	arg;

	arg = va_arg((*ges)->ap, unsigned long long);
	ag = ft_itoa_base(arg, 8);
	ret = 0;
	sharp = ft_strnew(1);
	if ((*ges)->sharp && arg != 0)
		sharp = ft_strdup("0");
	if (!ag || !sharp)
		return (0);
	ft_putstr(sharp);
	ret += ft_setwidth_o((*ges)->width - ft_strlen(ag), ges, &ag);
	ret += ft_prec_mo(ges, ag);
	if ((*ges)->impl)
		ret = ft_strlen(ag);
	else
		ret += ft_strlen(ag);
	ret += ft_print_ag(ges, ag, sharp);
	free(ag);
	free(sharp);
	return (ret - (*ges)->plus);
}

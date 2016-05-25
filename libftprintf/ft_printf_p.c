/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 14:34:54 by nflores           #+#    #+#             */
/*   Updated: 2016/01/25 17:03:04 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_prec_p(t_printf **ges, const char *s)
{
	unsigned int	i;
	int				ret;

	i = 0;
	ret = 0;
	if ((*ges)->lng >= (*ges)->width && (*ges)->width)
	{
		ft_putstr("0x");
		ret += 2;
		if ((int)ft_strlen(s) + 1 < (*ges)->lng - (*ges)->width)
			ret += ft_strlen(s);
		(*ges)->zero = 1;
		(*ges)->ret++;
	}
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

static void	ft_pminus(char *ag, t_printf **ges)
{
	if ((*ges)->minus)
	{
		ft_putstr("0x");
		ft_putstr(ag);
	}
	if ((*ges)->zero)
	{
		ft_putstr("0x");
		if (ag[0] == '0')
			(*ges)->ret++;
	}
}

static int	ft_print_ag(t_printf **ges, const char *ag)
{
	int ret;

	ret = 0;
	if (!(*ges)->minus)
	{
		if (!(*ges)->zero)
			ft_putstr("0x");
		if (!(*ges)->impl)
		{
			if (ret == 0 && (*ges)->lng && !(*ges)->zero)
				ret += ft_prec_p(ges, ag) + 2;
			ft_putstr(ag);
		}
	}
	return (ret);
}

int			ft_printf_p(t_printf **ges)
{
	char	*ag;
	int		ret;
	void	*arg;

	arg = va_arg((*ges)->ap, void *);
	ag = ft_itoa_base((unsigned long)arg, 16);
	if (!ag)
		return (0);
	lowercase(&ag);
	ft_pminus(ag, ges);
	if ((ret = ft_setwidth_p((*ges)->width - ft_strlen(ag) - 2, ges, &ag)) > 0
		&& (*ges)->width && !(*ges)->zero)
		ret += ft_prec_p(ges, ag);
	else if (ret == 0 && (*ges)->width && !(*ges)->zero)
		ret += ft_prec_p(ges, ag) + 1;
	else if ((*ges)->width && !(*ges)->zero)
		ret += ft_prec_p(ges, ag) - 1;
	ret += ft_print_ag(ges, ag) + 2;
	if (!(*ges)->impl)
		ret += ft_strlen(ag);
	free(ag);
	return (ret - (*ges)->minus - (*ges)->plus - (*ges)->space - (*ges)->zero);
}

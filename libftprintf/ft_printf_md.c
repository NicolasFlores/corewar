/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_md.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 10:54:59 by nflores           #+#    #+#             */
/*   Updated: 2016/01/25 15:31:17 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_minus(char *ag, t_printf **ges)
{
	if ((*ges)->minus)
		ft_putstr(ag);
}

static int	ft_prec_md(t_printf **ges, const char *s)
{
	unsigned int	i;
	int				ret;

	i = 0;
	ret = 0;
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

static int	ft_set_flag(long long arg, t_printf **ges)
{
	int ret;

	ret = 0;
	if ((*ges)->space && arg >= 0 && !(*ges)->plus && !(*ges)->minus)
		ft_putchar(' ');
	else if ((*ges)->space)
		ret -= (*ges)->space;
	if ((*ges)->plus && arg >= 0 && !(*ges)->minus)
		ft_putchar('+');
	else if ((*ges)->plus)
		ret -= (*ges)->plus;
	return (ret);
}

int			ft_printf_md(t_printf **ges)
{
	char		*ag;
	int			ret;
	long int	arg;

	arg = va_arg((*ges)->ap, long int);
	if (arg == 9223372036854775807)
		ag = ft_itoa_base(arg, 10);
	else
		ag = ft_itoa(arg);
	if (!ag)
		return (0);
	ret = 0;
	ft_minus(ag, ges);
	ret += ft_setwidth((*ges)->width - ft_strlen(ag), ges, &ag);
	ret += ft_prec_md(ges, ag);
	ret += ft_set_flag(arg, ges);
	ft_putstr(ag);
	ret += ft_strlen(ag);
	free(ag);
	return (ret - (*ges)->minus - (*ges)->zero);
}

int			ft_printf_mmd(t_printf **ges)
{
	char		*ag;
	int			ret;
	long long	arg;

	arg = va_arg((*ges)->ap, long long);
	if (arg == 9223372036854775807)
		ag = ft_itoa_base(arg, 10);
	else
		ag = ft_itoa(arg);
	if (!ag)
		return (0);
	ret = 0;
	ft_minus(ag, ges);
	ret += ft_setwidth((*ges)->width - ft_strlen(ag), ges, &ag);
	ret += ft_prec_md(ges, ag);
	ret += ft_set_flag(arg, ges);
	ft_putstr(ag);
	ret += ft_strlen(ag);
	free(ag);
	return (ret - (*ges)->minus - (*ges)->zero);
}

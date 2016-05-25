/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_mx.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 11:28:03 by nflores           #+#    #+#             */
/*   Updated: 2016/01/26 13:43:48 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_print_ag(t_printf **ges, char *ag, int *ret)
{
	if (ft_atoi(ag) != 0 || !(*ges)->impl || ((*ges)->lng && (*ges)->width) ||
		(*ges)->sharp)
		ft_putstr(ag);
	if ((*ges)->impl)
		(*ret) = ft_strlen(ag);
	else
		(*ret) += ft_strlen(ag);
}

static void	ft_flag_modif(t_printf **ges, char *ag, char *sharp)
{
	if ((*ges)->flag == 15 || (*ges)->flag == 20)
	{
		lowercase(&ag);
		lowercase(&sharp);
	}
}

int			ft_printf_mx(t_printf **ges)
{
	char				*ag;
	char				*sharp;
	int					ret;
	unsigned long int	arg;

	arg = va_arg((*ges)->ap, unsigned long int);
	ag = ft_itoa_base(arg, 16);
	sharp = ft_strnew(1);
	ret = 0;
	if ((*ges)->sharp && arg != 0)
		sharp = ft_strdup("0X");
	if (!ag || !sharp)
		return (-1);
	ft_flag_modif(ges, ag, sharp);
	ft_putstr(sharp);
	ret += ft_setwidth_x((*ges)->width - ft_strlen(ag), ges, &ag);
	ret += ft_prec_x(ges, ag);
	ft_print_ag(ges, ag, &ret);
	if (ft_strlen(sharp) || (*ges)->sharp)
		ret += ft_strlen(sharp) - 1;
	free(ag);
	free(sharp);
	return (ret - (*ges)->plus - (*ges)->space - (*ges)->zero);
}

int			ft_printf_mmx(t_printf **ges)
{
	char				*ag;
	char				*sharp;
	int					ret;
	unsigned long long	arg;

	arg = va_arg((*ges)->ap, unsigned long long int);
	ag = ft_itoa_base(arg, 16);
	sharp = ft_strnew(1);
	ret = 0;
	if ((*ges)->sharp && arg != 0)
		sharp = ft_strdup("0X");
	if (!ag || !sharp)
		return (-1);
	ft_flag_modif(ges, ag, sharp);
	ft_putstr(sharp);
	ret += ft_setwidth_x((*ges)->width - ft_strlen(ag), ges, &ag);
	ret += ft_prec_x(ges, ag);
	ft_print_ag(ges, ag, &ret);
	if (ft_strlen(sharp) || (*ges)->sharp)
		ret += ft_strlen(sharp) - 1;
	free(ag);
	free(sharp);
	return (ret - (*ges)->plus - (*ges)->space - (*ges)->zero);
}

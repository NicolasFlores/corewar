/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_mu.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 11:00:09 by nflores           #+#    #+#             */
/*   Updated: 2016/01/19 15:52:47 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_printf_mu(t_printf **ges)
{
	char				*ag;
	int					ret;
	unsigned long int	arg;

	arg = va_arg((*ges)->ap, unsigned long int);
	ag = ft_itoa_base(arg, 10);
	if (!ag)
		return (0);
	ft_putstr(ag);
	ret = ft_strlen(ag);
	free(ag);
	return (ret - (*ges)->space);
}

int		ft_printf_mmu(t_printf **ges)
{
	char				*ag;
	int					ret;
	unsigned long long	arg;

	arg = va_arg((*ges)->ap, unsigned long long);
	ag = ft_itoa_base(arg, 10);
	if (!ag)
		return (0);
	ft_putstr(ag);
	ret = ft_strlen(ag);
	free(ag);
	return (ret - (*ges)->space);
}

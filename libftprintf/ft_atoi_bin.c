/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_bin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 09:53:03 by nflores           #+#    #+#             */
/*   Updated: 2016/01/21 16:22:33 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_pow_bin(int exp)
{
	int ret;

	if (exp == 0)
		return (1);
	ret = 2;
	while (exp > 1)
	{
		ret *= 2;
		exp--;
	}
	return (ret);
}

int			ft_atoi_bin(const char *str)
{
	int	i;
	int	ret;

	if (str == NULL)
		return (0);
	i = 0;
	ret = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '1')
			ret += ft_pow_bin(ft_strlen(str) - 1 - i);
		i++;
	}
	return (ret);
}

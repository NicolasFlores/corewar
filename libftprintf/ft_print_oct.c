/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_oct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/25 15:09:50 by nflores           #+#    #+#             */
/*   Updated: 2016/01/25 15:13:12 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_print_oct(char **oct)
{
	int ret;

	ret = 0;
	if (oct[0])
	{
		ret = ft_atoi_bin(oct[0]);
		write(1, &ret, 1);
		ret = 1;
	}
	if (oct[1])
	{
		ret = ft_atoi_bin(oct[1]);
		write(1, &ret, 1);
		ret = 2;
	}
	if (oct[2])
	{
		ret = ft_atoi_bin(oct[2]);
		write(1, &ret, 1);
		ret = 3;
	}
	return (ret);
}

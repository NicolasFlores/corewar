/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_modif.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 10:04:28 by nflores           #+#    #+#             */
/*   Updated: 2016/01/18 17:33:17 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_modif_jz(const char *str, unsigned int pos, t_printf **ges)
{
	if (str[pos] == 'j')
	{
		(*ges)->modif = 5;
		return (1);
	}
	else if (str[pos] == 'z')
	{
		(*ges)->modif = 6;
		return (1);
	}
	return (0);
}

static int	ft_modif_lh(const char *str, unsigned int pos, t_printf **ges)
{
	if (str[pos] == 'h')
	{
		if (str[pos + 1] == 'h')
		{
			(*ges)->modif = 1;
			return (2);
		}
		(*ges)->modif = 2;
		return (1);
	}
	else if (str[pos] == 'l')
	{
		if (str[pos + 1] == 'l')
		{
			(*ges)->modif = 4;
			return (2);
		}
		(*ges)->modif = 3;
		return (1);
	}
	return (0);
}

int			ft_modif(const char *str, unsigned int pos, t_printf **ges)
{
	int ret;

	ret = 0;
	(*ges)->modif = 0;
	ret += ft_modif_jz(str, pos, ges);
	ret += ft_modif_lh(str, pos, ges);
	return (ret);
}

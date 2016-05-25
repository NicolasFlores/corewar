/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prec_d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/25 15:23:35 by nflores           #+#    #+#             */
/*   Updated: 2016/01/26 15:46:40 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_prec_lng(t_printf **ges, char **s)
{
	int ret;

	ret = 0;
	if ((*ges)->lng >= (*ges)->width && (*ges)->width &&
		(int)ft_strlen(*s) <= (*ges)->lng)
	{
		ret += 2;
		if ((int)ft_strlen(*s) + 1 < (*ges)->lng - (*ges)->width &&
			((int)ft_strlen(*s) < (*ges)->width && (*ges)->width))
		{
			ret += ft_strlen(*s);
			if (*s[0] == '-')
				ret--;
		}
		else
		{
			ret += 2;
			if (*s[0] != '-' || (int)ft_strlen(*s) >= (*ges)->width)
				ret++;
		}
		(*ges)->ret++;
	}
	return (ret);
}

static int	ft_prec_neg(t_printf **ges, char **s)
{
	int		ret;
	char	*tmp;

	ret = 0;
	tmp = NULL;
	if (ft_strlen(*s) <= (unsigned int)(*ges)->lng && !(*ges)->width &&
		*s[0] == '-')
		ret += 2 + ft_strlen(*s);
	if (*s[0] == '-' && !(*ges)->plus && !(*ges)->space && (*ges)->lng)
	{
		ft_putchar('-');
		tmp = ft_strdup(*s + 1);
		free(*s);
		*s = ft_strdup(tmp);
		(*ges)->ret++;
	}
	free(tmp);
	return (ret);
}

int			ft_prec_d(t_printf **ges, char **s)
{
	unsigned int	i;
	int				ret;
	char			*lng;

	i = 0;
	ret = 0;
	ret += ft_prec_lng(ges, s);
	ret += ft_prec_neg(ges, s);
	lng = ft_itoa((*ges)->lng);
	if ((*ges)->lng && ft_strlen(*s) < (unsigned long)(*ges)->lng)
	{
		while (i < (*ges)->lng - ft_strlen(*s))
		{
			ft_putchar('0');
			i++;
		}
	}
	else if ((*ges)->lng)
		ret -= 1 + ft_strlen(lng);
	free(lng);
	return (ret);
}

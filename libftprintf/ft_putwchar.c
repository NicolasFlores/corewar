/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putwchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/25 16:15:26 by nflores           #+#    #+#             */
/*   Updated: 2016/01/26 15:16:10 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_putwchar(wint_t c)
{
	char	**oct;
	int		ret;

	if (c <= 127)
	{
		ft_putchar(c);
		return (1);
	}
	oct = ft_setoct_s(c);
	ret = ft_print_oct(oct);
	free(oct[0]);
	free(oct[1]);
	free(oct[2]);
	free(oct[3]);
	free(oct);
	return (ret);
}

int		ft_putwstr(wint_t *s)
{
	int ret;
	int i;

	i = 0;
	ret = 0;
	while (s[i] != 0)
	{
		if (s[i] <= 127)
		{
			ret++;
			ft_putchar(s[i]);
		}
		else
			ret += ft_putwchar(s[i]);
		i++;
	}
	return (ret);
}

size_t	ft_wcharlen(wint_t c)
{
	if (c <= 127)
		return (1);
	else if (c <= 2047)
		return (2);
	return (3);
}

size_t	ft_strwlen(wint_t *s)
{
	int i;
	int ret;

	i = 0;
	ret = 0;
	while (s[i])
	{
		if (s[i] <= 127)
			ret++;
		else if (s[i] <= 2047)
			ret += 2;
		else
			ret += 3;
		i++;
	}
	return (ret);
}

int		ft_ischar(wint_t *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] > 127)
			return (0);
		i++;
	}
	return (1);
}

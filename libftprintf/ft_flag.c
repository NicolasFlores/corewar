/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 10:38:24 by nflores           #+#    #+#             */
/*   Updated: 2016/01/26 15:31:08 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_width_int(const char *str, unsigned int pos, t_printf **ges)
{
	unsigned int i;
	unsigned int j;

	i = 0;
	j = 0;
	while (str[pos + i + 1] >= '0' && str[pos + i + 1] <= '9')
		i++;
	if (i >= 1)
		(*ges)->width = ft_atoi(str + pos + j + 1);
	else
		(*ges)->width = 0;
	return (i);
}

int			ft_width(const char *str, unsigned int pos, t_printf **ges)
{
	unsigned int i;

	i = 0;
	(*ges)->space = 0;
	while (str[pos + i + 1] == '#' || str[pos + i + 1] == '+' ||
		str[pos + i + 1] == ' ' || str[pos + i + 1] == '0' ||
		str[pos + i + 1] == '-')
	{
		if (str[i + pos + 1] == '#')
			(*ges)->sharp = 1;
		if (str[i + pos + 1] == '+')
			(*ges)->plus++;
		if (str[pos + i + 1] == ' ')
			(*ges)->space++;
		if (str[pos + i + 1] == '0')
			(*ges)->zero++;
		if (str[pos + i + 1] == '-')
			(*ges)->minus++;
		i++;
	}
	i += ft_width_int(str, pos + i, ges);
	return (i);
}

int			ft_prec(const char *str, unsigned int pos, t_printf **ges)
{
	unsigned int i;

	i = 0;
	if (str[pos + i + 1] == '.')
	{
		(*ges)->lng = ft_atoi(str + pos + i + 2);
		if ((*ges)->lng == 0)
		{
			(*ges)->lng = 1;
			(*ges)->impl = 1;
			(*ges)->ret--;
			if (ft_isdigit(str[pos + i + 2]))
				(*ges)->ret--;
		}
		i += 1;
		while (str[pos + i + 1] >= '0' && str[pos + i + 1] <= '9')
			i++;
	}
	return (i + 1);
}

int			ft_flag(const char *str, unsigned int pos, t_printf **ges)
{
	char	*flag;
	int		i;

	flag = "sSpdDioOuUxXcC%";
	i = 0;
	while (str[pos] != flag[i] && flag[i] != '\0')
		i++;
	if (flag[i] == '\0')
	{
		(*ges)->impl = 1;
		i = -1;
	}
	else if (flag[i] == '%')
	{
		if (!check_pct(str, pos + 1, ges))
			return (-1);
	}
	if ((*ges)->space && i != -1 && flag[i] == '%')
		(*ges)->ret--;
	return (i);
}

int			ft_ptr(t_printf **ges)
{
	int			ret;
	static int	(*ptrfct[])(t_printf **) = {
		ft_printf_s, ft_printf_ms, ft_printf_p, ft_printf_d,
		ft_printf_md, ft_printf_d, ft_printf_o, ft_printf_mo,
		ft_printf_u, ft_printf_mu, ft_printf_x, ft_printf_x,
		ft_printf_c, ft_printf_mc, ft_printf_pct, ft_printf_mx,
		ft_printf_mx, ft_printf_mmo, ft_printf_mmu, ft_printf_mmd,
		ft_printf_mmx, ft_printf_mmx};

	ret = 0;
	ret += ft_setmodif(ges);
	ret += ptrfct[(*ges)->flag](ges);
	return (ret);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/06 14:27:10 by nflores           #+#    #+#             */
/*   Updated: 2016/01/26 12:56:47 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_printf	*ft_print_init(t_printf **ges)
{
	*ges = (t_printf *)malloc(sizeof(t_printf));
	if (!(*ges))
		return (NULL);
	(*ges)->width = 0;
	(*ges)->sharp = 0;
	(*ges)->plus = 0;
	(*ges)->minus = 0;
	(*ges)->space = 0;
	(*ges)->zero = 0;
	(*ges)->flag = 0;
	(*ges)->lng = 0;
	(*ges)->modif = 0;
	(*ges)->ret = 0;
	(*ges)->pct = 0;
	(*ges)->impl = 0;
	return (*ges);
}

static int		ft_printf_flag(const char *str, t_printf **ges, unsigned int *i)
{
	if (str[*i] == '%')
	{
		(*ges)->pct++;
		(*i) += ft_width(str, *i, ges);
		(*i) += ft_prec(str, *i, ges);
		(*i) += ft_modif(str, *i, ges);
		(*ges)->flag = ft_flag(str, *i, ges);
		if ((*ges)->flag == 14)
			(*ges)->pct++;
		if ((*ges)->flag == -1 && !(*ges)->space && (*ges)->pct != 1)
			return (0);
		if ((*ges)->pct == 1 && (*ges)->flag == -1 && !(*ges)->space)
			(*ges)->ret++;
		if ((*ges)->flag != -1)
		{
			(*i)++;
			(*ges)->ret += ft_ptr(ges) - 2;
		}
		else
			(*ges)->ret -= 2;
	}
	return (1);
}

static void		ft_print_width(t_printf **ges)
{
	if ((*ges)->width && (*ges)->flag == -1)
	{
		while (0 < (*ges)->width - 1)
		{
			if ((*ges)->zero)
				ft_putchar('0');
			else
				ft_putchar(' ');
			(*ges)->width--;
			(*ges)->ret++;
		}
		(*ges)->ret -= (*ges)->width + 2;
		(*ges)->width--;
	}
}

static void		ft_check_ret(const char *str, t_printf **ges, unsigned int *i)
{
	if (ft_isalpha(str[(*i)]) && str[(*i) + 2] == '\0' && !(*ges)->minus)
		(*ges)->ret++;
}

int				ft_printf(const char *str, ...)
{
	t_printf		*ges;
	unsigned int	i;

	i = 0;
	ges = ft_print_init(&ges);
	va_start(ges->ap, str);
	while (str[i] != '\0')
	{
		if (!ft_printf_flag(str, &ges, &i))
			return (0);
		if (str[i] != '%' && str[i] != '\0')
		{
			if (!(ges->impl) || ges->minus)
				write(1, str + i, 1);
			ft_print_width(&ges);
			if (ges->impl && !(ges->minus))
				write(1, str + i, 1);
			ft_check_ret(str, &ges, &i);
			i++;
		}
	}
	va_end(ges->ap);
	i += ges->ret;
	free(ges);
	return (i);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_ms.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 12:36:24 by nflores           #+#    #+#             */
/*   Updated: 2016/01/25 16:29:22 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_width_init(t_printf **ges, wint_t *s, int *i, int *n)
{
	if ((*ges)->width && (*ges)->width > *n && (*ges)->lng)
		*n = (*ges)->width - (*ges)->lng + 1;
	if (ft_ischar(s))
	{
		while (*i < (*ges)->lng)
		{
			if (ft_wcharlen(s[*i]) == 1)
			{
				(*n)--;
				(*ges)->ret--;
			}
			(*i)++;
		}
		if ((*ges)->zero)
			(*n)++;
	}
}

static int	ft_setwidth_ms(int n, t_printf **ges, wint_t *s)
{
	int		i;
	char	c;

	i = 0;
	c = ' ';
	ft_width_init(ges, s, &i, &n);
	i = 0;
	if (n > 0)
	{
		if ((*ges)->zero && !(*ges)->minus && n - (*ges)->lng > 0)
			c = '0';
		while (i < n)
		{
			write(1, &c, 1);
			i++;
		}
		return (i - 2);
	}
	else if ((*ges)->width)
		return (i - 1);
	return (0);
}

static int	ft_prec_init(t_printf **ges, wint_t *s, int *i, int *n)
{
	if ((*ges)->lng)
	{
		while (*i < (*ges)->lng)
		{
			if (*n + (int)ft_wcharlen(s[*i]) <= (*ges)->lng && !(*ges)->impl)
			{
				ft_putwchar(s[*i]);
				(*n) += ft_wcharlen(s[*i]);
				(*i)++;
			}
			else
			{
				if ((*ges)->impl && ft_ischar(s))
					(*ges)->ret++;
				break ;
			}
		}
		return (1);
	}
	return (0);
}

static int	ft_prec_ms(t_printf **ges, wint_t *s)
{
	int i;
	int n;

	i = 0;
	n = 0;
	if (!ft_prec_init(ges, s, &i, &n))
		return (ft_putwstr(s));
	if ((*ges)->lng > (*ges)->width && (*ges)->width)
		return (n - i + 2);
	return (i);
}

int			ft_printf_ms(t_printf **ges)
{
	wint_t	*arg;
	int		ret;

	if ((*ges)->plus)
		return (0);
	arg = va_arg((*ges)->ap, wint_t *);
	if (arg == NULL)
	{
		ft_putstr("(null)");
		return (6 - (*ges)->space - (*ges)->plus);
	}
	ret = 0;
	if (!(*ges)->minus)
		ret += ft_setwidth_ms((*ges)->width - ft_strwlen(arg), ges, arg);
	ret += ft_prec_ms(ges, arg) + (*ges)->impl;
	if ((*ges)->minus)
		ret += ft_setwidth_ms((*ges)->width - ft_strwlen(arg), ges, arg);
	return (ret - (*ges)->plus - (*ges)->space - (*ges)->zero - (*ges)->minus);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_s.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 14:16:57 by nflores           #+#    #+#             */
/*   Updated: 2016/01/26 13:34:06 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_print_prec(t_printf **ges, char **s, int *ret, unsigned int *i)
{
	while ((int)(*i) < (int)((*ges)->width - ft_strlen(*s) - (*ges)->lng + 1))
	{
		ft_putchar(' ');
		(*i)++;
		(*ret)++;
	}
	if ((*ges)->impl)
	{
		(*ges)->lng = 0;
		(*ges)->ret++;
	}
	(*s)[(*ges)->lng] = '\0';
	ft_putstr(*s);
	(*ret) -= 1 + ft_strlen(ft_itoa((*ges)->lng));
}

static void	ft_print_space(t_printf **ges, char **s, unsigned int *i)
{
	while ((*i) < (*ges)->lng - ft_strlen(*s))
	{
		ft_putchar(' ');
		(*i)++;
	}
}

static int	ft_prec_s(t_printf **ges, char *s)
{
	unsigned int	i;
	int				ret;

	i = 0;
	ret = 0;
	if ((*ges)->lng && ft_strlen(s) < (unsigned int)(*ges)->lng &&
		(*ges)->width > (*ges)->lng)
		ft_print_space(ges, &s, &i);
	else if ((*ges)->lng && ft_strlen(s) >= (unsigned int)(*ges)->lng)
	{
		ft_print_prec(ges, &s, &ret, &i);
	}
	else
	{
		ft_putstr(s);
		if ((*ges)->lng)
			ret -= (*ges)->lng - ft_strlen(s);
		if ((*ges)->width && !(*ges)->zero)
			ret += (*ges)->lng - (*ges)->width;
	}
	if ((*ges)->lng && !ret && (*ges)->width)
		ft_putstr(s);
	return (ret);
}

int			ft_printf_s(t_printf **ges)
{
	char	*ag;
	int		ret;
	char	*arg;

	arg = va_arg((*ges)->ap, char *);
	if (arg != NULL)
		ag = ft_strdup(arg);
	else
		ag = ft_strdup("(null)");
	if (!ag)
		return (0);
	ret = 0;
	if (!(*ges)->minus)
		ret += ft_setwidth_s((*ges)->width, ges, &ag);
	ret += ft_prec_s(ges, ag);
	ret += ft_strlen(ag);
	if ((*ges)->minus)
		ret += ft_setwidth_s((*ges)->width - ft_strlen(ag), ges, &ag);
	free(ag);
	return (ret - (*ges)->plus - (*ges)->space - (*ges)->minus);
}

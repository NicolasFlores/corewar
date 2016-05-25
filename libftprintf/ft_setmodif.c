/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setmodif.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 14:24:03 by nflores           #+#    #+#             */
/*   Updated: 2016/01/19 15:57:24 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_setl(t_printf **ges)
{
	if ((*ges)->flag == 12 || (*ges)->flag == 0 || (*ges)->flag == 6 ||
		(*ges)->flag == 8)
		(*ges)->flag += 1;
	else if ((*ges)->flag == 3 || (*ges)->flag == 5)
		(*ges)->flag = 4;
	else if ((*ges)->flag == 10 || (*ges)->flag == 11)
		(*ges)->flag += 5;
	else if ((*ges)->flag == 7)
		(*ges)->flag = 17;
	else if ((*ges)->flag == 9)
		(*ges)->flag = 18;
	else if ((*ges)->flag == 4)
		(*ges)->flag = 19;
	return (-1);
}

static int	ft_setll(t_printf **ges)
{
	if ((*ges)->flag == 3 || (*ges)->flag == 5)
		(*ges)->flag = 19;
	else if ((*ges)->flag == 6)
		(*ges)->flag = 17;
	else if ((*ges)->flag == 8)
		(*ges)->flag = 18;
	else if ((*ges)->flag == 10 || (*ges)->flag == 11)
		(*ges)->flag += 10;
	return (-2);
}

static int	ft_setz(t_printf **ges)
{
	if ((*ges)->flag == 3 || (*ges)->flag == 5)
		(*ges)->flag = 19;
	else if ((*ges)->flag == 8)
		(*ges)->flag = 9;
	else if ((*ges)->flag == 6)
		(*ges)->flag = 17;
	else if ((*ges)->flag == 10 || (*ges)->flag == 11)
		(*ges)->flag += 10;
	return (-1);
}

int			ft_setmodif(t_printf **ges)
{
	if ((*ges)->modif == 3)
		return (ft_setl(ges));
	else if ((*ges)->modif == 4)
		return (ft_setll(ges));
	else if ((*ges)->modif == 5 || (*ges)->modif == 6)
		return (ft_setz(ges));
	else if ((*ges)->modif == 1)
		return (-2);
	else if ((*ges)->modif == 2)
		return (-1);
	return (0);
}

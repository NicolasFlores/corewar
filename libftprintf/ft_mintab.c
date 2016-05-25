/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mintab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 15:12:45 by nflores           #+#    #+#             */
/*   Updated: 2015/12/01 15:15:51 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_mintab(const int *tab)
{
	int i;
	int ret;

	i = 1;
	if (!tab)
		return (0);
	ret = tab[0];
	while (tab[i])
	{
		if (tab[i] < ret)
			ret = tab[i];
		i++;
	}
	return (ret);
}

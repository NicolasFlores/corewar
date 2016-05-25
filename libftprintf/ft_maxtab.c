/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_maxtab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 15:16:03 by nflores           #+#    #+#             */
/*   Updated: 2015/12/01 15:17:53 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_maxtab(const int *tab)
{
	int i;
	int ret;

	if (!tab)
		return (0);
	i = 1;
	ret = tab[0];
	while (tab[i])
	{
		if (tab[i] > ret)
			ret = tab[i];
		i++;
	}
	return (ret);
}

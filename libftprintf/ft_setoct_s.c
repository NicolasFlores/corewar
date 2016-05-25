/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setoct_s.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 14:06:06 by nflores           #+#    #+#             */
/*   Updated: 2016/01/26 14:07:35 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		**ft_setoct_s(wint_t c)
{
	char	**oct;
	char	*mask;

	oct = (char **)malloc(sizeof(char *) * 4);
	if (!oct)
		return (NULL);
	mask = ft_mask(c);
	oct[0] = ft_strsub(mask, 0, 8);
	oct[1] = ft_strsub(mask, 8, 8);
	oct[2] = ft_strsub(mask, 16, 8);
	oct[3] = NULL;
	free(mask);
	return (oct);
}

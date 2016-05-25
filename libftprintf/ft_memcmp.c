/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 14:23:46 by nflores           #+#    #+#             */
/*   Updated: 2015/11/24 14:33:13 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char *cmp1;
	unsigned char *cmp2;

	cmp1 = (unsigned char *)s1;
	cmp2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	else if (cmp1[0] == cmp2[0])
		return (ft_memcmp(cmp1 + 1, cmp2 + 1, n - 1));
	return (cmp1[0] - cmp2[0]);
}

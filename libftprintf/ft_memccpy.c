/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 12:50:54 by nflores           #+#    #+#             */
/*   Updated: 2015/11/24 14:35:57 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned int	i;
	unsigned char	*set_dst;
	unsigned char	*cp_src;

	i = 0;
	set_dst = dst;
	cp_src = (unsigned char *)src;
	while (i < n)
	{
		set_dst[i] = cp_src[i];
		if (set_dst[i] == (unsigned char)c)
			return (set_dst + i + 1);
		i++;
	}
	return (NULL);
}

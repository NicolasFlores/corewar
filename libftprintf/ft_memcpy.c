/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 12:33:29 by nflores           #+#    #+#             */
/*   Updated: 2015/11/24 14:37:20 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memcpy(void *dst, const void *src, size_t n)
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
		i++;
	}
	return (dst);
}

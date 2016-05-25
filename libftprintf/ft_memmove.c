/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 13:43:54 by nflores           #+#    #+#             */
/*   Updated: 2015/11/24 13:53:07 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void		*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned int	i;
	unsigned char	*set_dst;
	unsigned char	*tmp;

	i = 0;
	set_dst = dst;
	tmp = (unsigned char *)malloc(sizeof(char) * len);
	tmp = (unsigned char *)ft_memcpy(tmp, src, len);
	set_dst = (unsigned char *)ft_memcpy(set_dst, tmp, len);
	return (dst);
}

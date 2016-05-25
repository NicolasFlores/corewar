/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 10:28:23 by nflores           #+#    #+#             */
/*   Updated: 2015/11/30 15:33:05 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t			ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	idst;
	unsigned int	n;

	i = 0;
	j = 0;
	idst = ft_strlen(dst);
	n = size;
	while (dst[i] != '\0' && n > 0)
	{
		i++;
		n--;
	}
	if (n == 0)
		return (ft_strlen(src) + size);
	while (src[j] != '\0' && j < n - 1)
	{
		dst[i] = src[j];
		j++;
		i++;
	}
	dst[i] = '\0';
	return (idst + ft_strlen(src));
}

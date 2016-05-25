/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 14:13:59 by nflores           #+#    #+#             */
/*   Updated: 2015/11/24 14:20:59 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memchr(const void *s, int c, size_t n)
{
	unsigned int	i;
	unsigned char	*find_s;

	i = 0;
	find_s = (unsigned char *)s;
	while (i < n)
	{
		if (find_s[i] == (unsigned char)c)
			return (find_s + i);
		i++;
	}
	return (NULL);
}

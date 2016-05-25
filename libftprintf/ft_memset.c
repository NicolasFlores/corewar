/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 12:00:21 by nflores           #+#    #+#             */
/*   Updated: 2015/11/24 12:38:41 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*b_set;
	unsigned int	i;

	b_set = b;
	i = 0;
	while (i < len)
	{
		b_set[i] = (unsigned char)c;
		i++;
	}
	return (b);
}

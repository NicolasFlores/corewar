/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 15:10:59 by nflores           #+#    #+#             */
/*   Updated: 2015/11/27 16:06:34 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strchr(const char *s, int c)
{
	unsigned int	i;
	char			*ret;

	ret = (char *)s;
	i = 0;
	while (ret[i] != '\0')
	{
		if (ret[i] == (char)c)
			return (ret + i);
		i++;
	}
	if (ret[i] == (char)c)
		return (ret + i);
	return (NULL);
}

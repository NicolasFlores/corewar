/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 15:16:07 by nflores           #+#    #+#             */
/*   Updated: 2015/11/26 17:19:16 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strrchr(const char *s, int c)
{
	char	*ret;
	int		i;

	i = (int)ft_strlen(s);
	ret = (char *)s;
	while (i >= 0)
	{
		if (s[i] == (char)c)
		{
			ret = (char *)(s + i);
			return (ret);
		}
		i--;
	}
	return (NULL);
}

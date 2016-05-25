/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 11:00:31 by nflores           #+#    #+#             */
/*   Updated: 2015/11/27 14:40:37 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strstr(const char *s1, const char *s2)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	k;
	char			*ret;

	i = 0;
	if (s2 == NULL || s2[0] == '\0')
		return ((char *)s1);
	while (s1[i] != '\0')
	{
		j = 0;
		k = i;
		ret = (char *)(s1 + i);
		while (s1[k] == s2[j] || s2[j] == '\0')
		{
			if (s2[j] == '\0')
				return (ret);
			k++;
			j++;
		}
		i++;
	}
	return (NULL);
}

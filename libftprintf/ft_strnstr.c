/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 11:14:20 by nflores           #+#    #+#             */
/*   Updated: 2015/11/28 12:54:39 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	k;
	unsigned int	size;

	i = 0;
	if (s2 == NULL || s2[0] == '\0')
		return ((char *)s1);
	while (s1[i] != '\0' && i < n)
	{
		j = 0;
		k = i;
		size = n - i;
		while ((s1[k] == s2[j] && size > 0) || s2[j] == '\0')
		{
			if (s2[j] == '\0')
				return ((char *)(s1 + i));
			k++;
			j++;
			size--;
		}
		i++;
	}
	return (NULL);
}

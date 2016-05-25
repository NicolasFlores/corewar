/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 16:26:19 by nflores           #+#    #+#             */
/*   Updated: 2015/11/27 17:27:53 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	else if (n == 1)
		return ((unsigned char)(*s1) - (unsigned char)(*s2));
	else if (*s1 == '\0' && *s2 == '\0')
		return (0);
	else if (*s1 == *s2)
		return (ft_strncmp(s1 + 1, s2 + 1, n - 1));
	return ((unsigned char)(*s1) - (unsigned char)(*s2));
}

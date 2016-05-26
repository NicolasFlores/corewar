/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 10:48:26 by nflores           #+#    #+#             */
/*   Updated: 2016/05/26 11:26:52 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char		*ft_strdup(const char *s1)
{
	char *ret;

	ret = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (ret == NULL)
		return (NULL);
	ft_strcpy(ret, s1);
	return (ret);
}

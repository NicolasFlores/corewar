/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 16:45:27 by nflores           #+#    #+#             */
/*   Updated: 2015/11/30 12:55:15 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	ft_nbword(char const *s, char c)
{
	int i;
	int ret;

	i = 0;
	while (s[i] == c)
		i++;
	if (s[i] == '\0')
		return (0);
	ret = 1;
	while (s[i] != '\0')
	{
		while (s[i] != c)
			i++;
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			ret++;
	}
	return (ret);
}

static int	ft_size(char const *s, char c)
{
	int i;
	int ret;

	i = 0;
	while (s[i] == c)
		i++;
	if (s[i] == '\0')
		return (0);
	ret = 1;
	while (s[i] != '\0')
	{
		while (s[i] != c)
		{
			i++;
			ret++;
		}
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			ret++;
	}
	return (ret);
}

char		**ft_strsplit(char const *s, char c)
{
	char			**ret;
	int				i;
	unsigned int	j;
	unsigned int	start;
	unsigned int	end;

	ret = (char **)malloc(sizeof(char) * (ft_strlen(s) + ft_size(s, c) + 1));
	if (!ret)
		return (NULL);
	i = 0;
	j = 0;
	while (i < ft_nbword(s, c))
	{
		while (s[j] == c)
			j++;
		start = j;
		while (s[j] != c && s[j] != '\0')
			j++;
		end = j - start;
		if (s[j] != '\0' || start == 0 || i == 0)
			ret[i] = ft_strsub(s, start, end);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

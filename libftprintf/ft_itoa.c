/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 15:17:00 by nflores           #+#    #+#             */
/*   Updated: 2016/05/26 14:37:55 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ft_printf.h"

static int	ft_nbchar(long int n)
{
	int			ret;
	long int	nb;

	nb = n;
	ret = 1;
	if (nb < 0)
	{
		ret++;
		nb = -nb;
	}
	while (nb > 9)
	{
		ret += 1;
		nb /= 10;
	}
	return (ret);
}

static int	ft_pow(long int n, int p)
{
	int			i;
	long int	nb;

	i = 1;
	nb = n;
	while (i < p)
	{
		nb *= n;
		i++;
	}
	return (nb);
}

static char	*ft_itoa_m(void)
{
	char	*ret;

	ret = (char *)malloc(sizeof(char) * 21);
	if (!ret)
		return (NULL);
	ret = ft_strcpy(ret, "-9223372036854775808");
	return (ret);
}

static char	*ft_itoa_o(long int n)
{
	char		*ret;
	int			i;
	long int	nb;

	i = 0;
	nb = n;
	ret = (char *)malloc(sizeof(char) * (ft_nbchar(nb) + 1));
	if (!ret)
		return (NULL);
	if (n < 0)
	{
		ret[0] = '-';
		i++;
		n = -n;
	}
	while (i < ft_nbchar(nb))
	{
		ret[i] = 48 + (n / ft_pow((long)10, ft_nbchar(nb) - i - 1));
		n %= ft_pow((long)10, ft_nbchar(nb) - i - 1);
		i++;
	}
	ret[i - 1] = 48 + n % 10;
	ret[i] = '\0';
	return (ret);
}

char		*ft_itoa(long int n)
{
	char *ret;

	if (n == LONG_MIN || n == LLONG_MIN)
	{
		ret = ft_itoa_m();
		return (ret);
	}
	ret = ft_itoa_o(n);
	return (ret);
}

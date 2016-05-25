/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/06 15:22:06 by nflores           #+#    #+#             */
/*   Updated: 2016/01/07 10:23:32 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static unsigned int		ft_nbchar(unsigned long n, unsigned int base)
{
	unsigned int	ret;
	unsigned long	nb;

	nb = n;
	ret = 1;
	while (nb > base - 1)
	{
		ret += 1;
		nb /= base;
	}
	return (ret);
}

static unsigned long	ft_pow(unsigned long n, unsigned long p)
{
	unsigned long i;
	unsigned long nb;

	i = 1;
	nb = n;
	while (i < p)
	{
		nb *= n;
		i++;
	}
	return (nb);
}

char					*ft_itoa_base(unsigned long n, unsigned int base)
{
	char			*ret;
	unsigned int	i;
	unsigned long	nb;

	i = 0;
	nb = n;
	ret = (char *)malloc(sizeof(char) * ft_nbchar(n, base) + 1);
	if (!ret)
		return (NULL);
	while (i < ft_nbchar(nb, base))
	{
		if (n / ft_pow(base, ft_nbchar(nb, base) - i - 1) < 10)
			ret[i] = 48 + (n / ft_pow(base, ft_nbchar(nb, base) - i - 1));
		else
			ret[i] = 'A' + (n / ft_pow(base, ft_nbchar(nb, base) - i - 1)) - 10;
		n %= ft_pow(base, ft_nbchar(nb, base) - i - 1);
		i++;
	}
	if (n % base < 10)
		ret[i - 1] = 48 + n % base;
	else
		ret[i - 1] = 'A' + n % base - 10;
	ret[i] = '\0';
	return (ret);
}

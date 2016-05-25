/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_c.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 13:54:58 by nflores           #+#    #+#             */
/*   Updated: 2016/01/26 16:04:56 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_printf_c(t_printf **ges)
{
	char	*ag;
	char	arg;
	int		ret;

	ag = ft_strnew(1);
	if (!ag)
		return (0);
	arg = va_arg((*ges)->ap, int);
	ret = 0;
	if ((*ges)->sharp || (*ges)->plus)
		return (0);
	ret -= (*ges)->space;
	if (ft_setwidth_c((*ges)->width - 1, ges) == 0 && (*ges)->width)
		ret++;
	ag[0] = (char)arg;
	ft_putchar(ag[0]);
	free(ag);
	if ((*ges)->impl && (*ges)->width)
		ret -= (*ges)->impl;
	if ((*ges)->lng > 1)
		ret -= 2;
	return (ret + 1 - (*ges)->zero);
}

static void	ft_set_mask(char *mask, char *bin)
{
	int i;
	int j;

	i = ft_strlen(mask) - 1;
	j = ft_strlen(bin) - 1;
	while (j >= 0)
	{
		if (mask[i] != '1' && mask[i] != '0')
		{
			mask[i] = bin[j];
			i--;
			j--;
		}
		else
			i--;
	}
	j = 0;
	while (mask[j] != '\0')
	{
		if (mask[j] == 'x')
			mask[j] = '0';
		j++;
	}
}

char		*ft_mask(wint_t c)
{
	char	*mask;
	char	*bin;

	mask = NULL;
	if (c <= 127)
		mask = ft_strdup("0xxxxxxx");
	else if (c <= 2047)
		mask = ft_strdup("110xxxxx10xxxxxx");
	else
		mask = ft_strdup("1110xxxx10xxxxxx10xxxxxx");
	bin = ft_itoa_base(c, 2);
	if (!mask || !bin)
		return (NULL);
	ft_set_mask(mask, bin);
	free(bin);
	return (mask);
}

char		**ft_setoct(t_printf **ges)
{
	char	**oct;
	wint_t	arg;
	char	*mask;

	arg = va_arg((*ges)->ap, wint_t);
	oct = (char **)malloc(sizeof(char *) * 4);
	if (!oct)
		return (NULL);
	mask = ft_mask(arg);
	oct[0] = ft_strsub(mask, 0, 8);
	oct[1] = ft_strsub(mask, 8, 8);
	oct[2] = ft_strsub(mask, 16, 8);
	oct[3] = NULL;
	free(mask);
	return (oct);
}

int			ft_printf_mc(t_printf **ges)
{
	int		ret;
	char	**oct;

	if ((*ges)->sharp || (*ges)->plus)
		return (0);
	oct = ft_setoct(ges);
	ret = ft_print_oct(oct);
	if ((*ges)->lng > 1)
		ret -= 2;
	free(oct[0]);
	free(oct[1]);
	free(oct[2]);
	free(oct[3]);
	free(oct);
	return (ret - (*ges)->space - (*ges)->zero);
}

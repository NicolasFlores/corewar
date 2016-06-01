/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_newchamp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 14:08:30 by nflores           #+#    #+#             */
/*   Updated: 2016/05/30 13:20:22 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/vm.h"

t_champ		*ft_newchamp(char *name, char *comment, int t_size, int pr_size)
{
	t_champ *ret;
	int		i;

	ret = (t_champ *)malloc(sizeof(t_champ));
	if (!ret)
		exit(write(2, "Malloc Error\n", 13));
	ret->name = ft_strdup(name);
	ret->comment = ft_strdup(comment);
	ret->prog = (char *)malloc(sizeof(char) * pr_size);
	if (!(ret->name) || !(ret->comment) || !(ret->prog))
		exit(write(2, "Malloc Error\n", 13));
	ret->pc = -1;
	ret->total_size = t_size;
	ret->prog_size = pr_size;
	i = -1;
	while (++i < REG_NUMBER)
		ret->reg[i] = 0;
	return (ret);
}

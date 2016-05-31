/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_value.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 14:37:26 by nflores           #+#    #+#             */
/*   Updated: 2016/05/27 13:56:23 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/vm.h"

void	write_value(t_mem **mem, int value, int addr, t_champ *champ)
{
	t_mem	*tmp;
	int		i;

	i = 0;
	tmp = *mem;
	if (addr >= 0)
		while (i < addr - 1)
		{
			tmp = tmp->next;
			i++;
		}
	else
		while (i > addr - 1)
		{
			tmp = tmp->prev;
			i--;
		}
	i = REG_SIZE;
	while (i > 0)
	{
		if (i == 1)
			tmp->oct = 0x000000ff & value;
		else
			tmp->oct = (value >> ((i - 1) * 8)) | (0xff << ((i - 1) * 8));
		tmp->champ_wr = champ->num;
		tmp = tmp->next;
		i--;
	}
}

int		read_value(t_mem *mem, int addr, int size)
{
	int i;
	int ret;

	i = 0;
	if (i <= addr)
		while (i < addr - 1)
		{
			mem = mem->next;
			i++;
		}
	else
		while (i > addr + 1)
		{
			mem = mem->prev;
			i--;
		}
	ret = 0;
	if (size == 1)
		return (mem->oct);
	i = size;
	while (i > 0)
	{
		ret += (mem->oct << ((i - 1) * 8)) & (0xff << ((i - 1) * 8));
		i--;
		mem = mem->next;
	}
	return (ret);
}

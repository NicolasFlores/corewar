/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_index.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/07 16:40:20 by nflores           #+#    #+#             */
/*   Updated: 2016/06/07 17:15:20 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/vm.h"

int		ft_index_value(t_mem *mem, int val, int size, char dir)
{
	if (dir == 1)
	{
		if (val >= 0)
			return (size + val % IDX_MOD);
		else
			return (size - (val * -1) % IDX_MOD);
	}
	if (val >= 0)
		return (read_value(mem, size + val % IDX_MOD + 1, REG_SIZE));
	return (read_value(mem, size - (val * -1) % IDX_MOD - 1, REG_SIZE));
}

void	ft_set_addrind(t_mem *mem, int addr, int *reg)
{
	if (addr >= 0)
	{
		addr %= IDX_MOD;
		*reg = read_value(mem, addr + 1, REG_SIZE);
	}
	else
	{
		addr = -((addr * -1) % IDX_MOD);
		*reg = read_value(mem, addr - 1, REG_SIZE);
	}
}

int		ft_index_value_add(int val)
{
	if (val >= 0)
		return (val % IDX_MOD);
	return (-((val * -1) % IDX_MOD));
}

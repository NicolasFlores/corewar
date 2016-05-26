/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_param.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 12:53:05 by nflores           #+#    #+#             */
/*   Updated: 2016/05/26 10:34:16 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/vm.h"

void	set_param(t_mem *mem, t_param *param, t_partype par, t_proc *proc)
{
	int		val;
	t_reg	reg;

	if (par == REG)
	{
		reg = proc->champ->reg[read_value(mem, proc->pc + 1, T_REG)];
		ft_printf("reg[%d] = %d\n", read_value(mem, proc->pc + 1, T_REG), reg.value);
		param->reg = &reg;
	}
	else if (par == IND)
	{
		val = read_value(mem, proc->pc + 1, IND_SIZE);
		ft_printf("ind : %d\n", val);
		param->ind = &val;
	}
	else
	{
		val = read_value(mem, proc->pc + 1, DIR_SIZE);
		ft_printf("dir : %d\n", val);
		param->dir = &val;
	}
}

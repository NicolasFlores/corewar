/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_param.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 12:53:05 by nflores           #+#    #+#             */
/*   Updated: 2016/05/27 13:13:57 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/vm.h"

void	set_param(t_mem *mem, t_param *param, t_partype par, t_proc *proc)
{
	t_reg	reg;

	if (par == REG)
	{
		reg = proc->champ->reg[read_value(mem, proc->pc + 1, T_REG) - 1];
		ft_printf("reg[%d] = %d\n", read_value(mem, proc->pc + 1, T_REG) - 1, reg.value);
		param->reg = &reg;
	}
	else if (par == IND)
	{
		param->ind = read_value(mem, proc->pc + 1, IND_SIZE);
		ft_printf("ind : %d\n", param->ind);
	}
	else if (par == DIRI)
	{
		param->dir = read_value(mem, proc->pc + 1, DIR_SIZE / 2);
		ft_printf("dir : %d\n", param->dir);
	}
	else
	{
		param->dir = read_value(mem, proc->pc + 1, DIR_SIZE);
		ft_printf("dir : %d\n", param->dir);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_param.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 12:53:05 by nflores           #+#    #+#             */
/*   Updated: 2016/05/30 16:22:42 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/vm.h"

void	set_param(t_mem *mem, t_param *param, t_partype par, t_proc *proc)
{
	int rv;

	if (par == REG)
	{
		rv = read_value(mem, proc->pc + 1, T_REG) % 16;
		if (rv == 0)
			rv = 16;
//		ft_printf("r%d = %d\n", rv, proc->champ->reg[rv - 1]);
		param->reg = &(proc->champ->reg[rv - 1]);
	}
	else if (par == IND)
	{
		param->ind = read_value(mem, proc->pc + 1, IND_SIZE);
//		ft_printf("ind : %d\n", param->ind);
	}
	else if (par == DIRI)
	{
		param->dir = read_value(mem, proc->pc + 1, DIR_SIZE / 2);
//		ft_printf("dir : %d\n", param->dir);
	}
	else
	{
		param->dir = read_value(mem, proc->pc + 1, DIR_SIZE);
//		ft_printf("dir : %d\n", param->dir);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_param.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 12:53:05 by nflores           #+#    #+#             */
/*   Updated: 2016/05/25 16:58:44 by nflores          ###   ########.fr       */
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
		param->reg = &reg;
	}
	else if (par == IND)
	{
		val = read_value(mem, proc->pc + 1, IND_SIZE);
		param->ind = &val;
	}
	else
	{
		val = read_value(mem, proc->pc + 1, DIR_SIZE);
		param->dir = &val;
	}
}

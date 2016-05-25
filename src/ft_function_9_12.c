/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_function_9_12.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 15:56:38 by nflores           #+#    #+#             */
/*   Updated: 2016/05/25 16:46:47 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/vm.h"

int		ft_zjmp(t_vm **vm, t_param **param, t_proc **exec_proc, t_proc **proc)
{
	if (*(param[0]->dir) >= 0)
		(*proc)->pc += *(param[0]->dir) % IDX_MOD;
	else
		(*proc)->pc -= (*(param[0]->dir) * -1) % IDX_MOD;
	if ((*proc)->champ->carry)
		(*proc)->champ->carry = 0;
	else
		(*proc)->champ->carry = 1;
	return (20);
}

int		ft_ldi(t_vm **vm, t_param **param, t_proc **exec_proc, t_proc **proc)
{
	int addr;

	if (param[0]->dir != NULL)
		addr = (*(param[0]->dir)) % IDX_MOD;
	else if (param[0]->ind != NULL)
	{
		if (*(param[0]->ind) >= 0)
			addr = read_value((*vm)->mem, (*proc)->pc + (*(param[0]->ind)) % IDX_MOD, 4);
		else
			addr = read_value((*vm)->mem, (*proc)->pc - ((*(param[0]->ind)) * -1) % IDX_MOD, 4);
	}
	else
		addr = param[0]->reg->value % IDX_MOD;
	if (param[1]->dir != NULL)
		addr += (*(param[1]->dir)) % IDX_MOD;
	else if (param[1]->ind != NULL)
	{
		if (*(param[1]->ind) >= 0)
			addr += read_value((*vm)->mem, (*proc)->pc + (*(param[1]->ind)) % IDX_MOD, 4);
		else
			addr += read_value((*vm)->mem, (*proc)->pc - ((*(param[1]->ind)) * -1) % IDX_MOD, 4);
	}
	else
		addr += param[0]->reg->value % IDX_MOD;
	if (addr >= 0)
		addr %= IDX_MOD;
	else
		addr = -((addr * -1) % IDX_MOD);
	param[2]->reg->value = read_value((*vm)->mem, (*proc)->pc + addr, REG_SIZE);
	return (25);
}

int		ft_sti(t_vm **vm, t_param **param, t_proc **exec_proc, t_proc **proc)
{
	int addr;

	if (param[1]->dir != NULL)
		addr = (*(param[1]->dir)) % IDX_MOD;
	else if (param[1]->ind != NULL)
	{
		if (*(param[1]->ind) >= 0)
			addr = read_value((*vm)->mem, (*proc)->pc + (*(param[1]->ind)) % IDX_MOD, 4);
		else
			addr = read_value((*vm)->mem, (*proc)->pc - ((*(param[1]->ind)) * -1) % IDX_MOD, 4);
	}
	else
		addr = param[2]->reg->value % IDX_MOD;
	if (param[2]->dir != NULL)
		addr += (*(param[2]->dir)) % IDX_MOD;
	else
		addr += param[2]->reg->value % IDX_MOD;
	write_value(&((*vm)->mem), param[0]->reg->value, addr, (*proc)->champ);
	return (25);
}

int		ft_fork(t_vm **vm, t_param **param, t_proc **exec_proc, t_proc **proc)
{
	return (1000);
}

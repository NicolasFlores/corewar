/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_function_1_4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 11:40:04 by nflores           #+#    #+#             */
/*   Updated: 2016/05/25 16:47:42 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/vm.h"

int		ft_live(t_vm **vm, t_param **param, t_proc **exec_proc, t_proc **proc)
{
	int i;

	(*proc)->live = (*proc)->pc + 10;
	(*vm)->live++;
	i = 0;
	while (i < (*vm)->proc)
	{
		if (*(param[0]->dir) == (exec_proc[i]->champ->num) * -1)
			(*vm)->last_live = *(param[0]->dir);
		i++;
	}
	return (10);
}

int		ft_ld(t_vm **vm, t_param **param, t_proc **exec_proc, t_proc **proc)
{
	if (param[0]->dir != NULL)
		param[1]->reg->value = *(param[0]->dir);
	else if (*(param[0]->ind) >= 0)
		param[1]->reg->value =
			read_value((*vm)->mem,
					(*proc)->pc + (*(param[0]->ind)) % IDX_MOD, REG_SIZE);
	else
		param[1]->reg->value =
			read_value((*vm)->mem,
					(*proc)->pc - (*(param[0]->ind) * -1) % IDX_MOD, REG_SIZE);
	return (5);
}

int		ft_st(t_vm **vm, t_param **param, t_proc **exec_proc, t_proc **proc)
{
	int addr;

	addr = 0;
	if (param[1]->reg != NULL)
		param[1]->reg->value = param[0]->reg->value;
	else if (*(param[1]->ind) >= 0)
		addr = (*proc)->pc + (*(param[1]->ind)) % IDX_MOD;
	else
		addr = (*proc)->pc - ((*(param[1]->ind)) * -1) % IDX_MOD;
	write_value(&((*vm)->mem), param[0]->reg->value, addr, (*proc)->champ);
	return (5);
}

int		ft_add(t_vm **vm, t_param **param, t_proc **exec_proc, t_proc **proc)
{
	param[2]->reg->value = param[0]->reg->value + param[1]->reg->value;
	if ((*proc)->champ->carry)
		(*proc)->champ->carry = 0;
	else
		(*proc)->champ->carry = 1;
	return (10);
}

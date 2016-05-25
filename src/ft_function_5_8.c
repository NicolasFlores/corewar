/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_function_5_8.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 14:09:42 by nflores           #+#    #+#             */
/*   Updated: 2016/05/25 16:46:59 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/vm.h"

int		ft_sub(t_vm **vm, t_param **param, t_proc **exec_proc, t_proc **proc)
{
	param[2]->reg->value = param[0]->reg->value - param[1]->reg->value;
	if ((*proc)->champ->carry)
		(*proc)->champ->carry = 0;
	else
		(*proc)->champ->carry = 1;
	return (10);
}

int		ft_and(t_vm **vm, t_param **param, t_proc **exec_proc, t_proc **proc)
{
	int val1;
	int val2;

	if (param[0]->reg != NULL)
		val1 = param[0]->reg->value;
	else if ((param[0]->dir) != NULL)
		val1 = *(param[0]->dir);
	else
	{
		if (*(param[0]->ind) >= 0)
			val1 = read_value((*vm)->mem, (*proc)->pc + (*(param[0]->ind)) % IDX_MOD, REG_SIZE);
		else
			val1 = read_value((*vm)->mem, (*proc)->pc - ((*(param[0]->ind)) * -1) % IDX_MOD, REG_SIZE);
	}
	if (param[1]->reg != NULL)
		val2 = param[1]->reg->value;
	else if ((param[1]->dir) != NULL)
		val2 = *(param[1]->dir);
	else
	{
		if (*(param[1]->ind) >= 0)
			val2 = read_value((*vm)->mem, (*proc)->pc + (*(param[1]->ind)) % IDX_MOD, REG_SIZE);
		else
			val2 = read_value((*vm)->mem, (*proc)->pc - ((*(param[1]->ind)) * -1) % IDX_MOD, REG_SIZE);
	}
	param[2]->reg->value = val1 & val2;
	if ((*proc)->champ->carry)
		(*proc)->champ->carry = 0;
	else
		(*proc)->champ->carry = 1;
	return (6);
}

int		ft_or(t_vm **vm, t_param **param, t_proc **exec_proc, t_proc **proc)
{
	int val1;
	int val2;

	if (param[0]->reg != NULL)
		val1 = param[0]->reg->value;
	else if ((param[0]->dir) != NULL)
		val1 = *(param[0]->dir);
	else
	{
		if (*(param[0]->ind) >= 0)
			val1 = read_value((*vm)->mem, (*proc)->pc + (*(param[0]->ind)) % IDX_MOD, REG_SIZE);
		else
			val1 = read_value((*vm)->mem, (*proc)->pc - ((*(param[0]->ind)) * -1) % IDX_MOD, REG_SIZE);
	}
	if (param[1]->reg != NULL)
		val2 = param[1]->reg->value;
	else if ((param[1]->dir) != NULL)
		val2 = *(param[1]->dir);
	else
	{
		if (*(param[1]->ind) >= 0)
			val2 = read_value((*vm)->mem, (*proc)->pc + (*(param[1]->ind)) % IDX_MOD, REG_SIZE);
		else
			val2 = read_value((*vm)->mem, (*proc)->pc + ((*(param[1]->ind)) * -1) % IDX_MOD, REG_SIZE);
	}
	param[2]->reg->value = val1 | val2;
	if ((*proc)->champ->carry)
		(*proc)->champ->carry = 0;
	else
		(*proc)->champ->carry = 1;
	return (6);
}

int		ft_xor(t_vm **vm, t_param **param, t_proc **exec_proc, t_proc **proc)
{
	int val1;
	int val2;

	if (param[0]->reg != NULL)
		val1 = param[0]->reg->value;
	else if ((param[0]->dir) != NULL)
		val1 = *(param[0]->dir);
	else
	{
		if (*(param[0]->ind) >= 0)
			val1 = read_value((*vm)->mem, (*proc)->pc + (*(param[0]->ind)) % IDX_MOD, REG_SIZE);
		else
			val1 = read_value((*vm)->mem, (*proc)->pc - ((*(param[0]->ind)) * -1) % IDX_MOD, REG_SIZE);
	}
	if (param[1]->reg != NULL)
		val2 = param[1]->reg->value;
	else if ((param[1]->dir) != NULL)
		val2 = *(param[1]->dir);
	else
	{
		if (*(param[1]->ind) >= 0)
			val2 = read_value((*vm)->mem, (*proc)->pc + (*(param[1]->ind)) % IDX_MOD, REG_SIZE);
		else
			val2 = read_value((*vm)->mem, (*proc)->pc - ((*(param[1]->ind)) * -1) % IDX_MOD, REG_SIZE);
	}
	param[2]->reg->value = val1 ^ val2;
	if ((*proc)->champ->carry)
		(*proc)->champ->carry = 0;
	else
		(*proc)->champ->carry = 1;
	return (6);
}

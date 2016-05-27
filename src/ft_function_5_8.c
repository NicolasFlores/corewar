/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_function_5_8.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 14:09:42 by nflores           #+#    #+#             */
/*   Updated: 2016/05/27 12:57:51 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/vm.h"

int		ft_sub(t_vm **vm, t_param_list *lst, int codage, t_proc **proc)
{
	if (param_type(read_value((*vm)->mem, codage, 1), 0, 5) == REG)
		lst->next->next->param->reg->value = lst->param->reg->value - lst->next->param->reg->value;
	if ((*proc)->champ->carry)
		(*proc)->champ->carry = 0;
	else
		(*proc)->champ->carry = 1;
	return (10);
}

int		ft_and(t_vm **vm, t_param_list *lst, int codage, t_proc **proc)
{
	int val1;
	int val2;

	if (param_type(read_value((*vm)->mem, codage, 1), 0, 6) == REG)
		val1 = lst->param->reg->value;
	else if (param_type(read_value((*vm)->mem, codage, 1), 0, 6) == DIR)
		val1 = lst->param->dir;
	else
	{
		if (lst->param->ind >= 0)
			val1 = read_value((*vm)->mem, (*proc)->pc + lst->param->ind % IDX_MOD, REG_SIZE);
		else
			val1 = read_value((*vm)->mem, (*proc)->pc - (lst->param->ind * -1) % IDX_MOD, REG_SIZE);
	}
	if (param_type(read_value((*vm)->mem, codage, 1), 1, 6) == REG)
		val2 = lst->next->param->reg->value;
	else if (param_type(read_value((*vm)->mem, codage, 1), 1, 6) == DIR)
		val2 = lst->next->param->dir;
	else
	{
		if (lst->next->param->ind >= 0)
			val2 = read_value((*vm)->mem, (*proc)->pc + lst->next->param->ind % IDX_MOD, REG_SIZE);
		else
			val2 = read_value((*vm)->mem, (*proc)->pc - (lst->next->param->ind * -1) % IDX_MOD, REG_SIZE);
	}
	lst->next->next->param->reg->value = val1 & val2;
	if ((*proc)->champ->carry)
		(*proc)->champ->carry = 0;
	else
		(*proc)->champ->carry = 1;
	return (6);
}

int		ft_or(t_vm **vm, t_param_list *lst, int codage, t_proc **proc)
{
	int val1;
	int val2;

	if (param_type(read_value((*vm)->mem, codage, 1), 0, 7) == REG)
		val1 = lst->param->reg->value;
	else if (param_type(read_value((*vm)->mem, codage, 1), 0, 7) == DIR)
		val1 = lst->param->dir;
	else
	{
		if (lst->param->ind >= 0)
			val1 = read_value((*vm)->mem, (*proc)->pc + lst->param->ind % IDX_MOD, REG_SIZE);
		else
			val1 = read_value((*vm)->mem, (*proc)->pc - (lst->param->ind * -1) % IDX_MOD, REG_SIZE);
	}
	if (param_type(read_value((*vm)->mem, codage, 1), 1, 7) == REG)
		val2 = lst->next->param->reg->value;
	else if (param_type(read_value((*vm)->mem, codage, 1), 1, 7) == DIR)
		val2 = lst->next->param->dir;
	else
	{
		if (lst->next->param->ind >= 0)
			val2 = read_value((*vm)->mem, (*proc)->pc + lst->next->param->ind % IDX_MOD, REG_SIZE);
		else
			val2 = read_value((*vm)->mem, (*proc)->pc + (lst->next->param->ind * -1) % IDX_MOD, REG_SIZE);
	}
	lst->next->next->param->reg->value = val1 | val2;
	if ((*proc)->champ->carry)
		(*proc)->champ->carry = 0;
	else
		(*proc)->champ->carry = 1;
	return (6);
}

int		ft_xor(t_vm **vm, t_param_list *lst, int codage, t_proc **proc)
{
	int val1;
	int val2;

	if (param_type(read_value((*vm)->mem, codage, 1), 0, 8) == REG)
		val1 = lst->param->reg->value;
	else if (param_type(read_value((*vm)->mem, codage, 1), 0, 8) == DIR)
		val1 = lst->param->dir;
	else
	{
		if (lst->param->ind >= 0)
			val1 = read_value((*vm)->mem, (*proc)->pc + lst->param->ind % IDX_MOD, REG_SIZE);
		else
			val1 = read_value((*vm)->mem, (*proc)->pc - (lst->param->ind * -1) % IDX_MOD, REG_SIZE);
	}
	if (param_type(read_value((*vm)->mem, codage, 1), 1, 8) == REG)
		val2 = lst->next->param->reg->value;
	else if (param_type(read_value((*vm)->mem, codage, 1), 1, 8) == DIR)
		val2 = lst->next->param->dir;
	else
	{
		if (lst->next->param->ind >= 0)
			val2 = read_value((*vm)->mem, (*proc)->pc + lst->next->param->ind % IDX_MOD, REG_SIZE);
		else
			val2 = read_value((*vm)->mem, (*proc)->pc - (lst->next->param->ind * -1) % IDX_MOD, REG_SIZE);
	}
	lst->next->next->param->reg->value = val1 ^ val2;
	if ((*proc)->champ->carry)
		(*proc)->champ->carry = 0;
	else
		(*proc)->champ->carry = 1;
	return (6);
}

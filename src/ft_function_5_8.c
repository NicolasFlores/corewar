/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_function_5_8.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 14:09:42 by nflores           #+#    #+#             */
/*   Updated: 2016/05/30 12:41:25 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/vm.h"

void	*ft_sub(t_vm **vm, t_param_list *lst, t_proc **proc)
{
	if (!(*vm))
		return (NULL);
	if (param_type((*proc)->codage, 0, 5) == REG)
		*(lst->next->next->param->reg) = *(lst->param->reg) -
										*(lst->next->param->reg);
	if (*(lst->next->next->param->reg) == 0)
		(*proc)->carry = 1;
	else
		(*proc)->carry = 0;
	return (NULL);
}

int		init_indvalue(t_vm **vm, int ind, int addr)
{
	int ret;

	if (ind >= 0)
		ret = read_value((*vm)->mem, addr + ind % IDX_MOD + 1, REG_SIZE);
	else
		ret = read_value((*vm)->mem, addr - ind % IDX_MOD - 1, REG_SIZE);
	return (ret);
}

void	*ft_and(t_vm **vm, t_param_list *lst, t_proc **proc)
{
	int val1;
	int val2;
	int addr;

	addr = (*proc)->pc - 2 - param_size(param_type((*proc)->codage, 0, 8)) -
			param_size(param_type((*proc)->codage, 1, 8)) -
			param_size(param_type((*proc)->codage, 2, 8));
	if (param_type((*proc)->codage, 0, 6) == REG)
		val1 = *(lst->param->reg);
	else if (param_type((*proc)->codage, 0, 6) == DIR)
		val1 = lst->param->dir;
	else
		val1 = init_indvalue(vm, lst->param->ind, addr);
	if (param_type((*proc)->codage, 1, 6) == REG)
		val2 = *(lst->next->param->reg);
	else if (param_type((*proc)->codage, 1, 6) == DIR)
		val2 = lst->next->param->dir;
	else
		val2 = init_indvalue(vm, lst->next->param->ind, addr);
	*(lst->next->next->param->reg) = val1 & val2;
	ft_carry(val1 & val2, proc);
	return (NULL);
}

void	*ft_or(t_vm **vm, t_param_list *lst, t_proc **proc)
{
	int val1;
	int val2;
	int addr;

	addr = (*proc)->pc - 2 - param_size(param_type((*proc)->codage, 0, 8)) -
			param_size(param_type((*proc)->codage, 1, 8)) -
			param_size(param_type((*proc)->codage, 2, 8));
	if (param_type((*proc)->codage, 0, 7) == REG)
		val1 = *(lst->param->reg);
	else if (param_type((*proc)->codage, 0, 7) == DIR)
		val1 = lst->param->dir;
	else
		val1 = init_indvalue(vm, lst->param->ind, addr);
	if (param_type((*proc)->codage, 1, 7) == REG)
		val2 = *(lst->next->param->reg);
	else if (param_type((*proc)->codage, 1, 7) == DIR)
		val2 = lst->next->param->dir;
	else
		val2 = init_indvalue(vm, lst->next->param->ind, addr);
	*(lst->next->next->param->reg) = val1 | val2;
	ft_carry(val1 | val2, proc);
	return (NULL);
}

void	*ft_xor(t_vm **vm, t_param_list *lst, t_proc **proc)
{
	int val1;
	int val2;
	int addr;

	addr = (*proc)->pc - 2 - param_size(param_type((*proc)->codage, 0, 8)) -
			param_size(param_type((*proc)->codage, 1, 8)) -
			param_size(param_type((*proc)->codage, 2, 8));
	if (param_type((*proc)->codage, 0, 8) == REG)
		val1 = *(lst->param->reg);
	else if (param_type((*proc)->codage, 0, 8) == DIR)
		val1 = lst->param->dir;
	else
		val1 = init_indvalue(vm, lst->param->ind, addr);
	if (param_type((*proc)->codage, 1, 8) == REG)
		val2 = *(lst->next->param->reg);
	else if (param_type((*proc)->codage, 1, 8) == DIR)
		val2 = lst->next->param->dir;
	else
		val2 = init_indvalue(vm, lst->next->param->ind, addr);
	*(lst->next->next->param->reg) = val1 ^ val2;
	ft_carry(val1 ^ val2, proc);
	return (NULL);
}

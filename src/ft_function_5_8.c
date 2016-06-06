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

void	*ft_and(t_vm **vm, t_param_list *lst, t_proc **proc)
{
	int val1;
	int val2;
	int size1;
	int size2;
	int size3;

	size1 = param_size(param_type((*proc)->codage, 0, 6));
	size2 = param_size(param_type((*proc)->codage, 1, 6));
	size3 = param_size(param_type((*proc)->codage, 2, 6));
	if (param_type((*proc)->codage, 0, 6) == REG)
		val1 = *(lst->param->reg);
	else if (param_type((*proc)->codage, 0, 6) == DIR)
		val1 = lst->param->dir;
	else
	{
		if (lst->param->ind >= 0)
			val1 = read_value((*vm)->mem,
								(*proc)->pc - 2 - size1 - size2 - size3 +
								lst->param->ind % IDX_MOD, REG_SIZE);
		else
			val1 = read_value((*vm)->mem,
								(*proc)->pc - 2 - size1 - size2 - size3 -
								(lst->param->ind * -1) % IDX_MOD, REG_SIZE);
	}
	if (param_type((*proc)->codage, 1, 6) == REG)
		val2 = *(lst->next->param->reg);
	else if (param_type((*proc)->codage, 1, 6) == DIR)
		val2 = lst->next->param->dir;
	else
	{
		if (lst->next->param->ind >= 0)
			val2 = read_value((*vm)->mem,
								(*proc)->pc - 2 - size1 - size2 - size3 +
								lst->next->param->ind % IDX_MOD, REG_SIZE);
		else
			val2 = read_value((*vm)->mem,
								(*proc)->pc - 2 - size1 - size2 - size3 -
								(lst->next->param->ind * -1) %
								IDX_MOD, REG_SIZE);
	}
	*(lst->next->next->param->reg) = val1 & val2;
	if ((val1 & val2) == 0)
		(*proc)->carry = 1;
	else
		(*proc)->carry = 0;
	return (NULL);
}

void	*ft_or(t_vm **vm, t_param_list *lst, t_proc **proc)
{
	int val1;
	int val2;
	int size1;
	int size2;
	int size3;

	size1 = param_size(param_type((*proc)->codage, 0, 7));
	size2 = param_size(param_type((*proc)->codage, 1, 7));
	size3 = param_size(param_type((*proc)->codage, 2, 7));
	if (param_type((*proc)->codage, 0, 7) == REG)
		val1 = *(lst->param->reg);
	else if (param_type((*proc)->codage, 0, 7) == DIR)
		val1 = lst->param->dir;
	else
	{
		if (lst->param->ind >= 0)
			val1 = read_value((*vm)->mem,
								(*proc)->pc - 2 - size1 - size2 - size3 +
								lst->param->ind % IDX_MOD, REG_SIZE);
		else
			val1 = read_value((*vm)->mem,
								(*proc)->pc - 2 - size1 - size2 - size3 -
								(lst->param->ind * -1) % IDX_MOD, REG_SIZE);
	}
	if (param_type((*proc)->codage, 1, 7) == REG)
		val2 = *(lst->next->param->reg);
	else if (param_type((*proc)->codage, 1, 7) == DIR)
		val2 = lst->next->param->dir;
	else
	{
		if (lst->next->param->ind >= 0)
			val2 = read_value((*vm)->mem,
								(*proc)->pc - 2 - size1 - size2 - size3 +
								lst->next->param->ind % IDX_MOD, REG_SIZE);
		else
			val2 = read_value((*vm)->mem,
								(*proc)->pc - 2 - size1 - size2 - size3 -
								(lst->next->param->ind * -1) %
								IDX_MOD, REG_SIZE);
	}
	*(lst->next->next->param->reg) = val1 | val2;
	if ((val1 | val2) == 0)
		(*proc)->carry = 1;
	else
		(*proc)->carry = 0;
	return (NULL);
}

void	*ft_xor(t_vm **vm, t_param_list *lst, t_proc **proc)
{
	int val1;
	int val2;
	int size1;
	int size2;
	int size3;

	size1 = param_size(param_type((*proc)->codage, 0, 8));
	size2 = param_size(param_type((*proc)->codage, 1, 8));
	size3 = param_size(param_type((*proc)->codage, 2, 8));
	if (param_type((*proc)->codage, 0, 8) == REG)
		val1 = *(lst->param->reg);
	else if (param_type((*proc)->codage, 0, 8) == DIR)
		val1 = lst->param->dir;
	else
	{
		if (lst->param->ind >= 0)
			val1 = read_value((*vm)->mem,
								(*proc)->pc - 2 - size1 - size2 - size3 +
								lst->param->ind % IDX_MOD, REG_SIZE);
		else
			val1 = read_value((*vm)->mem,
								(*proc)->pc - 2 - size1 - size2 - size3 -
								(lst->param->ind * -1) % IDX_MOD, REG_SIZE);
	}
	if (param_type((*proc)->codage, 1, 8) == REG)
		val2 = *(lst->next->param->reg);
	else if (param_type((*proc)->codage, 1, 8) == DIR)
		val2 = lst->next->param->dir;
	else
	{
		if (lst->next->param->ind >= 0)
			val2 = read_value((*vm)->mem,
								(*proc)->pc - 2 - size1 - size2 - size3 +
								lst->next->param->ind % IDX_MOD, REG_SIZE);
		else
			val2 = read_value((*vm)->mem,
								(*proc)->pc - 2 - size1 - size2 - size3 -
								(lst->next->param->ind * -1) %
								IDX_MOD, REG_SIZE);
	}
	*(lst->next->next->param->reg) = val1 ^ val2;
	if ((val1 ^ val2) == 0)
		(*proc)->carry = 1;
	else
		(*proc)->carry = 0;
	return (NULL);
}

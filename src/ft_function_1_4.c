/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_function_1_4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 11:40:04 by nflores           #+#    #+#             */
/*   Updated: 2016/05/30 16:45:13 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/vm.h"

void	*ft_live(t_vm **vm, t_param_list *lst, int codage, t_proc **proc)
{
	t_champ_list	*tmp;

	(*proc)->live = (*proc)->pc + 10;
	(*vm)->live++;
	tmp = (*vm)->champ_list;
	while (tmp)
	{
		if (lst->param->dir == (tmp->champ->num) * -1)
			(*vm)->last_live = lst->param->dir;
		tmp = tmp->next;
	}
	return (NULL);
}

void	*ft_ld(t_vm **vm, t_param_list *lst, int codage, t_proc **proc)
{
	int val;

	val = 0;
	if (param_type(codage, 0, 2) == DIR)
	{
		val = lst->param->dir;
		*(lst->next->param->reg) = val;
	}
	else if (lst->param->ind >= 0)
	{
		val = (*proc)->pc - 1 - IND_SIZE - T_REG + lst->param->ind;
		*(lst->next->param->reg) = read_value((*vm)->mem,
										(*proc)->pc + val % IDX_MOD, REG_SIZE);
	}
	else
	{
		val = (*proc)->pc - 1 - IND_SIZE - T_REG - lst->param->ind;
		*(lst->next->param->reg) = read_value((*vm)->mem,
										(*proc)->pc - val % IDX_MOD, REG_SIZE);
	}
	(*proc)->carry = 1;
	return (NULL);
}

void	*ft_st(t_vm **vm, t_param_list *lst, int codage, t_proc **proc)
{
	int addr;
	int val;

	val = *(lst->param->reg);
	addr = 0;
	if (param_type(codage, 1, 3) == REG)
		*(lst->next->param->reg) = *(lst->param->reg);
	else if (lst->next->param->ind >= 0)
	{
		addr = (*proc)->pc - 1 - IND_SIZE - T_REG +
				lst->next->param->ind % IDX_MOD;
		write_value(&((*vm)->mem), val, addr, (*proc)->champ);
	}
	else
	{
		addr = (*proc)->pc - 1 - IND_SIZE - T_REG -
				(lst->next->param->ind * -1) % IDX_MOD;
		write_value(&((*vm)->mem), *(lst->param->reg), addr, (*proc)->champ);
	}
	return (NULL);
}

void	*ft_add(t_vm **vm, t_param_list *lst, int codage, t_proc **proc)
{
	int val;

	if (param_type(codage, 0, 4) == REG)
		val = *(lst->param->reg) + *(lst->next->param->reg);
	*(lst->next->next->param->reg) = val;
	(*proc)->carry = 1;
	return (NULL);
}

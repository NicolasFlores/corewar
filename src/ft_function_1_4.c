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

int		ft_live(t_vm **vm, t_param_list *lst, int codage, t_proc **proc)
{
	t_champ_list	*tmp;

//	ft_putendl("---live---");
	(*proc)->live = (*proc)->pc + 10;
	(*vm)->live++;
	tmp = (*vm)->champ_list;
	while (tmp)
	{
		if (lst->param->dir == (tmp->champ->num) * -1)
			(*vm)->last_live = lst->param->dir;
		tmp = tmp->next;
	}
//	ft_putendl("---fin live---");
	return (10);
}

int		ft_ld(t_vm **vm, t_param_list *lst, int codage, t_proc **proc)
{
	int val;

//	ft_putendl("---ld---");
	val = 0;
	if (param_type(read_value((*vm)->mem, codage, 1), 0, 2) == DIR)
	{
		val = lst->param->dir;
		*(lst->next->param->reg) = val;
	}
	else if (lst->param->ind >= 0)
	{
		val = lst->param->ind;
		*(lst->next->param->reg) = read_value((*vm)->mem,
										(*proc)->pc + val % IDX_MOD, REG_SIZE);
	}
	else
	{
		val = lst->param->ind;
		*(lst->next->param->reg) = read_value((*vm)->mem,
										(*proc)->pc - val % IDX_MOD, REG_SIZE);
	}
//	ft_printf("dir = %d regval = %d\n", lst->param->dir, lst->next->param->reg->value); 
//	ft_putendl("---fin ld---");
	return (5);
}

int		ft_st(t_vm **vm, t_param_list *lst, int codage, t_proc **proc)
{
	int addr;
	int val;

//	ft_putendl("---st---");
	val = *(lst->param->reg);
//	printf("ind = %d regval = %d\n", lst->next->param->ind, val);
	addr = 0;
	if (param_type(read_value((*vm)->mem, codage, 1), 1, 3) == REG)
		*(lst->next->param->reg) = *(lst->param->reg);
	else if (lst->next->param->ind >= 0)
	{
//		printf("stregval = %d\n", *(lst->param->reg)/*val*/);
		addr = (*proc)->pc - 1 - IND_SIZE - T_REG + lst->next->param->ind % IDX_MOD;
//		printf("stregval = %d\n", *(lst->param->reg)/*val*/);
		write_value(&((*vm)->mem), val, addr, (*proc)->champ);
	}
	else
	{
		addr = (*proc)->pc - 1 - IND_SIZE - T_REG - (lst->next->param->ind * -1) % IDX_MOD;
		write_value(&((*vm)->mem), *(lst->param->reg), addr, (*proc)->champ);
	}
//	ft_printf("ind = %d regval = %d\n", lst->next->param->ind, *(lst->param->reg));
//	ft_putendl("---fin st---");
	return (5);
}

int		ft_add(t_vm **vm, t_param_list *lst, int codage, t_proc **proc)
{
	int val;

	
	if (param_type(read_value((*vm)->mem, codage, 1), 0, 4) == REG)
		val = *(lst->param->reg) + *(lst->next->param->reg);
	*(lst->next->next->param->reg) = val;
	if ((*proc)->champ->carry)
		(*proc)->champ->carry = 0;
	else
		(*proc)->champ->carry = 1;
	return (10);
}

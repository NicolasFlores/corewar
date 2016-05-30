/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_function_9_12.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 15:56:38 by nflores           #+#    #+#             */
/*   Updated: 2016/05/30 16:23:36 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/vm.h"

int		ft_zjmp(t_vm **vm, t_param_list *lst, int codage, t_proc **proc)
{
	if (lst->param->dir >= 0)
		(*proc)->pc += lst->param->dir % IDX_MOD;
	else
		(*proc)->pc -= (lst->param->dir * -1) % IDX_MOD;
	if ((*proc)->champ->carry)
		(*proc)->champ->carry = 0;
	else
		(*proc)->champ->carry = 1;
	return (20);
}

int		ft_ldi(t_vm **vm, t_param_list *lst, int codage, t_proc **proc)
{
	int addr;

	if (param_type(read_value((*vm)->mem, codage, 1), 0, 10) == DIRI)
		addr = lst->param->dir % IDX_MOD;
	else if (param_type(read_value((*vm)->mem, codage, 1), 0, 10) == IND)
	{
		if (lst->param->ind >= 0)
			addr = read_value((*vm)->mem, (*proc)->pc + lst->param->ind % IDX_MOD, 4);
		else
			addr = read_value((*vm)->mem, (*proc)->pc - (lst->param->ind * -1) % IDX_MOD, 4);
	}
	else
		addr = *(lst->param->reg) % IDX_MOD;
	if (param_type(read_value((*vm)->mem, codage, 1), 1, 10) == DIRI)
		addr += lst->next->param->dir % IDX_MOD;
	else if (param_type(read_value((*vm)->mem, codage, 1), 1, 10) == IND)
	{
		if (lst->next->param->ind >= 0)
			addr += read_value((*vm)->mem, (*proc)->pc + lst->next->param->ind % IDX_MOD, 4);
		else
			addr += read_value((*vm)->mem, (*proc)->pc - (lst->next->param->ind * -1) % IDX_MOD, 4);
	}
	else
		addr += *(lst->param->reg) % IDX_MOD;
	if (addr >= 0)
		addr %= IDX_MOD;
	else
		addr = -((addr * -1) % IDX_MOD);
	*(lst->next->next->param->reg) = read_value((*vm)->mem, (*proc)->pc + addr, REG_SIZE);
	return (25);
}

int		ft_sti(t_vm **vm, t_param_list *lst, int codage, t_proc **proc)
{
	int addr;

//	ft_putendl("---sti---");
//	ft_print_mem((*vm)->mem);
//	ft_printf("write %d\n", *(lst->param->reg));
	if (param_type(read_value((*vm)->mem, codage, 1), 1, 11) == DIRI)
		addr = lst->next->param->dir % IDX_MOD;
	else if (param_type(read_value((*vm)->mem, codage, 1), 1, 11) == IND)
	{
		if (lst->next->param->ind >= 0)
			addr = read_value((*vm)->mem, (*proc)->pc + lst->next->param->ind % IDX_MOD, 4);
		else
			addr = read_value((*vm)->mem, (*proc)->pc - (lst->next->param->ind * -1) % IDX_MOD, 4);
	}
	else
		addr = *(lst->next->param->reg) % IDX_MOD;
	if (param_type(read_value((*vm)->mem, codage, 1), 2, 11) == DIRI)
		addr += lst->next->next->param->dir % IDX_MOD;
	else
		addr += *(lst->next->next->param->reg) % IDX_MOD;
//	ft_printf("write %d\n", *(lst->param->reg));
	write_value(&((*vm)->mem), *(lst->param->reg), addr, (*proc)->champ);
//	ft_putendl("---fin sti---");
//	ft_print_mem((*vm)->mem);
	return (25);
}

int		ft_fork(t_vm **vm, t_param_list *lst, int codage, t_proc **proc)
{
	return (1000);
}

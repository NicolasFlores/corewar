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

void	*ft_zjmp(t_vm **vm, t_param_list *lst, int codage, t_proc **proc)
{
	if ((*proc)->carry == 1)
	{
		if (lst->param->dir >= 0)
			(*proc)->pc = (*proc)->pc - T_DIR + lst->param->diri % IDX_MOD;
		else
			(*proc)->pc = (*proc)->pc - T_DIR -
							(lst->param->diri * -1) % IDX_MOD;
		(*proc)->carry = 0;
	}
	else
		(*proc)->carry = 1;
	return (NULL);
}

void	*ft_ldi(t_vm **vm, t_param_list *lst, int codage, t_proc **proc)
{
	int addr;
	int size1;
	int size2;

	size1 = param_size(param_type(codage, 0, 10));
	size2 = param_size(param_type(codage, 1, 10));
	if (param_type(codage, 0, 10) == DIRI)
	{
		if (lst->next->next->param->diri >= 0)
			addr = (*proc)->pc - 1 - size1 - size2 - T_REG +
					lst->param->diri % IDX_MOD;
		else
			addr = (*proc)->pc - 1 - size1 - size2 - T_REG +
					(lst->param->diri * -1) % IDX_MOD;
	}
	else if (param_type(codage, 0, 10) == IND)
	{
		if (lst->param->ind >= 0)
			addr = read_value((*vm)->mem,
								(*proc)->pc - 1 - size1 - size2 - T_REG +
								lst->param->ind % IDX_MOD, 4);
		else
			addr = read_value((*vm)->mem,
								(*proc)->pc - 1 - size1 - size2 - T_REG -
								(lst->param->ind * -1) % IDX_MOD, 4);
	}
	else
	{
		if (*(lst->param->reg) >= 0)
			addr = (*proc)->pc - 1 - size1 - size2 - T_REG +
					*(lst->param->reg) % IDX_MOD;
		else
			addr = (*proc)->pc - 1 - size1 - size2 - T_REG +
					(*(lst->param->reg) * -1) % IDX_MOD;
	}
	if (param_type(codage, 1, 10) == DIRI)
	{
		if (lst->next->next->param->diri >= 0)
			addr += (*proc)->pc - 1 - size1 - size2 - T_REG +
					lst->next->param->diri % IDX_MOD;
		else
			addr += (*proc)->pc - 1 - size1 - size2 - T_REG +
					(lst->next->param->diri * -1) % IDX_MOD;
	}
	else if (param_type(codage, 1, 10) == IND)
	{
		if (lst->next->param->ind >= 0)
			addr += read_value((*vm)->mem,
								(*proc)->pc - 1 - size1 - size2 - T_REG +
								lst->next->param->ind % IDX_MOD, 4);
		else
			addr += read_value((*vm)->mem,
								(*proc)->pc - 1 - size1 - size2 - T_REG -
								(lst->next->param->ind * -1) % IDX_MOD, 4);
	}
	else
	{
		if (*(lst->next->param->reg) >= 0)
			addr += (*proc)->pc - 1 - size1 - size2 - T_REG +
					*(lst->next->param->reg) % IDX_MOD;
		else
			addr += (*proc)->pc -1 - size1 - size2 - T_REG +
					(*(lst->next->param->reg) * -1) % IDX_MOD;
	}
	if (addr >= 0)
		addr %= IDX_MOD;
	else
		addr = -((addr * -1) % IDX_MOD);
	*(lst->next->next->param->reg) = read_value((*vm)->mem,
												(*proc)->pc + addr, REG_SIZE);
	return (NULL);
}

void	*ft_sti(t_vm **vm, t_param_list *lst, int codage, t_proc **proc)
{
	int addr;
	int size1;
	int size2;

	size1 = param_size(param_type(codage, 1, 11));
	size2 = param_size(param_type(codage, 2, 11));
	if (param_type(codage, 1, 11) == DIRI)
	{
		if (lst->next->param->diri >= 0)
			addr = (*proc)->pc - 1 - size1 - size2 - T_REG +
					lst->next->param->diri % IDX_MOD;
		else
			addr = (*proc)->pc - 1 - size1 - size2 - T_REG +
					(lst->next->param->diri * -1) % IDX_MOD;
	}
	else if (param_type(codage, 1, 11) == IND)
	{
		if (lst->next->param->ind >= 0)
			addr = read_value((*vm)->mem,
								(*proc)->pc - 1 - size1 - size2 - T_REG +
								lst->next->param->ind % IDX_MOD, 4);
		else
			addr = read_value((*vm)->mem,
								(*proc)->pc - 1 - size1 - size2 - T_REG -
								(lst->next->param->ind * -1) % IDX_MOD, 4);
	}
	else
	{
		if (*(lst->next->param->reg) >= 0)
			addr = (*proc)->pc - 1 - size1 - size2 - T_REG +
					*(lst->next->param->reg) % IDX_MOD;
		else
			addr = (*proc)->pc - 1 - size1 - size2 - T_REG -
					(*(lst->next->param->reg) * -1) % IDX_MOD;
	}
	if (param_type(codage, 2, 11) == DIRI)
	{
		if (lst->next->next->param->diri >= 0)
			addr += (*proc)->pc - 1 - size1 - size2 - T_REG +
					lst->next->next->param->diri % IDX_MOD;
		else
			addr += (*proc)->pc - 1 - size1 - size2 - T_REG +
					(lst->next->next->param->diri * -1) % IDX_MOD;
	}
	else
	{
		if (*(lst->next->next->param->reg) >= 0)
			addr += (*proc)->pc - 1 - size1 - size2 - T_REG +
					*(lst->next->next->param->reg) % IDX_MOD;
		else
			addr += (*proc)->pc - 1 - size1 - size2 - T_REG -
					(*(lst->next->next->param->reg) * -1) % IDX_MOD;
	}
	if (addr >= 0)
		addr %= IDX_MOD;
	else
		addr = ((addr * -1) % IDX_MOD) * -1;
	write_value(&((*vm)->mem), *(lst->param->reg), addr, (*proc)->champ);
	return (NULL);
}

void	*ft_fork(t_vm **vm, t_param_list *lst, int codage, t_proc **proc)
{
	t_proc	*fork;
	int		i;

	fork = init_proc((*proc)->champ, (*vm)->proc);
	if (lst->param->diri >= 0)
		fork->pc = (*proc)->pc - T_DIR + lst->param->diri % IDX_MOD;
	else
		fork->pc = (*proc)->pc - T_DIR - (lst->param->diri * -1) % IDX_MOD;
	fork->carry = (*proc)->carry;
	fork->live = (*proc)->live;
	i = 0;
	while (i < REG_NUMBER)
	{
		fork->reg[i] = (*proc)->reg[i];
		i++;
	}
	(*vm)->proc++;
	return (fork);
}

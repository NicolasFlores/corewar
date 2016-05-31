/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_function_13_16.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 16:40:45 by nflores           #+#    #+#             */
/*   Updated: 2016/05/30 12:44:08 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/vm.h"

void	*ft_lld(t_vm **vm, t_param_list *lst, int codage, t_proc **proc)
{
	if (param_type(read_value((*vm)->mem, codage, 1), 0, 13) == DIR)
		*(lst->next->param->reg) = lst->param->dir;
	else if (lst->param->ind >= 0)
		*(lst->next->param->reg) =
			read_value((*vm)->mem, (*proc)->pc - 1 - IND_SIZE - T_REG
					+ lst->param->ind, REG_SIZE);
	else
		*(lst->next->param->reg) =
			read_value((*vm)->mem, (*proc)->pc - 1 - IND_SIZE - T_REG
					- lst->param->ind * -1, REG_SIZE);
	return (NULL);
}

void	*ft_lldi(t_vm **vm, t_param_list *lst, int codage, t_proc **proc)
{
	int addr;
	int size1;
	int size2;

	size1 = param_size(param_type(read_value((*vm)->mem, codage, 1), 0, 14));
	size2 = param_size(param_type(read_value((*vm)->mem, codage, 1), 1, 14));
	if (param_type(read_value((*vm)->mem, codage, 1), 0, 13) == DIRI)
		addr = lst->param->dir;
	else if (param_type(read_value((*vm)->mem, codage, 1), 0, 13) == IND)
	{
		if (lst->param->ind >= 0)
			addr = read_value((*vm)->mem, (*proc)->pc - 1 - size1 - size2 - T_REG + lst->param->ind, 4);
		else
			addr = read_value((*vm)->mem, (*proc)->pc - 1 - size1 - size2 - T_REG - lst->param->ind * -1, 4);
	}
	else
		addr = *(lst->param->reg);
	if (param_type(read_value((*vm)->mem, codage, 1), 1, 13) == DIRI)
		addr += lst->next->param->dir;
	else if (param_type(read_value((*vm)->mem, codage, 1), 1, 13) == IND)
	{
		if (lst->next->param->ind >= 0)
			addr += read_value((*vm)->mem, (*proc)->pc - 1 - size1 - size2 - T_REG + lst->next->param->ind, 4);
		else
			addr += read_value((*vm)->mem, (*proc)->pc - 1 - size1 - size2 - T_REG - lst->next->param->ind * -1, 4);
	}
	else
		addr += *(lst->param->reg);
	*(lst->next->next->param->reg) = read_value((*vm)->mem, (*proc)->pc + addr, REG_SIZE);
	return (NULL);
}

void	*ft_lfork(t_vm **vm, t_param_list *lst, int codage, t_proc **proc)
{
	t_proc *fork;

	fork = init_proc((*proc)->champ, (*vm)->proc);
	fork->pc = (*proc)->pc - DIR_SIZE + lst->param->dir;
	(*vm)->proc++;
	return (fork);
}

void	*ft_aff(t_vm **vm, t_param_list *lst, int codage, t_proc **proc)
{
	unsigned char c;

	c = *(lst->param->reg);
	ft_printf("Aff : %c\n", c);
	return (NULL);
}

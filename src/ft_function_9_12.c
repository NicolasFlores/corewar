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

void	*ft_zjmp(t_vm **vm, t_param_list *lst, t_proc **proc)
{
	if (!(*vm))
		return (NULL);
	if ((*proc)->carry == 1)
	{
		if (lst->param->dir >= 0)
			(*proc)->pc = (*proc)->pc - 1 - T_DIR + lst->param->diri % IDX_MOD;
		else
			(*proc)->pc = (*proc)->pc - 1 - T_DIR -
							(lst->param->diri * -1) % IDX_MOD;
	}
	return (NULL);
}

void	*ft_ldi(t_vm **vm, t_param_list *lst, t_proc **proc)
{
	int addr;
	int size;

	size = (*proc)->pc - 2 - param_size(param_type((*proc)->codage, 0, 10)) -
			param_size(param_type((*proc)->codage, 1, 10)) - T_REG;
	if (param_type((*proc)->codage, 0, 10) == DIRI)
		addr = ft_index_value((*vm)->mem, lst->param->diri, size, 1);
	else if (param_type((*proc)->codage, 0, 10) == IND)
		addr = ft_index_value((*vm)->mem, lst->param->ind, size, 0);
	else
		addr = ft_index_value((*vm)->mem, *(lst->param->reg), size, 1);
	if (param_type((*proc)->codage, 1, 10) == DIRI)
		addr += ft_index_value((*vm)->mem, lst->next->param->diri, size, 1);
	else if (param_type((*proc)->codage, 1, 10) == IND)
		addr = ft_index_value((*vm)->mem, lst->next->param->ind, size, 0);
	else
		addr = ft_index_value((*vm)->mem, *(lst->next->param->reg), size, 1);
	ft_set_addrind((*vm)->mem, addr, lst->next->next->param->reg);
	return (NULL);
}

void	*ft_sti(t_vm **vm, t_param_list *lst, t_proc **proc)
{
	int addr;
	int size;

	size = (*proc)->pc - 2 - param_size(param_type((*proc)->codage, 1, 11)) -
			param_size(param_type((*proc)->codage, 2, 11)) - T_REG;
	if (param_type((*proc)->codage, 1, 11) == DIRI)
		addr = ft_index_value((*vm)->mem, lst->next->param->diri, size, 1);
	else if (param_type((*proc)->codage, 1, 11) == IND)
		addr = ft_index_value((*vm)->mem, lst->next->param->ind, size, 0);
	else
		addr = ft_index_value((*vm)->mem, *(lst->next->param->reg), size, 1);
	if (param_type((*proc)->codage, 2, 11) == DIRI)
		addr += ft_index_value_add(lst->next->next->param->diri);
	else
		addr += ft_index_value_add(*(lst->next->next->param->reg));
	if (addr >= 0)
		addr %= IDX_MOD;
	else
		addr = ((addr * -1) % IDX_MOD) * -1;
	write_value(&((*vm)->mem), *(lst->param->reg), addr + 1, (*proc)->champ);
	return (NULL);
}

void	*ft_fork(t_vm **vm, t_param_list *lst, t_proc **proc)
{
	t_proc	*fork;
	int		i;

	fork = init_proc((*proc)->champ, (*vm)->proc);
	if (lst->param->diri >= 0)
		fork->pc = (*proc)->pc - 1 - T_DIR + lst->param->diri % IDX_MOD;
	else
		fork->pc = (*proc)->pc - 1 - T_DIR - (lst->param->diri * -1) % IDX_MOD;
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

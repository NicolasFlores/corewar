/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_function_13_16.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 16:40:45 by nflores           #+#    #+#             */
/*   Updated: 2016/05/27 13:00:50 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/vm.h"

int		ft_lld(t_vm **vm, t_param_list *lst, int codage, t_proc **proc)
{
	if (param_type(read_value((*vm)->mem, codage, 1), 0, 13) == DIR)
		lst->next->param->reg->value = lst->param->dir;
	else if (lst->param->ind >= 0)
		lst->next->param->reg->value =
			read_value((*vm)->mem, (*proc)->pc + lst->param->ind, REG_SIZE);
	else
		lst->next->param->reg->value =
			read_value((*vm)->mem,
					(*proc)->pc - lst->param->ind * -1, REG_SIZE);
	return (10);
}

int		ft_lldi(t_vm **vm, t_param_list *lst, int codage, t_proc **proc)
{
	int addr;

	if (param_type(read_value((*vm)->mem, codage, 1), 0, 13) == DIRI)
		addr = lst->param->dir;
	else if (param_type(read_value((*vm)->mem, codage, 1), 0, 13) == IND)
	{
		if (lst->param->ind >= 0)
			addr = read_value((*vm)->mem, (*proc)->pc + lst->param->ind, 4);
		else
			addr = read_value((*vm)->mem, (*proc)->pc - lst->param->ind * -1, 4);
	}
	else
		addr = lst->param->reg->value;
	if (param_type(read_value((*vm)->mem, codage, 1), 1, 13) == DIRI)
		addr += lst->next->param->dir;
	else if (param_type(read_value((*vm)->mem, codage, 1), 1, 13) == IND)
	{
		if (lst->next->param->ind >= 0)
			addr += read_value((*vm)->mem, (*proc)->pc + lst->next->param->ind, 4);
		else
			addr += read_value((*vm)->mem, (*proc)->pc - lst->next->param->ind * -1, 4);
	}
	else
		addr += lst->param->reg->value;
	lst->next->next->param->reg->value = read_value((*vm)->mem, (*proc)->pc + addr, REG_SIZE);
	return (50);
}

int		ft_lfork(t_vm **vm, t_param_list *lst, int codage, t_proc **proc)
{
	return (1000);
}

int		ft_aff(t_vm **vm, t_param_list *lst, int codage, t_proc **proc)
{
	unsigned char c;

	c = lst->param->reg->value;
	ft_printf("Aff : %c\n", c);
	return (2);
}

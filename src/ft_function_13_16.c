/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_function_13_16.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 16:40:45 by nflores           #+#    #+#             */
/*   Updated: 2016/05/25 16:46:12 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/vm.h"

int		ft_lld(t_vm **vm, t_param **param, t_proc **exec_proc, t_proc **proc)
{
	if (param[0]->dir != NULL)
		param[1]->reg->value = *(param[0]->dir);
	else if (*(param[0]->ind) >= 0)
		param[1]->reg->value =
			read_value((*vm)->mem, (*proc)->pc + *(param[0]->ind), REG_SIZE);
	else
		param[1]->reg->value =
			read_value((*vm)->mem,
					(*proc)->pc - (*(param[0]->ind)) * -1, REG_SIZE);
	return (10);
}

int		ft_lldi(t_vm **vm, t_param **param, t_proc **exec_proc, t_proc **proc)
{
	int addr;

	if (param[0]->dir != NULL)
		addr = *(param[0]->dir);
	else if (param[0]->ind != NULL)
	{
		if (*(param[0]->ind) >= 0)
			addr = read_value((*vm)->mem, (*proc)->pc + *(param[0]->ind), 4);
		else
			addr = read_value((*vm)->mem, (*proc)->pc - ((*(param[0]->ind)) * -1), 4);
	}
	else
		addr = param[0]->reg->value;
	if (param[1]->dir != NULL)
		addr += *(param[1]->dir);
	else if (param[1]->ind != NULL)
	{
		if (*(param[1]->ind) >= 0)
			addr += read_value((*vm)->mem, (*proc)->pc + *(param[1]->ind), 4);
		else
			addr += read_value((*vm)->mem, (*proc)->pc - ((*(param[1]->ind)) * -1), 4);
	}
	else
		addr += param[0]->reg->value;
	param[2]->reg->value = read_value((*vm)->mem, (*proc)->pc + addr, REG_SIZE);
	return (50);
}

int		ft_lfork(t_vm **vm, t_param **param, t_proc **exec_proc, t_proc **proc)
{
	return (1000);
}

int		ft_aff(t_vm **vm, t_param **param, t_proc **exec_proc, t_proc **proc)
{
	unsigned char c;

	c = param[0]->reg->value;
	ft_printf("Aff : %c\n", c);
	return (2);
}

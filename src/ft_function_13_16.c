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
	if (param_type(codage, 0, 13) == DIR)
		*(lst->next->param->reg) = lst->param->dir;
	else if (lst->param->ind >= 0)
		*(lst->next->param->reg) =
			read_value((*vm)->mem, (*proc)->pc - 1 - IND_SIZE - T_REG
					+ lst->param->ind, REG_SIZE);
	else
		*(lst->next->param->reg) =
			read_value((*vm)->mem, (*proc)->pc - 1 - IND_SIZE - T_REG
					- lst->param->ind * -1, REG_SIZE);
	(*proc)->carry = 1;
	return (NULL);
}

void	*ft_lldi(t_vm **vm, t_param_list *lst, int codage, t_proc **proc)
{
	int addr;
	int size1;
	int size2;

	size1 = param_size(param_type(codage, 0, 14));
	size2 = param_size(param_type(codage, 1, 14));
	if (param_type(codage, 0, 14) == DIRI)
		addr = (*proc)->pc - 1 - size1 - size2 - T_REG + lst->param->diri;
	else if (param_type(codage, 0, 14) == IND)
		addr = read_value((*vm)->mem,
							(*proc)->pc - 1 - size1 - size2 - T_REG +
							lst->param->ind, 4);
	else
		addr = (*proc)->pc - 1 - size1 - size2 - T_REG + *(lst->param->reg);
	if (param_type(codage, 1, 14) == DIRI)
		addr += (*proc)->pc - 1 - size1 - size2 - T_REG +
				lst->next->param->diri;
	else if (param_type(codage, 1, 14) == REG)
		addr += (*proc)->pc - 1 - size1 - size2 - T_REG +
				*(lst->next->param->reg);
	*(lst->next->next->param->reg) = read_value((*vm)->mem,
												(*proc)->pc + addr, REG_SIZE);
	(*proc)->carry = 1;
	return (NULL);
}

void	*ft_lfork(t_vm **vm, t_param_list *lst, int codage, t_proc **proc)
{
	t_proc	*fork;
	int		i;

	fork = init_proc((*proc)->champ, (*vm)->proc);
	fork->pc = (*proc)->pc - T_DIR + lst->param->diri;
	fork->carry = (*proc)->carry;
	fork->live = (*proc)->live;
	(*vm)->proc++;
	(*proc)->carry = 1;
	i = 0;
	while (i < REG_NUMBER)
	{
		fork->reg[i] = (*proc)->reg[i];
		i++;
	}
	return (fork);
}

void	*ft_aff(t_vm **vm, t_param_list *lst, int codage, t_proc **proc)
{
	unsigned char c;

	c = *(lst->param->reg);
	ft_printf("Aff : %c\n", c);
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_function_1_4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 11:40:04 by nflores           #+#    #+#             */
/*   Updated: 2016/06/10 12:41:29 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/vm.h"

void	ft_carry(int val, t_proc **proc)
{
	if (val == 0)
		(*proc)->carry = 1;
	else
		(*proc)->carry = 0;
}

void	*ft_live(t_vm **vm, t_param_list *lst, t_proc **proc)
{
	t_champ_list	*tmp;

	(*proc)->live = 1;
	(*vm)->live++;
	tmp = (*vm)->champ_list;
	while (tmp)
	{
		if (lst->param->dir == (tmp->champ->num) * -1)
		{
			(*vm)->last_live = lst->param->dir;
			ft_printf("Un processus dit que le joueur %d(%s) est en vie\n",
					tmp->champ->num, tmp->champ->name);
			break ;
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void	*ft_ld(t_vm **vm, t_param_list *lst, t_proc **proc)
{
	int val;

	val = 0;
	if (param_type((*proc)->codage, 0, 2) == DIR)
	{
		val = lst->param->dir;
		*(lst->next->param->reg) = val;
	}
	else if (lst->param->ind >= 0)
	{
		val = (*proc)->pc - 2 - IND_SIZE - T_REG + lst->param->ind % IDX_MOD;
		*(lst->next->param->reg) = read_value((*vm)->mem, val + 1, REG_SIZE);
	}
	else
	{
		val = (*proc)->pc - 2 - IND_SIZE - T_REG -
				(lst->param->ind * -1) % IDX_MOD;
		*(lst->next->param->reg) = read_value((*vm)->mem, val - 1, REG_SIZE);
	}
	if (val == 0)
		(*proc)->carry = 1;
	else
		(*proc)->carry = 0;
	return (NULL);
}

void	*ft_st(t_vm **vm, t_param_list *lst, t_proc **proc)
{
	int addr;
	int val;

	val = *(lst->param->reg);
	addr = 0;
	if (param_type((*proc)->codage, 1, 3) == REG)
		*(lst->next->param->reg) = *(lst->param->reg);
	else if (lst->next->param->ind >= 0)
	{
		addr = (*proc)->pc - 2 - IND_SIZE - T_REG +
				lst->next->param->ind % IDX_MOD;
		write_value(&((*vm)->mem), val, addr + 1, (*proc)->champ);
	}
	else
	{
		addr = (*proc)->pc - 2 - IND_SIZE - T_REG -
				(lst->next->param->ind * -1) % IDX_MOD;
		write_value(&((*vm)->mem), *(lst->param->reg), addr + 1,
					(*proc)->champ);
	}
	return (NULL);
}

void	*ft_add(t_vm **vm, t_param_list *lst, t_proc **proc)
{
	int val;

	val = 0;
	if (!(*vm))
		return (NULL);
	if (param_type((*proc)->codage, 0, 4) == REG)
		val = *(lst->param->reg) + *(lst->next->param->reg);
	*(lst->next->next->param->reg) = val;
	if (val == 0)
		(*proc)->carry = 1;
	else
		(*proc)->carry = 0;
	return (NULL);
}

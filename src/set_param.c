/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_param.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 12:53:05 by nflores           #+#    #+#             */
/*   Updated: 2016/05/30 16:22:42 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/vm.h"

void	set_param(t_mem *mem, t_param *param, t_partype par, t_proc *proc)
{
	int rv;

	if (par == REG)
	{
		rv = read_value(mem, proc->pc + 1, T_REG) % 16;
		if (rv == 0)
			rv = 16;
		param->reg = &(proc->reg[rv - 1]);
	}
	else if (par == IND)
		param->ind = read_value(mem, proc->pc + 1, IND_SIZE);
	else if (par == DIRI)
		param->diri = read_value(mem, proc->pc + 1, DIR_SIZE / 2);
	else
		param->dir = read_value(mem, proc->pc + 1, DIR_SIZE);
	param->par = par;
}

int		ft_param_erase(t_mem *mem, t_proc *proc)
{
	t_param_list	*tmp;
	t_proc			*tmp2;
	t_param			*new;
	int				i;

	tmp = proc->par_list;
	new = init_param();
	tmp2 = init_proc(proc->champ, 0);
	tmp2->pc = proc->prevpc;
	i = 0;
	while (i < REG_NUMBER)
	{
		tmp2->reg[i] = proc->reg[i];
		i++;
	}
	while (tmp)
	{
		if (tmp->param->par != NUL)
			set_param(mem, new, tmp->param->par, tmp2);
		new->par = tmp->param->par;
		if (new->par == REG && *(new->reg) != *(tmp->param->reg))
			return (1);
		else if (new->par == IND && new->ind != tmp->param->ind)
			return (1);
		else if (new->par == DIRI && new->diri != tmp->param->diri)
			return (1);
		else if (new->par == DIR && new->dir != tmp->param->dir)
			return (1);
		tmp = tmp->next;
	}
	free(new);
	free(tmp2);
	return (0);
}

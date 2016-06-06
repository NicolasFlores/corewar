/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_proc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/01 15:43:08 by nflores           #+#    #+#             */
/*   Updated: 2016/06/01 16:12:29 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/vm.h"

void		init_parlst(t_proc **proc)
{
	int i;

	i = 0;
	while (i < 3)
	{
		if (!((*proc)->par_list))
			(*proc)->par_list = ft_param_lstnew();
		else
			ft_param_lstadd(&((*proc)->par_list), ft_param_lstnew());
		i++;
	}
}

t_proc		*init_proc(t_champ *champ, int n)
{
	t_proc	*ret;
	int		i;

	ret = (t_proc *)malloc(sizeof(t_proc));
	if (!ret)
		exit(write(2, "Malloc error\n", 13));
	ret->par_list = NULL;
	init_parlst(&ret);
	i = 0;
	while (i < REG_NUMBER)
	{
		ret->reg[i] = champ->reg[i];
		i++;
	}
	ret->champ = champ;
	ret->num = n;
	ret->pc = champ->pc;
	ret->prevpc = champ->pc;
	ret->live = 0;
	ret->opc = 0;
	ret->wex = 0;
	ret->codage = 0;
	ret->exec = 1;
	return (ret);
}

void		kill_proc(t_vm **vm, t_proc_list **exec_proc)
{
	int				i;
	int				tpr;
	t_proc_list		*tmp;
	t_proc_list		*tmp2;

	i = 0;
	tpr = (*vm)->proc;
	tmp = *exec_proc;
	while (i < tpr && tmp)
	{
		if (tmp->proc->live == 0)
		{
			tmp2 = tmp->next;
			ft_remove_proc(exec_proc, tmp->proc->num);
			tmp = tmp2;
			(*vm)->proc--;
		}
		else
		{
			tmp->proc->live = 0;
			tmp = tmp->next;
		}
		i++;
	}
}

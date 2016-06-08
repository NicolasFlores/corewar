/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_game.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/18 15:21:30 by nflores           #+#    #+#             */
/*   Updated: 2016/05/30 17:55:36 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/vm.h"

void	init_game(t_proc_list **exec_proc, t_champ_list *champ_list, t_vm *vm)
{
	int				i;
	t_champ_list	*tmp;

	i = 0;
	tmp = champ_list;
	while (i < vm->proc)
	{
		if (!(*exec_proc))
			*exec_proc = ft_proc_lstnew(init_proc(tmp->champ, i));
		else
			ft_proc_lstadd(exec_proc, ft_proc_lstnew(init_proc(tmp->champ, i)));
		i++;
		tmp = tmp->next;
	}
}

void	check_die(t_vm *vm, t_proc_list **exec_proc)
{
	if (vm->cycles == vm->ctd)
	{
		kill_proc(&vm, exec_proc);
		if (vm->live >= NBR_LIVE || vm->check == MAX_CHECKS - 1)
		{
			vm->cdelta -= CYCLE_DELTA;
			vm->check = 0;
			if (vm->cdelta <= 0)
				vm->cdelta = 1;
		}
		else
			vm->check++;
		vm->ctd += vm->cdelta;
		vm->live = 0;
	}
}

void	ft_param_game(t_vm *vm, t_proc_list **lst, int i, t_param_list *tmp)
{
	(*lst)->proc->codage = read_value(vm->mem, (*lst)->proc->pc, 1);
	if ((*lst)->proc->opc == 1 || (*lst)->proc->opc == 9 ||
		(*lst)->proc->opc == 12 || (*lst)->proc->opc == 15 ||
		ft_codage_valid((*lst)->proc->opc, (char)((*lst)->proc->codage)))
		while (--i)
		{
			if ((*lst)->proc->opc != 1 && (*lst)->proc->opc != 9 &&
				(*lst)->proc->opc != 12 && (*lst)->proc->opc != 15)
				(*lst)->proc->par = param_type((*lst)->proc->codage,
												nb_param((*lst)->proc->opc) - i,
												(*lst)->proc->opc);
			else if ((*lst)->proc->opc == 1)
				(*lst)->proc->par = DIR;
			else
				(*lst)->proc->par = DIRI;
			if ((*lst)->proc->par != NUL)
				set_param(vm->mem, tmp->param, (*lst)->proc->par, (*lst)->proc);
			else
				break ;
			tmp = tmp->next;
			(*lst)->proc->pc += param_size((*lst)->proc->par);
		}
}

void	get_opc(t_proc_list **lst, t_vm *vm)
{
	int 			i;
	t_param_list	*tmp;

	if (!is_opcode((*lst)->proc->opc))
		(*lst)->proc->opc = read_value(vm->mem, (*lst)->proc->pc + 1, 1);
	if ((*lst)->proc->exec && is_opcode((*lst)->proc->opc))
	{
		(*lst)->proc->prevpc = (*lst)->proc->pc;
		if ((*lst)->proc->opc == 1 || (*lst)->proc->opc == 9 ||
			(*lst)->proc->opc == 12 || (*lst)->proc->opc == 15)
			(*lst)->proc->pc++;
		else
			(*lst)->proc->pc += 2;
		i = nb_param((*lst)->proc->opc) + 1;
		tmp = (*lst)->proc->par_list;
		ft_param_game(vm, lst, i, tmp);
		(*lst)->proc->wex = vm->cycles + nb_cycles((*lst)->proc->opc) -
							(vm->cycles != 0);
		(*lst)->proc->exec = 0;
		if ((*lst)->proc->pc >= MEM_SIZE)
			(*lst)->proc->pc -= MEM_SIZE;
	}
	else if ((*lst)->proc->exec && !is_opcode((*lst)->proc->opc))
		(*lst)->proc->pc++;
}

void	ft_game(t_vm *vm, t_champ_list *champ_list, t_opt *opt)
{
	t_proc_list		*exec_proc;
	t_proc_list		*tmp;

	exec_proc = NULL;
	init_game(&exec_proc, champ_list, vm);
	while (vm->proc)
	{
		check_die(vm, &exec_proc);
		tmp = exec_proc;
		while (tmp)
		{
			get_opc(&tmp, vm);
			exec_opc(&tmp, &exec_proc, vm);
			tmp = tmp->next;
		}
		if (opt->set && opt->opt_d && vm->cycles == opt->n_d)
			break ;
		vm->cycles++;
	}
	ft_win(vm, opt, champ_list);
}

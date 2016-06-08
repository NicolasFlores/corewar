/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_opc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/08 11:28:04 by nflores           #+#    #+#             */
/*   Updated: 2016/06/08 12:11:47 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/vm.h"

void	*(*g_opcode[])(t_vm **, t_param_list *, t_proc **) = {
	ft_live, ft_ld, ft_st, ft_add, ft_sub, ft_and, ft_or, ft_xor, ft_zjmp,
	ft_ldi, ft_sti, ft_fork, ft_lld, ft_lldi, ft_lfork, ft_aff};

void	ft_exec(t_proc_list **lst, t_proc_list **exec_proc, t_vm *vm)
{
	if (((*lst)->proc->opc == 1 || (*lst)->proc->opc == 9 ||
		ft_codage_valid((*lst)->proc->opc, (char)((*lst)->proc->codage))) &&
		(*lst)->proc->par != NUL)
		g_opcode[(*lst)->proc->opc - 1](&vm,
										(*lst)->proc->par_list,
										&((*lst)->proc));
	else if (((*lst)->proc->opc == 12 || (*lst)->proc->opc == 15) &&
			(*lst)->proc->par != NUL)
		ft_proc_lstadd(exec_proc,
					ft_proc_lstnew(
						g_opcode[(*lst)->proc->opc - 1](&vm,
														(*lst)->proc->par_list,
														&((*lst)->proc))));
}

void	exec_opc(t_proc_list **lst, t_proc_list **exec_proc, t_vm *vm)
{
	if (vm->cycles != 0 && vm->cycles == (*lst)->proc->wex)
	{
		if (ft_codage_erase(vm->mem, (*lst)->proc) ||
			ft_param_erase(vm->mem, (*lst)->proc))
		{
			if ((*lst)->proc->opc == 1 || (*lst)->proc->opc == 9 ||
				(*lst)->proc->opc == 12 || (*lst)->proc->opc == 15)
				(*lst)->proc->codage = read_value(vm->mem,
												(*lst)->proc->prevpc + 1, 1);
			else
				(*lst)->proc->codage = read_value(vm->mem,
												(*lst)->proc->prevpc + 2, 1);
			reset_param(&((*lst)->proc->par_list));
			(*lst)->proc->exec = 1;
			(*lst)->proc->pc = (*lst)->proc->prevpc;
			get_opc(lst, vm);
		}
		ft_exec(lst, exec_proc, vm);
		(*lst)->proc->exec = 1;
		reset_param(&((*lst)->proc->par_list));
		(*lst)->proc->opc = 0;
		(*lst)->proc->wex = 0;
		(*lst)->proc->codage = 0;
	}
}

void	ft_win(t_vm *vm, t_opt *opt, t_champ_list *champ_list)
{
	t_champ_list *tmp;

	if (opt->set && opt->opt_d && vm->cycles == opt->n_d)
		ft_print_mem(vm->mem);
	else
	{
		tmp = champ_list;
		while (tmp->next && tmp->champ->num * -1 != vm->last_live)
			tmp = tmp->next;
		ft_printf("le joueur %d(%s) a gagne\n", tmp->champ->num,
				tmp->champ->name);
	}
}

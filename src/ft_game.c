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

void		*(*g_opcode[])(t_vm **, t_param_list *, int, t_proc **) = {
	ft_live, ft_ld, ft_st, ft_add, ft_sub, ft_and, ft_or, ft_xor, ft_zjmp,
	ft_ldi, ft_sti, ft_fork, ft_lld, ft_lldi, ft_lfork, ft_aff};

void		ft_game(t_vm *vm, t_champ_list *champ_list)
{
	t_proc_list		*exec_proc;
	t_proc_list		*tmp3;
	t_param_list	*tmp;
	int				i;
	t_champ_list	*tmp2;

	i = 0;
	tmp2 = champ_list;
	exec_proc = NULL;
	while (i < vm->proc)
	{
		if (!exec_proc)
			exec_proc = ft_proc_lstnew(init_proc(tmp2->champ, i));
		else
			ft_proc_lstadd(&exec_proc, ft_proc_lstnew(init_proc(tmp2->champ, i)));
		i++;
		tmp2 = tmp2->next;
	}
	while (vm->proc)
	{
		if (vm->cycles == vm->ctd)
		{
			kill_proc(&vm, &exec_proc);
			if (vm->live >= 21 || vm->check == MAX_CHECKS)
			{
				vm->cdelta -= CYCLE_DELTA;
				vm->check = 0;
				if (vm->cdelta <= 0)
					vm->cdelta = 1;
			}
			else
				vm->check++;
			vm->ctd += vm->cdelta;
		}
		tmp3 = exec_proc;
		while (tmp3)
		{
			if (!is_opcode(tmp3->proc->opc))
				tmp3->proc->opc = read_value(vm->mem, tmp3->proc->pc + 1, 1);
			if (tmp3->proc->exec && is_opcode(tmp3->proc->opc))
			{
				if (tmp3->proc->opc == 1 || tmp3->proc->opc == 9 || tmp3->proc->opc == 12 || tmp3->proc->opc == 15)
					tmp3->proc->pc++;
				else
					tmp3->proc->pc += 2;
				i = nb_param(tmp3->proc->opc);
				tmp3->proc->codage = read_value(vm->mem, tmp3->proc->pc, 1);
				tmp = tmp3->proc->par_list;
				if (tmp3->proc->opc == 1 || tmp3->proc->opc == 9 || tmp3->proc->opc == 12 || tmp3->proc->opc == 15 ||
					ft_codage_valid(tmp3->proc->opc, (char)(tmp3->proc->codage)))
					while (i)
					{
						if (tmp3->proc->opc != 1 && tmp3->proc->opc != 9 && tmp3->proc->opc != 12 && tmp3->proc->opc != 15)
							tmp3->proc->par = param_type(tmp3->proc->codage, nb_param(tmp3->proc->opc) - i, tmp3->proc->opc);
						else if (tmp3->proc->opc == 1)
							tmp3->proc->par = DIR;
						else
							tmp3->proc->par = DIRI;
						if (tmp3->proc->par != NUL)
							set_param(vm->mem, tmp->param, tmp3->proc->par, tmp3->proc);
						else
							break ;
						i--;
						tmp = tmp->next;
						tmp3->proc->pc += param_size(tmp3->proc->par);
						if (tmp3->proc->pc >= MEM_SIZE)
							tmp3->proc->pc -= MEM_SIZE;
					}
				tmp3->proc->wex = vm->cycles + nb_cycles(tmp3->proc->opc);
				if (vm->cycles != 0)
					tmp3->proc->wex--;
				tmp3->proc->exec = 0;
			}
			else if (tmp3->proc->exec && !is_opcode(tmp3->proc->opc))
			{
				tmp3->proc->pc++;
				if (tmp3->proc->pc >= MEM_SIZE)
					tmp3->proc->pc -= MEM_SIZE;
			}
			if (vm->cycles != 0 && vm->cycles == tmp3->proc->wex)
			{
				//ft_printf("cycle = %d | opcode = %d | proc = %d | pc = %d\n", vm->cycles, tmp3->proc->opc, tmp3->proc->num, tmp3->proc->pc);
				if ((tmp3->proc->opc == 1 || tmp3->proc->opc == 9 ||
					ft_codage_valid(tmp3->proc->opc, (char)(tmp3->proc->codage))) && tmp3->proc->par != NUL)
					g_opcode[tmp3->proc->opc - 1](&vm, tmp3->proc->par_list, tmp3->proc->codage, &(tmp3->proc));
				else if ((tmp3->proc->opc == 12 || tmp3->proc->opc == 15) && tmp3->proc->par != NUL)
				{
					ft_proc_lstadd(&exec_proc,
								ft_proc_lstnew(g_opcode[tmp3->proc->opc - 1](&vm, tmp3->proc->par_list, tmp3->proc->codage, &(tmp3->proc))));
				}
				tmp3->proc->exec = 1;
				reset_param(&(tmp3->proc->par_list));
				tmp3->proc->opc = 0;
				tmp3->proc->wex = 0;
				tmp3->proc->codage = 0;
			}
			tmp3 = tmp3->next;
		}
		vm->cycles++;
		if (vm->cycles == 2715)
		{;
			//ft_printf("nb proc = %d\n", vm->proc);
			//exit(0);
		}
	}
	ft_printf("cycles =  %d\n", vm->cycles);
	tmp2 = champ_list;
	while (tmp2->next && tmp2->champ->num * -1 != vm->last_live)
		tmp2 = tmp2->next;
	ft_printf("le joueur %d(%s) a gagne\n", tmp2->champ->num,
			tmp2->champ->name);
}

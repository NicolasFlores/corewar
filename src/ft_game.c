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

t_proc		*init_proc(t_champ *champ, int n)
{
	t_proc *ret;
	int i;

	ret = (t_proc *)malloc(sizeof(t_proc));
	if (!ret)
		exit(write(2, "Malloc error\n", 13));
	ret->par_list = NULL;
	i = 0;
	while (i < 3)
	{
		if (!(ret->par_list))
			ret->par_list = ft_param_lstnew();
		else
			ft_param_lstadd(&(ret->par_list), ft_param_lstnew());
		i++;
	}
	ret->champ = champ;
	ret->num = n;
	ret->pc = champ->pc;
	ret->live = 0;
	ret->size = champ->prog_size;
	ret->exec = 1;
	return (ret);
}

void		kill_proc(t_vm **vm, t_proc_list **exec_proc)
{
	int i;
	int j;
	int tpr;
	t_proc_list *tmp;
	t_proc_list *tmp2;

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

void		ft_game(t_vm *vm, t_champ_list *champ_list)
{
	t_proc_list		*exec_proc, *tmp3;
	t_param_list	*tmp;
	int			i, j, k, l, ctd;
	int			*opc, *wex, *codage;
	int			*opc2, *wex2, *codage2;
	t_partype	par;
	t_champ_list *tmp2;

	i = 0;
	tmp2 = champ_list;
	exec_proc = NULL;
	ctd = CYCLE_TO_DIE;
	opc = (int *)malloc(sizeof(int) * vm->proc);
	wex = (int *)malloc(sizeof(int) * vm->proc);
	codage = (int *)malloc(sizeof(int) * vm->proc);
	if (!opc || !wex || !codage)
		exit(write(2, "Malloc error\n", 13));
	while (i < vm->proc)
	{
		if (!exec_proc)
			exec_proc = ft_proc_lstnew(init_proc(tmp2->champ, i));
		else
			ft_proc_lstadd(&exec_proc, ft_proc_lstnew(init_proc(tmp2->champ, i)));
		opc[i] = 0;
		wex[i] = 0;
		codage[i] = 0;
		i++;
		tmp2 = tmp2->next;
	}
	while (vm->proc)
	{
		if (vm->cycles == vm->ctd)
		{
			kill_proc(&vm, &exec_proc);
			if (vm->live >= 21)
			{
				ctd -= CYCLE_DELTA;
				vm->ctd += ctd;
				vm->check = 0;
			}
			else if (vm->check == MAX_CHECKS)
			{
				ctd -= CYCLE_DELTA;
				vm->check = 0;
				vm->ctd += ctd;
			}
			else
			{
				vm->ctd += ctd;
				vm->check++;
			}
		}
		i = 0;
		tmp3 = exec_proc;
		while (i < vm->proc)
		{
			if (!is_opcode(opc[i]))
				opc[i] = read_value(vm->mem, tmp3->proc->pc + 1, 1);
			if (tmp3->proc->exec && is_opcode(opc[i]))
			{
				if (opc[i] == 1 || opc[i] == 9 || opc[i] == 12 || opc[i] == 15)
					tmp3->proc->pc++;
				else
					tmp3->proc->pc += 2;
				j = nb_param(opc[i]);
				codage[i] = tmp3->proc->pc;
				tmp = tmp3->proc->par_list;
				if (opc[i] == 1 || opc[i] == 9 || opc[i] == 12 || opc[i] == 15 ||
					ft_codage_valid(opc[i], read_value(vm->mem, codage[i], 1)))
					while (j)
					{
						if (opc[i] != 1 && opc[i] != 9 && opc[i] != 12 && opc[i] != 15)
							par = param_type(read_value(vm->mem, codage[i], 1), nb_param(opc[i]) - j, opc[i]);
						else if (opc[i] == 1)
							par = DIR;
						else
							par = DIRI;
						if (par != NUL)
							set_param(vm->mem, tmp->param, par, tmp3->proc);
						else
							break ;
						j--;
						tmp = tmp->next;
						tmp3->proc->pc += param_size(par);
					}
				wex[i] = vm->cycles + nb_cycles(opc[i]);
				tmp3->proc->exec = 0;
			}
			else if (tmp3->proc->exec && !is_opcode(opc[i]))
				tmp3->proc->pc++;
			if (vm->cycles != 0 && vm->cycles == wex[i])
			{
				if (opc[i] == 1 || opc[i] == 9 ||
					ft_codage_valid(opc[i], (char)read_value(vm->mem, codage[i], 1)))
					g_opcode[opc[i] - 1](&vm, tmp3->proc->par_list, codage[i], &(tmp3->proc));
				else if (opc[i] == 12 || opc[i] == 15)
				{
					ft_proc_lstadd(&exec_proc,
								ft_proc_lstnew(g_opcode[opc[i] - 1](&vm, tmp3->proc->par_list, codage[i], &(tmp3->proc))));
					opc2 = realloc(opc, sizeof(int) * vm->proc);
					wex2 = realloc(wex, sizeof(int) * vm->proc);
					codage2 = realloc(codage, sizeof(int) * vm->proc);
					if (!opc2 || !wex2 || !codage2)
						exit(write(2, "Realloc error\n", 14));
					opc = opc2;
					wex = wex2;
					codage = codage2;
					opc[vm->proc - 1] = 0;
					wex[vm->proc - 1] = 0;
					codage[vm->proc - 1] = 0;
				}
				tmp3->proc->exec = 1;
				reset_param(&(tmp3->proc->par_list));
				opc[i] = 0;
				wex[i] = 0;
				codage[i] = 0;
			}
			i++;
			tmp3 = tmp3->next;
		}
		vm->cycles++;
	}
	tmp2 = champ_list;
	while (tmp2->next && tmp2->champ->num * -1 != vm->last_live)
		tmp2 = tmp2->next;
	ft_printf("le joueur %d(%s) a gagne\n", tmp2->champ->num,
			tmp2->champ->name);
	free(opc);
	free(wex);
	free(codage);
}

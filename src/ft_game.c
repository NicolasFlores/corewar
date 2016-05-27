/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_game.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/18 15:21:30 by nflores           #+#    #+#             */
/*   Updated: 2016/05/27 13:11:01 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/vm.h"

int			(*g_opcode[])(t_vm **, t_param_list *, int, t_proc **) = {
	ft_live, ft_ld, ft_st, ft_add, ft_sub, ft_and, ft_or, ft_xor, ft_zjmp,
	ft_ldi, ft_sti, ft_fork, ft_lld, ft_lldi, ft_lfork, ft_aff};

t_param		*init_param(void)
{
	t_param *ret;

	ret = (t_param *)malloc(sizeof(t_param *));
	if (!ret)
		exit(write(2, "Malloc error\n", 13));
	ret->reg = NULL;
	ret->ind = 0;
	ret->dir = 0;
	return (ret);
}

t_param_list	*ft_param_lstnew(void)
{
	t_param_list *ret;

	ret = (t_param_list *)malloc(sizeof(t_param_list));
	if (!ret)
		exit(write(2, "Malloc error\n", 13));
	ret->param = init_param();
	ret->next = NULL;
	return (ret);
}

void		ft_param_lstadd(t_param_list **lst, t_param_list *new)
{
	t_param_list *tmp;

	tmp = *lst;
	if (tmp)
		while (tmp->next)
			tmp = tmp->next;
	tmp->next = new;
}

t_proc		*init_proc(t_champ *champ)
{
	t_proc *ret;
	t_param_list *tmp;
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
	ret->pc = champ->pc;
	ret->live = 0;
	ret->size = champ->prog_size;
	ret->exec = 1;
	return (ret);
}


void		reset_param(t_param_list **lst)
{
	t_param_list *tmp;

	tmp = *lst;
	while (tmp)
	{
		tmp->param->reg = NULL;
		tmp->param->ind = 0;
		tmp->param->dir = 0;
		tmp = tmp->next;
	}
}

void		kill_proc(t_vm **vm, t_proc **exec_proc)
{
	int i;
	int j;
	int tpr;

	i = 0;	
	tpr = (*vm)->proc;
	while (i < tpr)
	{
		if (exec_proc[i]->live == 0)
		{
			free(exec_proc[i]);
			exec_proc[i] = NULL;
			(*vm)->proc--;
		}
		else
			exec_proc[i]->live = 0;
		i++;
	}
	i = 0;
	while (i < tpr - 1)
	{
		while (exec_proc[i] != NULL)
			i++;
		j = i + 1;
		while (j < tpr)
		{
			if (exec_proc[j] != NULL)
			{
				exec_proc[i] = exec_proc[j];
				exec_proc[j] = NULL;
				break ;
			}
			j++;
		}
		i++;
	}
}

void		ft_game(t_vm *vm, t_champ_list *champ_list)
{
	t_proc		*exec_proc[vm->proc];
	t_param_list	*tmp;
	int			i, j;
	int			opc[vm->proc], wex[vm->proc];
	int			codage[vm->proc];
	t_partype	par;
	t_champ_list *tmp2;

	ft_print_mem(vm->mem);
	i = 0;
	tmp2 = champ_list;
	while (i < vm->proc)
	{
		exec_proc[i] = init_proc(tmp2->champ);
		opc[i] = 0;
		wex[i] = 0;
		codage[i] = 0;
		i++;
		tmp2 = tmp2->next;
	}
	while (vm->proc)
	{
//		ft_printf("---cycle %d---\n", vm->cycles);
		if (vm->cycles == vm->ctd)
		{
			ft_printf("---cycle %d -> kill---\n", vm->cycles);
			kill_proc(&vm, exec_proc);
			if (vm->live >= 21)
			{ 
				vm->ctd += CYCLE_TO_DIE - CYCLE_DELTA;
				vm->check = 0;
			}
			else if (vm->check == MAX_CHECKS)
			{
				vm->check = 0;
				vm->ctd += CYCLE_TO_DIE - CYCLE_DELTA;
			}
			else
			{
				vm->ctd += CYCLE_TO_DIE;
				vm->check++;
			}
		}
		i = 0;
		while (i < vm->proc)
		{
			if (!is_opcode(opc[i]))
				opc[i] = read_value(vm->mem, exec_proc[i]->pc + 1, 1);
			if (exec_proc[i]->exec && is_opcode(opc[i]))
			{
				//ft_printf("cycle %d champion %d oct = %d opc = %d\n", vm->cycles, i + 1, exec_proc[i]->pc, opc[i]);
				exec_proc[i]->exec = 0;
				if (opc[i] == 1 || opc[i] == 9 || opc[i] == 12 || opc[i] == 15)
					exec_proc[i]->pc++;
				else
					exec_proc[i]->pc += 2;
				j = nb_param(opc[i]);
				codage[i] = exec_proc[i]->pc;
				tmp = exec_proc[i]->par_list;
				while (j)
				{
					if (opc[i] != 1 && opc[i] != 9 && opc[i] != 12 && opc[i] != 15)
						par = param_type(read_value(vm->mem, codage[i], 1), nb_param(opc[i]) - j, opc[i]);
					else if (opc[i] == 1)
						par = DIR;
					else
						par = DIRI;
					if (par != NUL)
						set_param(vm->mem, tmp->param, par, exec_proc[i]);
					else
					{
						exec_proc[i]->exec = 1;
						break ;
					}
					j--;
					tmp = tmp->next;
					ft_printf("cycle %d opc = %d par size = %d partype = %d\n", vm->cycles, opc[i], param_size(par), par);
					exec_proc[i]->pc += param_size(par);
				}
				wex[i] = vm->cycles + nb_cycles(opc[i]);
			}
			else if (exec_proc[i]->exec && !is_opcode(opc[i]))
				exec_proc[i]->pc++;
			if (vm->cycles != 0 && vm->cycles == wex[i])
			{
				ft_printf("<<<cycle %d>>>\nopc = %d champ %d pc = %d\n", vm->cycles, opc[i], i + 1, exec_proc[i]->pc);
				g_opcode[opc[i] - 1](&vm, exec_proc[i]->par_list, codage[i], &(exec_proc[i]));
				exec_proc[i]->exec = 1;
				reset_param(&(exec_proc[i]->par_list));
				opc[i] = 0;
				ft_putendl("<<<>>>");
			}
			i++;
		}
		vm->cycles++;
	}
	ft_print_mem(vm->mem);
	while (champ_list->next && champ_list->champ->num * -1 != vm->last_live)
		champ_list = champ_list->next;
	ft_printf("le joueur %d(%s) a gagne\n", champ_list->champ->num,
			champ_list->champ->name);
	free(exec_proc[0]);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_game.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/18 15:21:30 by nflores           #+#    #+#             */
/*   Updated: 2016/05/26 13:43:46 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/vm.h"

int			(*g_opcode[])(t_vm **, t_param **, t_proc **, t_proc **) = {
	ft_live, ft_ld, ft_st, ft_add, ft_sub, ft_and, ft_or, ft_xor, ft_zjmp,
	ft_ldi, ft_sti, ft_fork, ft_lld, ft_lldi, ft_lfork, ft_aff};

t_proc		*init_proc(t_champ *champ)
{
	t_proc *ret;

	ret = (t_proc *)malloc(sizeof(t_proc));
	if (!ret)
		exit(write(2, "Malloc error\n", 13));
	ret->champ = champ;
	ret->pc = champ->pc;
	ret->live = 0;
	ret->size = champ->prog_size;
	ret->exec = 1;
	return (ret);
}

t_param		**init_param(void)
{
	t_param **ret;

	ret = (t_param **)malloc(sizeof(t_param *) * 3);
	if (!ret)
		exit(write(2, "Malloc error\n", 13));
	ret[0] = (t_param *)malloc(sizeof(t_param));
	ret[1] = (t_param *)malloc(sizeof(t_param));
	ret[2] = (t_param *)malloc(sizeof(t_param));
	if (!ret[0] || !ret[1] || !ret[2])
		exit(write(2, "Malloc error\n", 13));
	ret[0]->reg = NULL;
	ret[0]->ind = NULL;
	ret[0]->dir = NULL;
	ret[1]->reg = NULL;
	ret[1]->ind = NULL;
	ret[1]->dir = NULL;
	ret[2]->reg = NULL;
	ret[2]->ind = NULL;
	ret[2]->dir = NULL;
	return (ret);
}

void		reset_param(t_param **param)
{
	param[0]->reg = NULL;
	param[0]->ind = NULL;
	param[0]->dir = NULL;
	param[1]->reg = NULL;
	param[1]->ind = NULL;
	param[1]->dir = NULL;
	param[2]->reg = NULL;
	param[2]->ind = NULL;
	param[2]->dir = NULL;
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
	t_proc		**exec_proc;
	t_param		***param;
	int			i, j;
	int			opc[vm->proc], wex[vm->proc];
	int			codage;
	t_partype	par;
	t_champ_list *tmp;

	i = 0;
	tmp = champ_list;
	exec_proc = (t_proc **)malloc(sizeof(t_proc *) * vm->proc);
	param = (t_param ***)malloc(sizeof(t_param **) * vm->proc);
	if (!exec_proc)
		exit(write(2, "Malloc error\n", 13));
	while (i < vm->proc)
	{
		exec_proc[i] = init_proc(tmp->champ);
		param[i] = init_param();
		opc[i] = 0;
		wex[i] = 0;
		i++;
		tmp = tmp->next;
	}
	while (vm->proc)
	{
		if (vm->cycles == vm->ctd)
		{
			kill_proc(&vm, exec_proc);
			vm->ctd += CYCLE_TO_DIE - CYCLE_DELTA;
		}
		i = 0;
		while (i < vm->proc)
		{
			if (opc[i] == 0)
				opc[i] = read_value(vm->mem, exec_proc[i]->pc + 1, 1);
			if (exec_proc[i]->exec && is_opcode(opc[i]))
			{
				ft_printf("oct = %d opc = %d\n", exec_proc[i]->pc, opc[i]);
				wex[i] = vm->cycles + nb_cycles(opc[i]);
				exec_proc[i]->exec = 0;
				if (opc[i] == 1 || opc[i] == 9 || opc[i] == 12 || opc[i] == 15)
					exec_proc[i]->pc++;
				else
					exec_proc[i]->pc += 2;
				j = nb_param(opc[i]);
				codage = exec_proc[i]->pc;
				while (j)
				{
					if (opc[i] != 1 && opc[i] != 9 && opc[i] != 12 && opc[i] != 15)
						par = param_type(read_value(vm->mem, codage, 1), nb_param(opc[i]) - j);
					else
						par = DIR;
					if (par != NUL)
						set_param(vm->mem, param[i][nb_param(opc[i]) - j], par, exec_proc[i]);
					else
						break ;
					j--;
					exec_proc[i]->pc += param_size(par);
				}
			}
			else if (exec_proc[i]->exec && !is_opcode(opc[i]))
				exec_proc[i]->pc++;
			if (vm->cycles == wex[i])
			{
				g_opcode[opc[i] - 1](&vm, param[i], exec_proc, &(exec_proc[i]));
				exec_proc[i]->exec = 1;
				reset_param(param[i]);
				opc[i] = 0;
			}
			i++;
		}
		vm->cycles++;
	}
	ft_printf("win = %d\n", vm->last_live);
	while (champ_list->next && champ_list->champ->num * -1 != vm->last_live)
		champ_list = champ_list->next;
	ft_printf("le joueur %d(%s) a gagne\n", champ_list->champ->num,
			champ_list->champ->name);
	free(exec_proc[0]);
	free(param[0][0]);
	free(param[0][1]);
	free(param[0][2]);
	free(param[0]);
}

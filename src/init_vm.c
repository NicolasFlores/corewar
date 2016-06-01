/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/18 15:07:04 by nflores           #+#    #+#             */
/*   Updated: 2016/05/27 11:16:22 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/vm.h"

t_vm	*init_vm(t_mem *mem, t_champ_list *lst)
{
	t_vm *ret;

	ret = (t_vm *)malloc(sizeof(t_vm));
	if (!ret)
		exit(write(2, "Malloc error\n", 13));
	ret->mem = mem;
	ret->champ_list = lst;
	ret->ctd = CYCLE_TO_DIE;
	ret->cdelta = CYCLE_TO_DIE;
	ret->cycles = 0;
	ret->check = 0;
	ret->live = 0;
	ret->last_live = 0;
	ret->proc = ft_champ_lstsize(lst);
	return (ret);
}

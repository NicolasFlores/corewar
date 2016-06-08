/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_newmem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/17 10:36:54 by nflores           #+#    #+#             */
/*   Updated: 2016/05/30 13:20:44 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/vm.h"

t_mem		*ft_newmem(int n)
{
	t_mem	*ret;

	ret = (t_mem *)malloc(sizeof(t_mem));
	if (!ret)
		exit(write(2, "Malloc error\n", 13));
	ret->oct = 0;
	ret->n = n;
	ret->champ_own = 0;
	ret->champ_wr = 0;
	ret->prev = ret;
	ret->next = ret;
	return (ret);
}

void		ft_meminit(t_mem **mem, int size)
{
	t_mem	*tmp;
	t_mem	*new;
	int		i;

	i = 0;
	*mem = ft_newmem(0);
	tmp = *mem;
	while (i < size - 1)
	{
		new = ft_newmem(i + 1);
		new->prev = tmp;
		new->next = tmp->next;
		tmp->next->prev = new;
		tmp->next = new;
		tmp = tmp->next;
		i++;
	}
}

void		ft_gameinit(t_mem **mem, t_champ_list *lst, int nb_champ)
{
	int		i;
	int		j;
	t_mem	*tmp;

	i = 0;
	tmp = *mem;
	while (i < MEM_SIZE)
	{
		j = 0;
		while (j < lst->champ->prog_size)
		{
			if (j == 0)
				lst->champ->pc = tmp->n;
			tmp->oct = lst->champ->prog[j];
			tmp->champ_own = lst->champ->reg[0];
			tmp->champ_wr = lst->champ->reg[0];
			j++;
			tmp = tmp->next;
		}
		i += MEM_SIZE / nb_champ + lst->champ->pc % 2;
		while (tmp->n != i - lst->champ->pc % 2 && tmp->n != MEM_SIZE - 1)
			tmp = tmp->next;
		lst = lst->next;
	}
	tmp = NULL;
}

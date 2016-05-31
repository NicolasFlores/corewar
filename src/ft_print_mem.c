/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_mem.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/27 10:36:14 by nflores           #+#    #+#             */
/*   Updated: 2016/05/31 11:46:07 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/vm.h"

void	ft_print_mem(t_mem *mem)
{
	int i;

	i = 0;
	while (i < MEM_SIZE)
	{
		ft_printf("%.2x ", mem->oct);
		i++;
		mem = mem->next;
		if (i != 0 && i % 64 == 0)
			ft_putchar('\n');
	}
}

void	ft_print_memn(t_mem *mem)
{
	int i;

	i = 0;
	while (i < MEM_SIZE)
	{
		ft_printf("%d\n", mem->n);
		i++;
		mem = mem->next;
		if (i != 0 && i % 64 == 0)
			ft_putchar('\n');
	}
}

void	ft_print_rmemn(t_mem *mem)
{
	int i;

	i = 0;
	while (i < MEM_SIZE)
	{
		ft_printf("%d\n", mem->prev->n);
		i++;
		mem = mem->prev;
		if (i != 0 && i % 64 == 0)
			ft_putchar('\n');
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_contest.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/12 15:16:44 by nflores           #+#    #+#             */
/*   Updated: 2016/05/23 16:03:34 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/vm.h"

void	ft_print_contest(t_champ_list *champ_list)
{
	ft_putendl("Champion dans l'arene :\n");
	while (champ_list)
	{
		ft_printf("Joueur %d -> %s(%s) est dans la place avec %d bytes.\n",
				champ_list->champ->num, champ_list->champ->name,
				champ_list->champ->comment, champ_list->champ->prog_size);
		champ_list = champ_list->next;
	}
	ft_putchar('\n');
}

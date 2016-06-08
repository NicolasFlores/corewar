/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_champ_lstnew.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 14:20:56 by nflores           #+#    #+#             */
/*   Updated: 2016/05/18 17:00:40 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/vm.h"

t_champ_list	*ft_champ_lstnew(t_champ *new)
{
	t_champ_list *ret;

	ret = (t_champ_list *)malloc(sizeof(t_champ_list));
	ret->champ = new;
	ret->next = NULL;
	return (ret);
}

void			ft_champ_lstadd(t_champ_list **lst, t_champ_list *new)
{
	t_champ_list *tmp;

	tmp = *lst;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

int				ft_champ_lstsize(t_champ_list *lst)
{
	int ret;

	ret = 0;
	while (lst)
	{
		ret++;
		lst = lst->next;
	}
	return (ret);
}

int				ft_num_valid(t_champ_list *lst)
{
	t_champ_list *tmp;
	t_champ_list *tmp2;

	tmp = lst;
	while (tmp)
	{
		tmp2 = tmp->next;
		while (tmp2)
		{
			if (tmp->champ->num == tmp2->champ->num)
				return (0);
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
	return (1);
}

void			ft_set_champnum(t_champ_list *lst, t_opt *opt)
{
	t_champ_list	*tmp;
	int				i;

	tmp = lst;
	i = -1;
	while (tmp && ++i < opt->opt_n)
	{
		tmp->champ->num = opt->n_n[i];
		tmp = tmp->next;
	}
	while (!ft_num_valid(lst))
	{
		i = 0;
		tmp = lst;
		while (tmp && i < opt->opt_n)
		{
			tmp = tmp->next;
			i++;
		}
		while (tmp)
		{
			tmp->champ->num++;
			tmp = tmp->next;
		}
	}
}

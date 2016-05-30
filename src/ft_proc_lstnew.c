/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_proc_lstnew.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/30 10:25:25 by nflores           #+#    #+#             */
/*   Updated: 2016/05/30 16:34:41 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/vm.h"

t_proc_list	*ft_proc_lstnew(t_proc *proc)
{
	t_proc_list	*ret;

	ret = (t_proc_list *)malloc(sizeof(t_proc_list));
	if (!ret)
		exit(write(2, "Malloc error\n", 13));
	ret->proc = proc;
	ret->next = NULL;
	return (ret);
}

void		ft_proc_lstadd(t_proc_list **lst, t_proc_list *new)
{
	t_proc_list *tmp;

	tmp = *lst;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}

void		ft_remove_proc(t_proc_list **lst, int n)
{
	t_proc_list *tmp;
	t_proc_list *tmp2;

	tmp = NULL;
	if (lst)
		tmp = *lst;
	else
		return ;
	tmp2 = tmp;
	while (tmp && tmp->next && tmp->proc->num != n)
	{
		tmp2 = tmp;
		tmp = tmp->next;
	}
	if (tmp == *lst)
		*lst = tmp->next;
	tmp2->next = tmp->next;
	free(tmp->proc);
	free(tmp);
}

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

	if (proc == NULL)
		return (NULL);
	ret = (t_proc_list *)malloc(sizeof(t_proc_list));
	if (!ret)
		exit(write(2, "Malloc error\n", 13));
	ret->proc = proc;
	ret->next = NULL;
	return (ret);
}

void		ft_proc_lstadd(t_proc_list **lst, t_proc_list *new)
{
	if (new == NULL)
		return ;
	new->next = *lst;
	*lst = new;
}

void		ft_proc_lstaddend(t_proc_list **lst, t_proc_list *new)
{
	t_proc_list *tmp;

	if (new == NULL)
		return ;
	tmp = *lst;
	while (tmp && tmp->next)
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
	ft_free_parlst(&(tmp->proc->par_list));
	free(tmp->proc);
	free(tmp);
}

int			ft_proc_lstsize(t_proc_list *lst)
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

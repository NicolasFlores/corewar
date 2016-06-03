/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_param.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/27 13:48:46 by nflores           #+#    #+#             */
/*   Updated: 2016/05/30 13:07:49 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/vm.h"

t_param			*init_param(void)
{
	t_param *ret;

	ret = (t_param *)malloc(sizeof(t_param));
	if (!ret)
		exit(write(2, "Malloc error\n", 13));
	ret->reg = NULL;
	ret->ind = 0;
	ret->dir = 0;
	ret->diri = 0;
	ret->par = NUL;
	return (ret);
}

void			reset_param(t_param_list **lst)
{
	t_param_list *tmp;

	tmp = *lst;
	while (tmp)
	{
		tmp->param->reg = NULL;
		tmp->param->ind = 0;
		tmp->param->dir = 0;
		tmp->param->diri = 0;
		tmp->param->par = NUL;
		tmp = tmp->next;
	}
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

void			ft_param_lstadd(t_param_list **lst, t_param_list *new)
{
	t_param_list *tmp;

	tmp = *lst;
	if (tmp)
		while (tmp->next)
			tmp = tmp->next;
	tmp->next = new;
}

void			ft_free_parlst(t_param_list **lst)
{
	t_param_list *tmp;

	tmp = *lst;
	while (tmp)
	{
		tmp = tmp->next;
		(*lst)->param->reg = NULL;
		free((*lst)->param);
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}

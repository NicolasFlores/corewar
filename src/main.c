/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/10 17:30:23 by nflores           #+#    #+#             */
/*   Updated: 2016/05/26 10:11:38 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/vm.h"

static int	ft_check_arg(t_opt **opt, int argc, char **argv)
{
	int i;

	if (argc == 1)
	{
		ft_putendl("Usage : ./corewar [-d N | -n N] <champ1.cor> <...>");
		exit(0);
	}
	i = get_opt(opt, argc, argv);
	if (i == argc - 1)
		exit(write(2, "One or more champ are required\n", 31));
	if (argc - i > MAX_PLAYERS + 1)
		exit(write(2, "Too many champions\n", 19));
	return (i);
}

static void	free_mem(t_mem **mem)
{
	t_mem *tmp;
	t_mem *tmp2;

	tmp = (*mem)->prev;
	while (*mem != tmp)
	{
		tmp2 = (*mem)->next;
		(*mem)->prev = NULL;
		(*mem)->next = NULL;
		free(*mem);
		*mem = tmp2;
	}
	free(*mem);
	*mem = NULL;
	tmp = NULL;
	tmp2 = NULL;
}

static void	free_champ(t_champ **champ)
{
	free((*champ)->name);
	free((*champ)->comment);
	free((*champ)->prog);
	free(*champ);
	champ = NULL;
}

static void	free_champ_list(t_champ_list **lst)
{
	t_champ_list *tmp;

	tmp = *lst;
	while (tmp)
	{
		tmp = tmp->next;
		free_champ(&((*lst)->champ));
		free(*lst);
		*lst = tmp;
	}
	lst = NULL;
}

int			main(int argc, char **argv)
{
	int				i;
	t_opt			*opt;
	t_champ_list	*champ_list;
	t_mem			*mem;
	t_vm			*vm;

	opt = NULL;
	i = ft_check_arg(&opt, argc, argv);
	champ_list = NULL;
	while (++i < argc)
		init_champ(argv, i, &champ_list, opt);
	ft_print_contest(champ_list);
	mem = NULL;
	ft_meminit(&mem, MEM_SIZE);
	ft_gameinit(&mem, champ_list, ft_champ_lstsize(champ_list));
	vm = init_vm(mem, champ_list);
	ft_game(vm, champ_list);
	free(opt);
	free_mem(&mem);
	free_champ_list(&champ_list);
	free(vm);
	return (0);
}

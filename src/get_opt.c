/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_opt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/12 12:58:37 by nflores           #+#    #+#             */
/*   Updated: 2016/05/12 15:42:04 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/vm.h"

static void	init_opt(t_opt **opt)
{
	*opt = (t_opt *)malloc(sizeof(t_opt));
	if (!(*opt))
		exit(write(2, "Malloc error\n", 13));
	(*opt)->opt_d = 0;
	(*opt)->opt_n = 0;
	(*opt)->n_d = 0;
	(*opt)->n_n = (int *)malloc(sizeof(int));
	if (!((*opt)->n_n))
		exit(write(2, "Malloc error\n", 13));
	*((*opt)->n_n) = 0;
}

static void	check_opt_format(char **argv, int ret)
{
	int i;

	i = 0;
	while (argv[ret + 1][i] != '\0')
	{
		if (!ft_isdigit(argv[ret + 1][i]))
			exit(write(2, "Invalid option\n", 15));
		i++;
	}
}

void		set_optn(t_opt **opt, char **argv, int size, int ret)
{
	int *tmp;
	int i;

	i = 0;
	while (i < size)
	{
		if (ft_atoi(argv[ret + 1]) == (*opt)->n_n[i])
			exit(write(2, "Same num for champ is invalid\n", 30));
		i++;
	}
	if (size > 0)
	{
		tmp = (int *)realloc((*opt)->n_n, sizeof(int) * (size + 1));
		(*opt)->n_n = tmp;
		tmp = NULL;
	}
	(*opt)->n_n[size] = ft_atoi(argv[ret + 1]);
}

int			get_opt(t_opt **opt, int argc, char **argv)
{
	int ret;

	ret = 1;
	init_opt(opt);
	while (ret < argc - 1 && argv[ret][0] == '-')
	{
		if (argv[ret][1] == 'n' && argv[ret][2] == '\0')
		{
			check_opt_format(argv, ret);
			set_optn(opt, argv, (*opt)->opt_n, ret);
			(*opt)->opt_n++;
			ret += 2;
		}
		else if (argv[ret][1] == 'd' && argv[ret][2] == '\0')
		{
			(*opt)->opt_d = 1;
			check_opt_format(argv, ret);
			(*opt)->n_d = ft_atoi(argv[ret + 1]);
			ret += 2;
		}
		else
			exit(write(2, "Invalid option\n", 15));
	}
	(*opt)->set = (*opt)->opt_d || (*opt)->opt_n;
	return (ret - 1);
}

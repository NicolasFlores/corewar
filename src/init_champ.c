/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_champ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/12 15:01:40 by nflores           #+#    #+#             */
/*   Updated: 2016/05/30 13:19:51 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/vm.h"

void	init_champ(char **argv, int i, t_champ_list **champ_list, t_opt *opt)
{
	int		oct;
	int		pr_size;
	t_champ	*tmp;
	char	*file;
	int		j;

	file = NULL;
	oct = check_arg(&file, argv[i]);
	pr_size = (file[PROG_NAME_LENGTH + sizeof(int) * 2] << 24) |
		(0x00ff0000 & (file[PROG_NAME_LENGTH + sizeof(int) * 2 + 1] << 16)) |
		(0x0000ff00 & (file[PROG_NAME_LENGTH + sizeof(int) * 2 + 2] << 8)) |
		(0x000000ff & file[PROG_NAME_LENGTH + sizeof(int) * 2 + 3]);
	tmp = ft_newchamp(file + sizeof(int), file + sizeof(int) * 3 +
					PROG_NAME_LENGTH, oct, pr_size);
	tmp->reg[0] = -(i - (opt->opt_n != 0) * 2 - opt->opt_d * 2);
	tmp->num = i - opt->opt_n * 2 - opt->opt_d * 2;
	j = -1;
	while (++j < tmp->prog_size)
		(tmp->prog)[j] = file[sizeof(int) * 4 + PROG_NAME_LENGTH +
							COMMENT_LENGTH + j];
	if (*champ_list)
		ft_champ_lstadd(champ_list, ft_champ_lstnew(tmp));
	else
		*champ_list = ft_champ_lstnew(tmp);
	free(file);
}

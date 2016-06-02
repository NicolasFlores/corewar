/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_opcode.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 11:45:24 by nflores           #+#    #+#             */
/*   Updated: 2016/05/27 10:34:04 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/vm.h"

int			is_opcode(char oct)
{
	return (oct >= 1 && oct <= 16);
}

int			nb_param(int opc)
{
	if (opc == 1 || opc == 9 || opc == 12 || opc == 15 || opc == 16)
		return (1);
	else if (opc == 2 || opc == 3 || opc == 13)
		return (2);
	return (3);
}

t_partype	param_type(char oct, int num, int opc)
{
	t_partype	ret;

	oct = (oct >> (6 - (num * 2))) & 0b00000011;
	ret = NUL;
	if (oct == 0b01)
		ret = REG;
	else if (oct == 0b10)
	{
		if (opc == 9 || opc == 10 || opc == 11 || opc == 12 ||
			opc == 14 || opc == 15)
			ret = DIRI;
		else
			ret = DIR;
	}
	else if (oct == 0b11)
		ret = IND;
	return (ret);
}

int			param_size(t_partype par)
{
	if (par == REG)
		return (T_REG);
	else if (par == DIRI)
		return (T_DIR);
	else if (par == DIR)
		return (DIR_SIZE);
	else if (par == IND)
		return (IND_SIZE);
	return (0);
}

int			nb_cycles(int opc)
{
	if (opc == 1 || opc == 4 || opc == 5 || opc == 13)
		return (10);
	else if (opc == 2 || opc == 3)
		return (5);
	else if (opc >= 6 && opc <= 8)
		return (6);
	else if (opc == 9)
		return (20);
	else if (opc == 10 || opc == 11)
		return (25);
	else if (opc == 12)
		return (800);
	else if (opc == 14)
		return (50);
	else if (opc == 15)
		return (1000);
	else if (opc == 16)
		return (2);
	return (-1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_codage.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/30 15:15:06 by nflores           #+#    #+#             */
/*   Updated: 2016/05/30 16:02:55 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/vm.h"

int		ft_codage_valid(int opc, int codage)
{
	if (opc == 2 || opc == 13)
		return (codage == 0x90 || codage == 0xd0);
	else if (opc == 3)
		return (codage == 0x50 || codage ==0x70);
	else if (opc == 4 || opc == 5)
		return (codage == 0x54);
	else if (opc == 6 || opc == 7 || opc == 8)
		return (codage == 0x54 || codage == 0x64 || codage == 0x74 ||
				codage == 0x94 || codage == 0xa4 || codage == 0xb4 ||
				codage == 0xd4 || codage == 0xe4 || codage == 0xf4);
	else if (opc == 10 || opc == 14)
		return (codage == 0x54 || codage == 0x64 || codage == 0x94 ||
				codage == 0xa4 || codage == 0xd4 || codage == 0xe4);
	else if (opc == 11)
		return (codage == 0x54 || codage == 0x58 || codage == 0x64 ||
				codage == 0x68 || codage == 0x74 || codage == 0x78);
	else if (opc == 16)
		return (codage == 0x40);
	return (0);
}

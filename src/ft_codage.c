/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_codage.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <nflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/15 10:48:24 by nflores           #+#    #+#             */
/*   Updated: 2016/06/15 12:26:26 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/vm.h"

int		ft_codage_valid(int opc, char codage)
{
	if (opc == 2 || opc == 13)
		return (codage == (char)0x90 || codage == (char)0xd0);
	else if (opc == 3)
		return (codage == (char)0x50 || codage == (char)0x70);
	else if (opc == 4 || opc == 5)
		return (codage == (char)0x54);
	else if (opc == 6 || opc == 7 || opc == 8)
		return (codage == (char)0x54 || codage == (char)0x64 ||
				codage == (char)0x74 || codage == (char)0x94 ||
				codage == (char)0xa4 || codage == (char)0xb4 ||
				codage == (char)0xd4 || codage == (char)0xe4 ||
				codage == (char)0xf4);
	else if (opc == 10 || opc == 14)
		return (codage == (char)0x54 || codage == (char)0x64 ||
				codage == (char)0x94 || codage == (char)0xa4 ||
				codage == (char)0xd4 || codage == (char)0xe4);
	else if (opc == 11)
		return (codage == (char)0x54 || codage == (char)0x58 ||
				codage == (char)0x64 || codage == (char)0x68 ||
				codage == (char)0x74 || codage == (char)0x78);
	else if (opc == 16)
		return (codage == (char)0x40);
	return (0);
}

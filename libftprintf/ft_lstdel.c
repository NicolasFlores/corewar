/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 13:14:13 by nflores           #+#    #+#             */
/*   Updated: 2015/11/30 14:38:06 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void			ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	if (*alst)
	{
		(del)((*alst)->content, (*alst)->content_size);
		if ((*alst)->next)
			ft_lstdel(&((*alst)->next), del);
		free(*alst);
		*alst = NULL;
	}
}

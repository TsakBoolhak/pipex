/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstclear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 13:37:02 by acabiac           #+#    #+#             */
/*   Updated: 2021/10/17 13:37:05 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_dlist.h"

void	ft_dlstclear(t_dlist **alst, void (*del)(void *))
{
	t_dlist	*tmp;

	if (!alst || !*alst)
		return ;
	*alst = ft_dlstfirst(*alst);
	while (*alst)
	{
		tmp = (*alst)->next;
		if (del)
			(*del)((*alst)->content);
		free(*alst);
		*alst = tmp;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstadd_front.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 13:43:29 by acabiac           #+#    #+#             */
/*   Updated: 2021/10/17 13:43:31 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dlist.h"

void	ft_dlstadd_front(t_dlist **alst, t_dlist *new)
{
	t_dlist	*lst;

	if (!new || !alst)
		return ;
	else if (!*alst)
	{
		*alst = new;
		return ;
	}
	lst = ft_dlstfirst(*alst);
	new->next = lst;
	lst->prev = new;
	*alst = new;
}

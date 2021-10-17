/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstadd_before.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 13:38:27 by acabiac           #+#    #+#             */
/*   Updated: 2021/10/17 13:38:28 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dlist.h"

void	ft_dlstadd_before(t_dlist **alst, t_dlist *ref, t_dlist *new)
{
	t_dlist	*lst;

	if (!new || !ref || !alst || !*alst)
		return ;
	lst = ft_dlstfirst(*alst);
	if (*alst == ref)
		*alst = new;
	while (lst && lst != ref)
		lst = lst->next;
	if (!lst)
		return ;
	new->prev = lst->prev;
	new->next = lst;
	if (lst->prev)
		lst->prev->next = new;
	lst->prev = new;
}

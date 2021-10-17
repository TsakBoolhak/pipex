/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstadd_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 13:43:11 by acabiac           #+#    #+#             */
/*   Updated: 2021/10/17 13:43:12 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dlist.h"

void	ft_dlstadd_back(t_dlist **alst, t_dlist *new)
{
	t_dlist	*lst;

	if (!new || !alst)
		return ;
	if (!*alst)
	{
		*alst = new;
		return ;
	}
	lst = ft_dlstlast(*alst);
	new->prev = lst;
	lst->next = new;
}

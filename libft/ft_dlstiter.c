/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstiter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 13:35:15 by acabiac           #+#    #+#             */
/*   Updated: 2021/10/17 13:35:17 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dlist.h"

void	ft_dlstiter(t_dlist *lst, void (*f)(void *))
{
	lst = ft_dlstfirst(lst);
	while (lst)
	{
		(*f)(lst->content);
		lst = lst->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstmap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 13:35:46 by acabiac           #+#    #+#             */
/*   Updated: 2021/10/17 13:35:47 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "ft_dlist.h"

t_dlist	*ft_dlstmap(t_dlist *lst, void *(*f)(void *), void (*del)(void *))
{
	t_dlist	*new_lst;
	t_dlist	*begin_lst;

	if (!lst)
		return (NULL);
	new_lst = ft_dlstdup(lst, del);
	if (!new_lst)
		return (NULL);
	begin_lst = new_lst;
	while (new_lst)
	{
		new_lst->content = f(new_lst->content);
		new_lst = new_lst->next;
	}
	return (begin_lst);
}

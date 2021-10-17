/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstarg_to_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 13:35:55 by acabiac           #+#    #+#             */
/*   Updated: 2021/10/17 13:35:57 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dlist.h"
#include "stddef.h"

t_dlist	*ft_dlstarg_to_list(int ac, char *av[])
{
	int		i;
	t_dlist	*lst;
	t_dlist	*new;

	lst = NULL;
	i = ac - 1;
	while (i > 0)
	{
		new = ft_dlstnew(av[i]);
		if (!new)
		{
			ft_dlstclear(&lst, NULL);
			return (NULL);
		}
		ft_dlstadd_front(&lst, new);
		i--;
	}
	return (lst);
}

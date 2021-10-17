/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstsplit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 13:41:20 by acabiac           #+#    #+#             */
/*   Updated: 2021/10/17 13:41:21 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dlist.h"
#include "ft_memory.h"
#include <stdlib.h>

t_dlist	*ft_dlstsplit(char const *s, char c)
{
	char	**tab;
	t_dlist	*lst;
	t_dlist	*new;
	size_t	i;

	tab = ft_split(s, c);
	if (!tab)
		return (NULL);
	i = 0;
	lst = NULL;
	while (tab[i])
	{
		new = ft_dlstnew(tab[i]);
		if (!new)
		{
			ft_dlstclear(&lst, NULL);
			return (ft_free_tab((void **)tab));
		}
		ft_dlstadd_back(&lst, new);
		i++;
	}
	free(tab);
	return (lst);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 13:37:58 by acabiac           #+#    #+#             */
/*   Updated: 2021/10/17 13:37:59 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_dlist.h"

t_dlist	*ft_dlstnew(void *content)
{
	t_dlist	*list;

	list = (t_dlist *)malloc(sizeof(t_dlist));
	if (!list)
		return (NULL);
	list->content = content;
	list->prev = NULL;
	list->next = NULL;
	return (list);
}

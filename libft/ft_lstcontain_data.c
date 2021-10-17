/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcontain_data.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 13:36:46 by acabiac           #+#    #+#             */
/*   Updated: 2021/10/17 13:36:47 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include "ft_string.h"

int	ft_lstcontain_data(t_list *lst, void *data, size_t size, size_t n)
{
	while (lst)
	{
		if (!ft_memcmp(data, lst->content, size * n))
			return (1);
		lst = lst->next;
	}
	return (0);
}

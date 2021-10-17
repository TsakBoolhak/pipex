/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tablen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 13:36:23 by acabiac           #+#    #+#             */
/*   Updated: 2021/10/17 13:36:24 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_tablen(char **tab)
{
	size_t	ret;

	ret = 0;
	if (!tab)
		return (ret);
	while (tab[ret])
		ret++;
	return (ret);
}

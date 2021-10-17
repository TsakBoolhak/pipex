/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 13:36:06 by acabiac           #+#    #+#             */
/*   Updated: 2021/10/17 13:36:08 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_tools.h"
#include "ft_string.h"
#include <stdlib.h>

char	**ft_tabdup(char **tab)
{
	size_t	tablen;
	char	**new_tab;

	if (!tab)
		return (NULL);
	tablen = ft_tablen(tab);
	new_tab = malloc(sizeof(*new_tab) * (tablen + 1));
	if (!new_tab)
		return (NULL);
	ft_memcpy(new_tab, tab, tablen * sizeof(*tab));
	new_tab[tablen] = NULL;
	return (new_tab);
}

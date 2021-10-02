/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_tools2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 02:22:03 by acabiac           #+#    #+#             */
/*   Updated: 2021/10/02 02:23:21 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strchr(const char *s, int c)
{
	char	to_find;

	to_find = (char)(c);
	while (*s && *s != to_find)
		s++;
	if (*s == to_find)
		return ((char *)(s));
	else
		return (NULL);
}

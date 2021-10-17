/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoll.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 13:34:55 by acabiac           #+#    #+#             */
/*   Updated: 2021/10/17 13:34:59 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

long long	ft_strtoll(const char *str, char **end)
{
	unsigned long long	result;
	int					i;
	int					j;
	int					sign;

	i = 0;
	j = 0;
	result = 0;
	while (ft_isspace(str[i]))
		i++;
	sign = 1 - (2 * (str[i] == '-'));
	i += (str[i] == '-' || str[i] == '+');
	while (ft_isdigit(str[i + j]))
	{
		result = result * 10 + str[i + j++] - '0';
		if (result > (unsigned long long)(LONG_MAX + (sign == -1)))
			j = 0;
		if (result > (unsigned long long)(LONG_MAX + (sign == -1)))
			break ;
	}
	if (end && !j)
		*end = (char *)str;
	else if (end)
		*end = (char *)(str + i + j);
	return (result * sign);
}

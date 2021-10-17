/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_charset.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 13:41:39 by acabiac           #+#    #+#             */
/*   Updated: 2021/10/17 13:41:42 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "ft_string.h"

char	*ft_strchr_charset(const char *s, const char *charset)
{
	if (!*charset)
		return ((char *)(s + ft_strlen(s)));
	while (*charset && !ft_strchr(s, *charset))
		charset++;
	if (*charset)
		return (ft_strchr(s, *charset));
	return (NULL);
}

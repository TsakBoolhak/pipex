/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 20:58:00 by acabiac           #+#    #+#             */
/*   Updated: 2021/10/26 13:35:21 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "pipex_bonus.h"

char	*ft_strjoin(char const *src, char const *to_append)
{
	char	*dst;
	size_t	len_src;
	size_t	len_to_append;

	if (!src && !to_append)
		return (NULL);
	else if (!src)
		return (ft_strdup(to_append));
	else if (!to_append)
		return (ft_strdup(src));
	len_src = ft_strlen(src);
	len_to_append = ft_strlen(to_append);
	dst = (char *)malloc(sizeof(*dst) * (len_src + len_to_append + 1));
	if (!dst)
		return (NULL);
	ft_memcpy(dst, src, len_src);
	ft_memcpy(dst + len_src, to_append, len_to_append + 1);
	return (dst);
}

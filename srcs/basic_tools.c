/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 22:15:40 by acabiac           #+#    #+#             */
/*   Updated: 2021/09/08 22:51:31 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	if (n == 0)
		return (0);
	i = 0;
	str1 = (unsigned char *)(s1);
	str2 = (unsigned char *)(s2);
	while (i < n - 1 && *str1 && *str2 && *str1 == *str2)
	{
		i++;
		str1++;
		str2++;
	}
	return (*str1 - *str2);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dst_tmp;
	unsigned char	*src_tmp;

	i = 0;
	dst_tmp = (unsigned char *)dst;
	src_tmp = (unsigned char *)src;
	while (i < n)
	{
		dst_tmp[i] = src_tmp[i];
		i++;
	}
	return (dst);
}

char	*ft_strdup(const char *src)
{
	char	*dst;
	size_t	len;

	len = ft_strlen(src);
	dst = (char *)malloc(sizeof(*dst) * (len + 1));
	if (!dst)
		return (NULL);
	ft_memcpy(dst, src, len);
	dst[len] = '\0';
	return (dst);
}

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

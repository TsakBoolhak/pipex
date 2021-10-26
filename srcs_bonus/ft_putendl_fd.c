/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 20:45:51 by acabiac           #+#    #+#             */
/*   Updated: 2021/10/26 13:53:44 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "pipex_bonus.h"

int	ft_putendl_fd(char *s, int fd)
{
	int	ret;

	ret = ft_putstr_fd(s, fd);
	if (ret < 0)
		return (-1);
	if (ft_putchar_fd('\n', fd) != 1)
		return (-1);
	return (ret + 1);
}

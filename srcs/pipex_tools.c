/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 22:28:26 by acabiac           #+#    #+#             */
/*   Updated: 2021/09/09 00:11:58 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "pipex.h"

int	init_pathes(char *cmd, char **envp, char ***ret, char ***pathes)
{
	int	i;

	*pathes = NULL;
	*ret = ft_split(cmd, ' ');
	if (*ret == NULL)
		return (1);
	i = 0;
	while (envp[i] && ft_strncmp("PATH", envp[i], 4))
		i++;
	if (!envp[i])
		return (0);
	*pathes = ft_split(envp[i], ':');
	if (!*pathes)
	{
		ft_free_tab((void **)ret);
		return (1);
	}
	return (0);
}

int	free_and_return(char **pathes, char **ret, int error)
{
	ft_free_tab((void **)pathes);
	ft_free_tab((void **)ret);
	return (error);
}

int	check_pathes(char *name, char ***ret, char ***pathes)
{
	int	i;
	int	check;

	i = 0;
	while (*pathes && (*pathes)[i])
	{
		check = check_path(&((*pathes)[i]), &((*ret)[0]), pathes);
		if (check == -1)
			return (close_and_print_error(name, -1, -1, -1));
		else if (!check)
			return (0);
		i++;
	}
	ft_free_tab((void **)*pathes);
	if (!access((*ret)[0], X_OK))
		return (0);
	write(2, name, ft_strlen(name));
	write(2, ": ", 2);
	perror((*ret)[0]);
	ft_free_tab((void **)*ret);
	return (-1);
}

int	check_path(char **path, char **ret, char ***pathes)
{
	char	*tmp;

	tmp = ft_strjoin(*path, "/");
	if (!tmp)
		return (free_and_return(*pathes, ret, -1));
	free(*path);
	*path = tmp;
	tmp = ft_strjoin(*path, *ret);
	if (!tmp)
		return (free_and_return(*pathes, ret, -1));
	else if (!access(tmp, X_OK))
	{
		free(*ret);
		*ret = tmp;
		ft_free_tab((void **)*pathes);
		return (0);
	}
	free(tmp);
	return (1);
}

int	close_and_print_error(char *str, int fd1, int fd2, int error)
{
	if (str)
		perror(str);
	if (fd1 >= 0)
		close(fd1);
	if (fd2 >= 0)
		close(fd2);
	return (error);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 23:07:08 by acabiac           #+#    #+#             */
/*   Updated: 2021/10/27 16:53:17 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

char	**handle_absolute(char ***pathes, char ***ret, char *cmd)
{
	ft_free_tab((void **)*pathes);
	if (!access((*ret)[0], X_OK))
		return (*ret);
	perror(cmd);
	ft_free_tab((void **)*ret);
	return (NULL);
}

char	**handle_relative(char ***pathes, char ***ret, char *cmd)
{
	char	*tmp;

	ft_free_tab((void **)*pathes);
	tmp = ft_strjoin("./", (*ret)[0]);
	if (!tmp)
	{
		ft_putendl_fd("pipex_bonus: Memory allocation failed", 2);
		ft_free_tab((void **)*ret);
		return (NULL);
	}
	if (!access(tmp, X_OK))
	{
		free((*ret)[0]);
		(*ret)[0] = tmp;
		return (*ret);
	}
	free(tmp);
	perror(cmd);
	ft_free_tab((void **)*ret);
	return (NULL);
}

int	check_path(char **path, char **ret, char ***pathes)
{
	char	*tmp;

	tmp = ft_strjoin(*path, "/");
	if (!tmp)
	{
		ft_putendl_fd("pipex_bonus: Memory allocation failed", 2);
		return (free_path_and_return(*pathes, ret, -1));
	}
	free(*path);
	*path = tmp;
	tmp = ft_strjoin(*path, *ret);
	if (!tmp)
	{
		ft_putendl_fd("pipex_bonus: Memory allocation failed", 2);
		return (free_path_and_return(*pathes, ret, -1));
	}
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

int	check_pathes(char ***ret, char ***pathes)
{
	int	i;
	int	check;

	i = 0;
	while (*pathes && (*pathes)[i])
	{
		check = check_path(&((*pathes)[i]), &((*ret)[0]), pathes);
		if (check == -1)
			return (-1);
		else if (!check)
			return (0);
		i++;
	}
	ft_free_tab((void **)*pathes);
	ft_free_tab((void **)*ret);
	return (-1);
}

char	**get_cmd_path(char *const envp[], char *cmd)
{
	char	**ret;
	char	**pathes;

	if (!cmd || !*cmd)
		return (NULL);
	if (init_pathes(cmd, (char **)envp, &ret, &pathes) || !ret || !ret[0])
	{
		ft_putendl_fd("pipex_bonus: Memory allocation failed", 2);
		return (NULL);
	}
	if (ret[0][0] == '/')
		return (handle_absolute(&pathes, &ret, cmd));
	else if (ft_strchr(ret[0], '/'))
		return (handle_relative(&pathes, &ret, cmd));
	else if (check_pathes(&ret, &pathes))
	{
		access(cmd, X_OK);
		perror(cmd);
		return (NULL);
	}
	else
		return (ret);
}

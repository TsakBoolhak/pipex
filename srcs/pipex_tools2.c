/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_tools2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 18:22:22 by acabiac           #+#    #+#             */
/*   Updated: 2021/10/02 03:06:23 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "pipex.h"

char	**handle_absolute(char ***pathes, char ***ret, char *const av[])
{
	ft_free_tab((void **)*pathes);
	if (!access((*ret)[0], X_OK))
		return (*ret);
	write(2, av[0], ft_strlen(av[0]));
	write(2, ": ", 2);
	perror((*ret)[0]);
	ft_free_tab((void **)*ret);
	return (NULL);
}

char	**handle_relative(char ***pathes, char ***ret, char *const av[])
{
	char	*tmp;

	ft_free_tab((void **)*pathes);
	tmp = ft_strjoin("./", (*ret)[0]);
	if (!tmp)
	{
		perror(av[0]);
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
	write(2, av[0], ft_strlen(av[0]));
	write(2, ": ", 2);
	perror((*ret)[0]);
	ft_free_tab((void **)*ret);
	return (NULL);
}

char	**get_cmd_path(char *const av[], char *const envp[], char *cmd)
{
	char	**ret;
	char	**pathes;

	if (!cmd || !*cmd)
		return (NULL);
	if (init_pathes(cmd, (char **)envp, &ret, &pathes))
	{
		perror(av[0]);
		return (NULL);
	}
	if (ret[0][0] == '/')
		return (handle_absolute(&pathes, &ret, av));
	else if (ft_strchr(ret[0], '/'))
		return (handle_relative(&pathes, &ret, av));
	else if (check_pathes(av[0], &ret, &pathes))
		return (NULL);
	else
		return (ret);
}

int	left_side(int pfd[2], char *const av[], char *const envp[])
{
	char	**cmd_av;
	int		fd;

	close(pfd[0]);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		write(2, av[0], ft_strlen(av[0]));
		write(2, ": ", 2);
		return (close_and_print_error(av[1], pfd[1], -1, 5));
	}
	if (dup2(fd, STDIN_FILENO) == -1)
		return (close_and_print_error(av[0], pfd[1], -1, 6));
	close(fd);
	if (dup2(pfd[1], STDOUT_FILENO) == -1)
		return (close_and_print_error(av[0], pfd[1], -1, 7));
	close(pfd[1]);
	cmd_av = get_cmd_path(av, envp, av[2]);
	if (!cmd_av)
		return (8);
	execve(cmd_av[0], cmd_av, envp);
	perror(av[0]);
	ft_free_tab((void **)cmd_av);
	return (9);
}

int	right_side(int pfd[2], char *const av[], char *const envp[])
{
	char	**cmd_av;
	int		fd;

	close(pfd[1]);
	fd = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd == -1)
	{
		write(2, av[0], ft_strlen(av[0]));
		write(2, ": ", 2);
		return (close_and_print_error(av[4], pfd[0], -1, 10));
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (close_and_print_error(av[0], pfd[0], -1, 11));
	close(fd);
	if (dup2(pfd[0], STDIN_FILENO) == -1)
		return (close_and_print_error(av[0], pfd[0], -1, 12));
	close(pfd[0]);
	cmd_av = get_cmd_path(av, envp, av[3]);
	if (!cmd_av)
		return (13);
	execve(cmd_av[0], cmd_av, envp);
	perror(av[0]);
	ft_free_tab((void **)cmd_av);
	return (14);
}

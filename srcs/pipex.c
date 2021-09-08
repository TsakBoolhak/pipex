/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 18:22:22 by acabiac           #+#    #+#             */
/*   Updated: 2021/09/09 00:13:54 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>
#include "pipex.h"

char	**get_cmd_path(char *const av[], char *const envp[], char *cmd)
{
	char	**ret;
	char	**pathes;

	if (init_pathes(cmd, (char **)envp, &ret, &pathes))
	{
		perror(av[0]);
		return (NULL);
	}
	if (check_pathes(av[0], &ret, &pathes))
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

int	main(int ac, char *const av[], char *const envp[])
{
	int	pfd[2];
	int	pid1;
	int	pid2;
	int	ret;

	if (ac != 5)
		return (1);
	else if (pipe(pfd) == -1)
		return (close_and_print_error(av[0], -1, -1, 2));
	pid1 = fork();
	if (pid1 == -1)
		return (close_and_print_error(av[0], pfd[0], pfd[1], 3));
	else if (!pid1)
		return (left_side(pfd, av, envp));
	pid2 = fork();
	if (pid2 == -1)
		return (close_and_print_error(av[0], pfd[0], pfd[1], 4));
	else if (!pid2)
		return (right_side(pfd, av, envp));
	close(pfd[0]);
	close(pfd[1]);
	ret = 1;
	while (ret > 0 && errno != ECHILD)
		ret = wait(NULL);
	return (0);
}

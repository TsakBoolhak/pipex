/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 18:22:22 by acabiac           #+#    #+#             */
/*   Updated: 2021/10/02 03:05:51 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "pipex.h"

int	main(int ac, char *const av[], char *const envp[])
{
	int	pfd[2];
	int	pid1;
	int	pid2;

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
	while (errno != ECHILD)
		wait(NULL);
	return (0);
}

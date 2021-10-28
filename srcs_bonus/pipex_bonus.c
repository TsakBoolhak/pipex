/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 21:43:40 by acabiac           #+#    #+#             */
/*   Updated: 2021/10/28 17:19:26 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <stddef.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;
	int		ret;

	if (init_pipex(&pipex, ac, av, envp))
		return (1);
	ret = main_loop(&pipex);
	while (errno != ECHILD)
		wait(NULL);
	if (ret)
		return (ret);
	else
		return (free_and_return(&pipex, NULL, 0, -2));
}

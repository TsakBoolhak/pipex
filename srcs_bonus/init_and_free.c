/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 23:47:13 by acabiac           #+#    #+#             */
/*   Updated: 2021/10/27 16:51:40 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

void	put_error(t_error errcode)
{
	static char	*err_msg[] = {"Memory allocation failed",
		"Too few argument given to the program"};

	if (errcode == PERROR)
		perror(NULL);
	else
	{
		ft_putstr_fd("pipex_bonus: ", 2);
		ft_putendl_fd(err_msg[errcode], 2);
	}
}

int	free_and_return(t_pipex *pipex, int *pfd, int ret, t_error errcode)
{
	if (!access(".here_doc_tmp", F_OK))
		unlink(".here_doc_tmp");
	if (pfd)
	{
		if (pfd[0] > 2)
			close(pfd[0]);
		if (pfd[1] > 2)
			close(pfd[1]);
	}
	if (pipex)
	{
		ft_lstclear(&(pipex->cmdlist), NULL);
		if (pipex->fd[0] > 2)
			close(pipex->fd[0]);
		if (pipex->fd[1] > 2)
			close(pipex->fd[1]);
		if ((pipex->pfd)[0] > 2)
			close((pipex->pfd)[0]);
		if ((pipex->pfd)[1] > 2)
			close((pipex->pfd)[1]);
	}
	if (errcode > -2)
		put_error(errcode);
	return (ret);
}

int	init_pathes(char *cmd, char **envp, char ***ret, char ***pathes)
{
	int	i;

	*pathes = NULL;
	*ret = ft_split(cmd, ' ');
	if (*ret == NULL)
		return (1);
	i = 0;
	while (envp[i] && ft_strncmp("PATH=", envp[i], 5))
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

int	free_path_and_return(char **pathes, char **ret, int error)
{
	ft_free_tab((void **)pathes);
	ft_free_tab((void **)ret);
	return (error);
}

int	init_pipex(t_pipex *pipex, int ac, char **av, char **envp)
{
	ft_memset(pipex, 0, sizeof(t_pipex));
	if (ac < 5)
		return (free_and_return(pipex, NULL, 1, ERR_TOO_FEW_ARG));
	pipex->here_doc = (ft_strcmp("here_doc", av[1]) == 0);
	if (pipex->here_doc)
		pipex->delim = av[2];
	else
		pipex->infile = av[1];
	pipex->outfile = av[ac - 1];
	if (open_files(pipex))
		return (free_and_return(pipex, NULL, 1, -2));
	pipex->envp = envp;
	if (pipex->here_doc && ac < 6)
		return (free_and_return(pipex, NULL, 1, ERR_TOO_FEW_ARG));
	if (fill_cmd_list(ac, av, pipex))
		return (free_and_return(pipex, NULL, 1, ERR_MALLOC));
	return (0);
}

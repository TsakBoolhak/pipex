/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 21:43:40 by acabiac           #+#    #+#             */
/*   Updated: 2021/10/18 19:22:16 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex_bonus.h"
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

void	put_error(t_error errcode)
{
	static char	*err_msg[] = {"Memory allocation failed",
		"Too few argument given to the program"};

	if (errcode == PERROR)
		perror(NULL);
	else
		ft_putendl_fd(err_msg[errcode], 1);
}

int	fill_cmd_list(int ac, char **av, t_pipex *pipex)
{
	int		i;
	t_list	*node;

	i = 2 + pipex->here_doc;
	while (i < ac - 1)
	{
		node = ft_lstnew(av[i]);
		if (!node)
		{
			ft_lstclear(&(pipex->cmdlist), NULL);
			return (1);
		}
		ft_lstadd_back(&(pipex->cmdlist), node);
		i++;
	}
	return (0);
}

int	free_and_return(t_pipex *pipex, int ret, t_error errcode)
{
	ft_lstclear(&(pipex->cmdlist), NULL);
	if ((pipex->pfd)[0] > 2)
		close((pipex->pfd)[0]);
	if ((pipex->pfd)[1] > 2)
		close((pipex->pfd)[1]);
	if (errcode > -2)
		put_error(errcode);
	return (ret);
}

void	ft_print_node(void *cmd)
{
	ft_putendl_fd(cmd, 1);
}

int	handle_child(t_pipex *pipex, t_list *node)
{
	if (node == pipex->cmdlist)
	{
		if (pipex->infile)
		{
			ft_putstr_fd("Handling infile: ", 1);
			ft_putendl_fd(pipex->infile, 1);
		}
		else
		{
			ft_putstr_fd("Handling here_doc: delimiter is : ", 1);
			ft_putendl_fd(pipex->delim, 1);
		}
	}
	ft_putstr_fd("Handling cmd: ", 1);
	ft_putendl_fd((char *)(node->content), 1);
	if (!(node->next))
	{
		ft_putstr_fd("Handling outfile: ", 1);
		ft_putendl_fd(pipex->outfile, 1);
	}
	close((pipex->pfd)[0]);
	close((pipex->pfd)[1]);
	return (0);
}

int	main_loop(t_pipex *pipex)
{
	int	pid1;
	t_list	*node;

	node = pipex->cmdlist;
	while (node)
	{
		if (pipe(pipex->pfd) == -1)
			return (free_and_return(pipex, 1, PERROR));
		pid1 = fork();
		if (pid1 == -1)
			return (free_and_return(pipex, 1, PERROR));
		else if (!pid1)
			return (handle_child(pipex, node));
		close((pipex->pfd)[0]);
		close((pipex->pfd)[1]);
		node = node->next;
	}
	return (0);
}

int	init_pipex(t_pipex *pipex, int ac, char **av, char **envp)
{
	ft_memset(pipex, 0, sizeof(t_pipex));
	if (ac < 5)
		return (free_and_return(pipex, 1, ERR_TOO_FEW_ARG));
	pipex->here_doc = (ft_strcmp("here_doc", av[1]) == 0);
	if (pipex->here_doc)
		pipex->delim = av[2];
	else
		pipex->infile = av[1];
	pipex->outfile = av[ac - 1];
	pipex->envp = envp;
	if (pipex->here_doc && ac < 6)
		return (free_and_return(pipex, 1, ERR_TOO_FEW_ARG));
	if (fill_cmd_list(ac, av, pipex))
		return (free_and_return(pipex, 1, ERR_MALLOC));
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;

	if (init_pipex(&pipex, ac, av, envp))
		return (1);
	main_loop(&pipex);
	while (errno != ECHILD)
		wait(NULL);
	return (free_and_return(&pipex, 1, -2));
}

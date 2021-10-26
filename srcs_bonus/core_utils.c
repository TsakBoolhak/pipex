/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 00:02:09 by acabiac           #+#    #+#             */
/*   Updated: 2021/10/27 00:08:35 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <unistd.h>

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

int	handle_redirections(t_pipex *pipex, int *pfd, t_list *node)
{
	if (node != pipex->cmdlist)
	{
		if (dup2(pipex->pfd[0], STDIN_FILENO) == -1)
			return (free_and_return(pipex, pfd, 1, PERROR));
		close((pipex->pfd)[0]);
		close((pipex->pfd)[1]);
	}
	else
	{
		if (dup2(pipex->fd[0], STDIN_FILENO) == -1)
			return (free_and_return(pipex, pfd, 1, PERROR));
	}
	if (node->next)
	{
		if (dup2(pfd[1], STDOUT_FILENO) == -1)
			return (free_and_return(pipex, pfd, 1, PERROR));
	}
	else
	{
		if (dup2(pipex->fd[1], STDOUT_FILENO) == -1)
			return (free_and_return(pipex, pfd, 1, PERROR));
	}
	return (0);
}

int	handle_child(t_pipex *pipex, int *pfd, t_list *node)
{
	char	**cmd_av;

	if (handle_redirections(pipex, pfd, node))
		return (1);
	close(pfd[0]);
	close(pfd[1]);
	cmd_av = get_cmd_path(pipex->envp, node->content);
	if (cmd_av == NULL)
		return (free_and_return(pipex, NULL, 1, -2));
	execve(cmd_av[0], cmd_av, pipex->envp);
	return (free_and_return(pipex, NULL, 1, -2));
}

int	main_loop(t_pipex *pipex)
{
	int		pid;
	int		pfd[2];
	t_list	*node;

	node = pipex->cmdlist;
	while (node)
	{
		if (node->next && pipe(pfd) == -1)
			return (free_and_return(pipex, NULL, 1, PERROR));
		pid = fork();
		if (pid == -1)
			return (free_and_return(pipex, pfd, 1, PERROR));
		else if (!pid)
			return (handle_child(pipex, pfd, node));
		if (node != pipex->cmdlist)
			close((pipex->pfd)[0]);
		if (node != pipex->cmdlist)
			close((pipex->pfd)[1]);
		if (node->next)
			(pipex->pfd)[0] = pfd[0];
		if (node->next)
			(pipex->pfd)[1] = pfd[1];
		node = node->next;
	}
	return (0);
}

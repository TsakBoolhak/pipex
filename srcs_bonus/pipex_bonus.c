/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 21:43:40 by acabiac           #+#    #+#             */
/*   Updated: 2021/10/15 18:05:37 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex_bonus.h"
#include <stdio.h>
#include <errno.h>

void	put_error(t_error errcode)
{
	static char *err_msg[] = {"Memory allocation failed" , "Too few argument given to the program"};

	if (errcode == PERROR)
		perror(NULL);
	else
		ft_putendl_fd(err_msg[errcode], 1);
}

int	fill_cmd_list(int ac, char **av, t_pipex *pipex)
{
	int		i;
	int		here;
	t_list	*node;

	here = (ft_strcmp("here_doc", av[1]) == 0);
	if (here)
		pipex->delim = av[2];
	i = 2 + here;
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
	if (errcode > -2)
		put_error(errcode);
	return (ret);
}

void	ft_print_node(void *cmd)
{
	ft_putendl_fd(cmd, 1);
}

int	main(int ac, char *av[], char *envp[])
{
	t_pipex	pipex;

	ft_memset(&pipex, 0, sizeof(t_pipex));
	if (ac < 5 || (!ft_strcmp("here_doc", av[1]) && ac < 6))
		return (free_and_return(&pipex, 1, ERR_TOO_FEW_ARG));
	if (fill_cmd_list(ac, av, &pipex))
		return (free_and_return(&pipex, 1, ERR_MALLOC));
	ft_lstiter(pipex.cmdlist, &ft_print_node);
	if (envp)
		return (free_and_return(&pipex, 1, -2));
	return (free_and_return(&pipex, 1, -2));
}

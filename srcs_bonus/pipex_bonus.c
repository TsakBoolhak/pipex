/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 21:43:40 by acabiac           #+#    #+#             */
/*   Updated: 2021/10/14 22:45:48 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex_bonus.h"

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

void	ft_print_node(void *cmd)
{
	ft_putendl_fd(cmd, 1);
}

int	main(int ac, char *av[], char *envp[])
{
	t_pipex	pipex;

	ft_memset(&pipex, 0, sizeof(t_pipex));
	if (ac < 5 || (!ft_strcmp("here_doc", av[1]) && ac < 6))
		return (1);
	if (fill_cmd_list(ac, av, &pipex))
		return (1);
	ft_lstiter(pipex.cmdlist, &ft_print_node);
	ft_lstclear(&(pipex.cmdlist), NULL);
	if (envp)
		return (0);
	return (0);
}

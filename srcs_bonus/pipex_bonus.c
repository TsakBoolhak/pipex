/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 21:43:40 by acabiac           #+#    #+#             */
/*   Updated: 2021/10/20 22:48:55 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex_bonus.h"
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>

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

int	free_and_return(t_pipex *pipex, int *pfd, int ret, t_error errcode)
{
	ft_lstclear(&(pipex->cmdlist), NULL);
	if (pfd)
	{
		close(pfd[0]);
		close(pfd[1]);
	}
	if ((pipex->pfd)[0] > 2)
		close((pipex->pfd)[0]);
	if ((pipex->pfd)[1] > 2)
		close((pipex->pfd)[1]);
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

char	**handle_absolute(char ***pathes, char ***ret)
{
	ft_free_tab((void **)*pathes);
	if (!access((*ret)[0], X_OK))
		return (*ret);
	perror(NULL);
	ft_free_tab((void **)*ret);
	return (NULL);
}

char	**handle_relative(char ***pathes, char ***ret)
{
	char	*tmp;

	ft_free_tab((void **)*pathes);
	tmp = ft_strjoin("./", (*ret)[0]);
	if (!tmp)
	{
		perror(NULL);
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
	perror(NULL);
	ft_free_tab((void **)*ret);
	return (NULL);
}

int	free_path_and_return(char **pathes, char **ret, int error)
{
	ft_free_tab((void **)pathes);
	ft_free_tab((void **)ret);
	return (error);
}

int	check_path(char **path, char **ret, char ***pathes)
{
	char	*tmp;

	tmp = ft_strjoin(*path, "/");
	if (!tmp)
		return (free_path_and_return(*pathes, ret, -1));
	free(*path);
	*path = tmp;
	tmp = ft_strjoin(*path, *ret);
	if (!tmp)
		return (free_path_and_return(*pathes, ret, -1));
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
		{
			perror(NULL);
			return (-1);
		}
		else if (!check)
			return (0);
		i++;
	}
	ft_free_tab((void **)*pathes);
	perror(NULL);
	ft_free_tab((void **)*ret);
	return (-1);
}

char	**get_cmd_path(char *const envp[], char *cmd)
{
	char	**ret;
	char	**pathes;

	if (!cmd || !*cmd)
		return (NULL);
	if (init_pathes(cmd, (char **)envp, &ret, &pathes))
	{
		perror(NULL);
		return (NULL);
	}
	if (ret[0][0] == '/')
		return (handle_absolute(&pathes, &ret));
	else if (ft_strchr(ret[0], '/'))
		return (handle_relative(&pathes, &ret));
	else if (check_pathes(&ret, &pathes))
		return (NULL);
	else
		return (ret);
}

/*int	handle_child(t_pipex *pipex, int *pfd, t_list *node)
{
	int		fd;
	char	**cmd_av;

	ft_putendl_fd(node->content, 2);
	if (node == pipex->cmdlist)
	{
		if (pipex->here_doc)
		{
			ft_putstr_fd("Handling here_doc: delimiter is : ", 1);
			ft_putendl_fd(pipex->delim, 1);
		}
		else
		{
//			close(pfd[0]);
//			pfd[0] = 0;
			fd = open(pipex->infile, O_RDONLY);
			if (fd == -1)
				return (1);
				//return (free_and_return(pipex, pfd, 1, PERROR));
			else if (dup2(fd, STDIN_FILENO) == -1)
				return (1);
				//return (free_and_return(pipex, pfd, 1, PERROR));
//			close(fd);
		}
	}
	else
	{
//		close(pfd[0]);
//		pfd[0] = 0;
		if (dup2(pipex->pfd[1], STDIN_FILENO) == -1)
			return (1);
		//	return (free_and_return(pipex, pfd, 1, PERROR));
		// recup ancienne sortie pr la rediriger en entrée 
	}
	if (node->next)
	{
//		if (pipex->pfd[1])
//			close(pipex->pfd[1]);
		pipex->pfd[1] = pfd[1];
		if (dup2(pfd[1], STDOUT_FILENO) == -1)
			return (1);
		//	return (free_and_return(pipex, pfd, 1, PERROR));
		// stocker la sortie dans la structure
	}
	else
	{
		//gerer le outfile
//		close(pfd[1]);
//		pfd[1] = 0;
		if (pipex->here_doc)
		{
		}
		else
		{
			fd = open(pipex->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0664);
			if (fd == -1)
				return (1);
				//return (free_and_return(pipex, pfd, 1, PERROR));
			if (dup2(fd, STDOUT_FILENO) == -1)
			{
//				close(fd);
				return (1);
				//return (free_and_return(pipex, pfd, 1, PERROR));
			}
//			close(fd);
		}
	}
	cmd_av = get_cmd_path(pipex->envp, node->content);
	execve(cmd_av[0], cmd_av, pipex->envp);
	//exec la cmd
	return (1);
//	return (free_and_return(pipex, NULL, 1, PERROR));
}*/

int	handle_child(t_pipex *pipex, int *pfd, t_list *node)
{
	int		fd;
	char	**cmd_av;

	if (node != pipex->cmdlist)
	{
		if (dup2(pipex->pfd[0], STDIN_FILENO) == -1)
		{
			close(pfd[0]);
			close(pfd[1]);
			return (1); // gerer les fermeture de fd en cas derreur
		}
		close((pipex->pfd)[0]);
		close((pipex->pfd)[1]);
	}
	else
	{
		if (pipex->here_doc)
		{
			ft_putstr_fd("Handling here_doc: delimiter is : ", 2);
			ft_putendl_fd(pipex->delim, 2);
		}
		else
		{
			fd = open(pipex->infile, O_RDONLY);
			if (fd == -1)
			{
				close(pfd[0]);
				close(pfd[1]);
				return (1);
			}
			else if (dup2(fd, STDIN_FILENO) == -1)
			{
				close(fd);
				close(pfd[0]);
				close(pfd[1]);
				return (1);
			}
			close(fd);
		}
	}
	if (node->next)
	{
		close(pfd[0]);
		if (dup2(pfd[1], STDOUT_FILENO) == -1)
		{
			close(pfd[1]);
			return (1); // gerer les fermeture de fd en cas derreur
		}
		close(pfd[1]);
	}
	else
	{
		close(pfd[0]);
		close(pfd[1]);
		if (pipex->here_doc)
		{
		}
		else
		{
			fd = open(pipex->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0664);
		}
		if (fd == -1)
		{
			return (1);
			//return (free_and_return(pipex, pfd, 1, PERROR));
		}
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			close(fd);
			return (1);
			//return (free_and_return(pipex, pfd, 1, PERROR));
		}
		close(fd);
	 //gerer outfile
	}
	cmd_av = get_cmd_path(pipex->envp, node->content);
	execve(cmd_av[0], cmd_av, pipex->envp);
	//exec la cmd
	return (1);
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
			return (1);
		//	return (free_and_return(pipex, NULL, 1, PERROR));
		pid = fork();
		if (pid == -1)
			return (1);
	//		return (free_and_return(pipex, pfd, 1, PERROR));
		else if (!pid)
	//		return (1);
			return (handle_child(pipex, pfd, node));
		if (node != pipex->cmdlist)
		{
			close((pipex->pfd)[0]);
			close((pipex->pfd)[1]);
		}
		if (node->next)
		{
			(pipex->pfd)[0] = pfd[0];
			(pipex->pfd)[1] = pfd[1];
		}
		node = node->next;
	}
	return (0);
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
	pipex->envp = envp;
	if (pipex->here_doc && ac < 6)
		return (free_and_return(pipex, NULL, 1, ERR_TOO_FEW_ARG));
	if (fill_cmd_list(ac, av, pipex))
		return (free_and_return(pipex, NULL, 1, ERR_MALLOC));
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
	return (free_and_return(&pipex, NULL, 1, -2));
}

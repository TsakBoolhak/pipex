/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 21:43:40 by acabiac           #+#    #+#             */
/*   Updated: 2021/10/26 14:47:16 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	clear_gnl_and_line(char **line)
{
	get_next_line(0, NULL, 2);
	free(*line);
	*line = NULL;
}

int	heredoc_filling_loop(t_pipex *pipex)
{
	int		ret;
	char	*line;

	ft_putstr_fd("heredoc> ", 1);
	while (1)
	{
		ret = get_next_line(0, &line, 0);
		if (ret == -1)
			return (free_and_return(pipex, NULL, 1, ERR_MALLOC));
		else if (!ret)
			continue ;
		if (!ft_strcmp(line, pipex->delim))
		{
			clear_gnl_and_line(&line);
			return (0);
		}
		if (ft_putendl_fd(line, pipex->fd[0]) == -1)
		{
			clear_gnl_and_line(&line);
			return (free_and_return(pipex, NULL, 1, PERROR));
		}
		clear_gnl_and_line(&line);
		ft_putstr_fd("heredoc> ", 1);
	}
	return (free_and_return(pipex, NULL, 1, PERROR));
}

int	handle_heredoc(t_pipex *pipex)
{
	pipex->fd[0] = open(".here_doc_tmp", O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (pipex->fd[0] == -1)
		return (free_and_return(pipex, NULL, 1, PERROR));
	else if (heredoc_filling_loop(pipex))
		return (1);
	close(pipex->fd[0]);
	pipex->fd[0] = open(".here_doc_tmp", O_RDONLY);
	if (pipex->fd[0] == -1)
		return (free_and_return(pipex, NULL, 1, PERROR));
	pipex->fd[1] = open(pipex->outfile, O_WRONLY | O_CREAT | O_APPEND, 0664);
	return (0);
}

int	open_files(t_pipex *pipex)
{
	if (pipex->here_doc && handle_heredoc(pipex))
		return (1);
	else if (!pipex->here_doc)
	{
		pipex->fd[0] = open(pipex->infile, O_RDONLY);
		if (pipex->fd[0] == -1)
			return (free_and_return(pipex, NULL, 1, PERROR));
		pipex->fd[1] = open(pipex->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	}
	if (pipex->fd[1] == -1)
		return (free_and_return(pipex, NULL, 1, PERROR));
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
	if (open_files(pipex))
		return (free_and_return(pipex, NULL, 1, -2));
	pipex->envp = envp;
	if (pipex->here_doc && ac < 6)
		return (free_and_return(pipex, NULL, 1, -2));
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

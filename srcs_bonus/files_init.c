/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 22:54:10 by acabiac           #+#    #+#             */
/*   Updated: 2021/10/26 23:03:07 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

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

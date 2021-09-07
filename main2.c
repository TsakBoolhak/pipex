/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 18:22:22 by acabiac           #+#    #+#             */
/*   Updated: 2021/09/07 21:28:59 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	if (n == 0)
		return (0);
	i = 0;
	str1 = (unsigned char *)(s1);
	str2 = (unsigned char *)(s2);
	while (i < n - 1 && *str1 && *str2 && *str1 == *str2)
	{
		i++;
		str1++;
		str2++;
	}
	return (*str1 - *str2);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dst_tmp;
	unsigned char	*src_tmp;

	i = 0;
	dst_tmp = (unsigned char *)dst;
	src_tmp = (unsigned char *)src;
	while (i < n)
	{
		dst_tmp[i] = src_tmp[i];
		i++;
	}
	return (dst);
}

char	*ft_strndup(const char *src, size_t len)
{
	char	*dst;

	if (len > ft_strlen(src))
		len = ft_strlen(src);
	dst = (char *)malloc(sizeof(*dst) * (len + 1));
	if (!dst)
		return (NULL);
	ft_memcpy(dst, src, len);
	dst[len] = '\0';
	return (dst);
}

char	*ft_strdup(const char *src)
{
	return (ft_strndup(src, ft_strlen(src)));
}

char	*ft_strjoin(char const *src, char const *to_append)
{
	char	*dst;
	size_t	len_src;
	size_t	len_to_append;

	if (!src && !to_append)
		return (NULL);
	else if (!src)
		return (ft_strdup(to_append));
	else if (!to_append)
		return (ft_strdup(src));
	len_src = ft_strlen(src);
	len_to_append = ft_strlen(to_append);
	dst = (char *)malloc(sizeof(*dst) * (len_src + len_to_append + 1));
	if (!dst)
		return (NULL);
	ft_memcpy(dst, src, len_src);
	ft_memcpy(dst + len_src, to_append, len_to_append + 1);
	return (dst);
}

void	*ft_free_tab(void **tab)
{
	size_t	i;

	if (!tab)
		return (NULL);
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

static size_t	ft_count_words(char const *s, char sep)
{
	size_t	i;
	size_t	words_count;

	i = 0;
	words_count = 0;
	while (s[i])
	{
		while (s[i] == sep)
			i++;
		if (s[i])
			words_count++;
		while (s[i] && s[i] != sep)
			i++;
	}
	return (words_count);
}

static size_t	ft_count_letters(char const *s, char sep)
{
	size_t	count;

	count = 0;
	while (s[count] && s[count] != sep)
		count++;
	return (count);
}

static char	*ft_alloc_word(char const *s, char c, size_t word)
{
	size_t	i;
	size_t	j;
	char	*result;

	i = 0;
	j = 0;
	while (j < word)
	{
		while (s[i] == c)
			i++;
		j++;
		while (s[i] && s[i] != c)
			i++;
	}
	j = 0;
	while (s[i] == c)
		i++;
	result = (char *)malloc(ft_count_letters(s + i, c) + 1);
	if (!result)
		return (NULL);
	while (s[i] && s[i] != c)
		result[j++] = s[i++];
	result[j] = '\0';
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	size_t	words_count;
	size_t	i;

	words_count = ft_count_words(s, c);
	result = (char **)malloc(sizeof(*result) * (words_count + 1));
	if (!result)
		return (NULL);
	result[words_count] = NULL;
	i = 0;
	while (i < words_count)
	{
		result[i] = ft_alloc_word(s, c, i);
		if (!result[i])
			return (ft_free_tab((void **)result));
		i++;
	}
	return (result);
}

int	init_pathes(char *cmd, char **envp, char ***ret, char ***pathes)
{
	int	i;

	*pathes = NULL;
	*ret = ft_split(cmd, ' ');
	if (*ret == NULL)
		return (1);
	i = 0;
	while (envp[i] && ft_strncmp("PATH", envp[i], 4))
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

int	free_and_return(char **pathes, char **ret, int error)
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
		return (free_and_return(*pathes, ret, -1));
	free(*path);
	*path = tmp;
	tmp = ft_strjoin(*path, *ret);
	if (!tmp)
		return (free_and_return(*pathes, ret, -1));
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

char	**get_cmd1(char *const av[], char *const envp[])
{
	char	**ret;
	char	**pathes;
	int		i;
	int		check;

	if (init_pathes((char *)av[2], (char **)envp, &ret, &pathes))
		return (NULL);
	i = 0;
	while (pathes && pathes[i])
	{
		check = check_path(&pathes[i], &ret[0], &pathes);
		if (check == -1)
			return (NULL);
		else if (!check)
			return (ret);
		i++;
	}
	ft_free_tab((void **)pathes);
	if (!access(ret[0], X_OK))
		return (ret);
	write(2, av[0], ft_strlen(av[0]));
	write(2, ": ", 2);
	perror(ret[0]);
	ft_free_tab((void **)ret);
	return (NULL);
}

char	**get_cmd2(char *const av[], char *const envp[])
{
	char	**ret;
	char	**pathes;
	int		i;
	int		check;

	if (init_pathes((char *)av[3], (char **)envp, &ret, &pathes))
		return (NULL);
	i = 0;
	while (pathes && pathes[i])
	{
		check = check_path(&pathes[i], &ret[0], &pathes);
		if (check == -1)
			return (NULL);
		else if (!check)
			return (ret);
		i++;
	}
	ft_free_tab((void **)pathes);
	if (!access(ret[0], X_OK))
		return (ret);
	write(2, av[0], ft_strlen(av[0]));
	write(2, ": ", 2);
	perror(ret[0]);
	ft_free_tab((void **)ret);
	return (NULL);
}

int	left_side(int pfd[2], char *const av[], char *const envp[])
{
	char	**cmd_av;
	int		fd;

	fd = open(av[1], O_RDONLY);
	close(pfd[0]);
	if (fd == -1)
	{
		write(2, av[0], ft_strlen(av[0]));
		write(2, ": ", 2);
		perror(av[1]);
		close(pfd[1]);
		return (5);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror(av[0]);
		close(pfd[1]);
		return (6);
	}
	if (dup2(pfd[1], STDOUT_FILENO) == -1)
	{
		perror(av[0]);
		close(pfd[1]);
		return (7);
	}
	close(fd);
	cmd_av = get_cmd1(av, envp);
	if (!cmd_av)
	{
		close(pfd[1]);
		return (8);
	}
	execve(cmd_av[0], cmd_av, envp);
	perror(av[0]);
	close(pfd[1]);
	ft_free_tab((void **)cmd_av);
	return (9);
}

int	right_side(int pfd[2], char *const av[], char *const envp[])
{
	char	**cmd_av;
	int		fd;

	close(pfd[1]);
	fd = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd == -1)
	{
		write(2, av[0], ft_strlen(av[0]));
		write(2, ": ", 2);
		perror(av[4]);
		close(pfd[0]);
		return (10);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror(av[0]);
		close(pfd[0]);
		return (11);
	}
	if (dup2(pfd[0], STDIN_FILENO) == -1)
	{
		perror(av[0]);
		close(pfd[0]);
		return (12);
	}
	close(fd);
	cmd_av = get_cmd2(av, envp);
	if (!cmd_av)
	{
		close(pfd[0]);
		return (13);
	}
	execve(cmd_av[0], cmd_av, envp);
	perror(av[0]);
	close(pfd[0]);
	ft_free_tab((void **)cmd_av);
	return (14);
}

int	main(int ac, char *const av[], char *const envp[])
{
	int	pfd[2];
	int	pid1;
	int	pid2;
	int	ret;

	if (ac != 5)
		return (1);
	else if (pipe(pfd) == -1)
	{
		perror(av[0]);
		return (2);
	}
	pid1 = fork();
	if (pid1 == -1)
	{
		perror(av[0]);
		close(pfd[0]);
		close(pfd[1]);
		return (3);
	}
	else if (!pid1)
		return (left_side(pfd, av, envp));
	else
	{
		pid2 = fork();
		if (pid2 == -1)
		{
			perror(av[0]);
			close(pfd[0]);
			close(pfd[1]);
			return (4);
		}
		else if (!pid2)
			return (right_side(pfd, av, envp));
		else
		{
			close(pfd[0]);
			close(pfd[1]);
			ret = 1;
			while (ret > 0)
			{
				ret = wait(NULL);
			}
			return (0);
		}
	}
}

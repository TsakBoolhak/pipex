/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 21:40:15 by acabiac           #+#    #+#             */
/*   Updated: 2021/10/26 14:09:11 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# define BUFFER_SIZE 4096
# include <stddef.h>

typedef enum e_error
{
	PERROR = -1,
	ERR_MALLOC,
	ERR_TOO_FEW_ARG
}t_error;

typedef struct s_gnl
{
	int		fd;
	char	remainder[BUFFER_SIZE + 1];
}t_gnl;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}t_list;

typedef struct s_pipex
{
	t_list	*cmdlist;
	int		here_doc;
	int		pfd[2];
	int		fd[2];
	char	*delim;
	char	*infile;
	char	*outfile;
	char	**envp;
}t_pipex;

char	*ft_strjoin(char const *src, char const *to_append);
char	*ft_strchr(const char *s, int c);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
int		ft_putchar_fd(char c, int fd);
int		ft_putstr_fd(char *s, int fd);
int		ft_putendl_fd(char *s, int fd);
void	*ft_memset(void *b, int c, size_t len);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_strdup(const char *src);
char	*ft_strndup(const char *src, size_t len);
char	**ft_split(char const *s, char c);
void	*ft_free_tab(void **tab);

int		get_next_line(int fd, char **line, int stop);
int		handle_stop(int fd, int stop, t_list **lst);
t_list	*set_fd_lst(int fd, t_list **lst);

void	ft_lstclear(t_list **alst, void (*del)(void *));
t_list	*ft_lstnew(void *content);
void	ft_lstadd_back(t_list **alst, t_list *new);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstdelone(t_list **alst, t_list *to_del, void (*del)(void *));

#endif

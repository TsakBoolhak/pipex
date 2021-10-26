/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 21:40:15 by acabiac           #+#    #+#             */
/*   Updated: 2021/10/27 00:03:53 by acabiac          ###   ########.fr       */
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

/*
** basic functions
*/
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

/*
** get next line
*/
int		get_next_line(int fd, char **line, int stop);
int		handle_stop(int fd, int stop, t_list **lst);
t_list	*set_fd_lst(int fd, t_list **lst);

/*
** linked list functions
*/
void	ft_lstclear(t_list **alst, void (*del)(void *));
t_list	*ft_lstnew(void *content);
void	ft_lstadd_back(t_list **alst, t_list *new);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstdelone(t_list **alst, t_list *to_del, void (*del)(void *));

/*
** files_init.c
*/
int		open_files(t_pipex *pipex);
void	clear_gnl_and_line(char **line);
int		heredoc_filling_loop(t_pipex *pipex);
int		handle_heredoc(t_pipex *pipex);

/*
** set_cmd_path.c
*/
char	**handle_absolute(char ***pathes, char ***ret);
char	**handle_relative(char ***pathes, char ***ret);
int		check_path(char **path, char **ret, char ***pathes);
int		check_pathes(char ***ret, char ***pathes);
char	**get_cmd_path(char *const envp[], char *cmd);

/*
** init_and_free.c
*/
void	put_error(t_error errcode);
int		free_and_return(t_pipex *pipex, int *pfd, int ret, t_error errcode);
int		init_pathes(char *cmd, char **envp, char ***ret, char ***pathes);
int		free_path_and_return(char **pathes, char **ret, int error);
int		init_pipex(t_pipex *pipex, int ac, char **av, char **envp);

/*
** core_utils.c
*/
int		fill_cmd_list(int ac, char **av, t_pipex *pipex);
int		handle_redirections(t_pipex *pipex, int *pfd, t_list *node);
int		handle_child(t_pipex *pipex, int *pfd, t_list *node);
int		main_loop(t_pipex *pipex);

#endif

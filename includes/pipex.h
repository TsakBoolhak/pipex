/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 21:44:27 by acabiac           #+#    #+#             */
/*   Updated: 2021/10/02 02:58:42 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/*
** ft_split.c
*/
char	**ft_split(char const *s, char c);
void	*ft_free_tab(void **tab);

/*
** basic_tools.c
*/
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_strdup(const char *src);
char	*ft_strjoin(char const *src, char const *to_append);

/*
** basic_tools2.c
*/
char	*ft_strchr(const char *s, int c);

/*
** pipex_tools.c
*/
int		init_pathes(char *cmd, char **envp, char ***ret, char ***pathes);
int		free_and_return(char **pathes, char **ret, int error);
int		check_pathes(char *name, char ***ret, char ***pathes);
int		check_path(char **path, char **ret, char ***pathes);
int		close_and_print_error(char *str, int fd1, int fd2, int error);

/*
** pipex_tools2.c
*/
char	**handle_absolute(char ***pathes, char ***ret, char *const av[]);
char	**handle_relative(char ***pathes, char ***ret, char *const av[]);
char	**get_cmd_path(char *const av[], char *const envp[], char *cmd);
int		left_side(int pfd[2], char *const av[], char *const envp[]);
int		right_side(int pfd[2], char *const av[], char *const envp[]);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 21:44:27 by acabiac           #+#    #+#             */
/*   Updated: 2021/09/08 22:32:47 by acabiac          ###   ########.fr       */
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
** pipex_tools.c
*/
int		init_pathes(char *cmd, char **envp, char ***ret, char ***pathes);
int		free_and_return(char **pathes, char **ret, int error);
int		check_path(char **path, char **ret, char ***pathes);
int		close_and_print_error(char *str, int fd1, int fd2, int error);

#endif

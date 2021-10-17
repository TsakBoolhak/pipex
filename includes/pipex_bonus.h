/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 21:40:15 by acabiac           #+#    #+#             */
/*   Updated: 2021/10/17 13:44:42 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

typedef enum e_error
{
	PERROR = -1,
	ERR_MALLOC,
	ERR_TOO_FEW_ARG
}	t_error;

typedef struct s_pipex
{
	t_list	*cmdlist;
	char	*delim;
}t_pipex;

#endif

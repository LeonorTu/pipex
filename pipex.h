/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:50:55 by jtu               #+#    #+#             */
/*   Updated: 2024/03/04 14:22:57 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include "libft/libft.h"
# include "libft/ft_printf/ft_printf.h"

typedef enum s_error
{
	NO_ERROR,
	WRONG_ARGC,
	PIPE_FAIL,
	FORK_FAIL,
	OPEN_FAIL,
	WRONG_FILE,
	CMD_NOT_FOUND,
	NO_PATH,
	NO_PERMISSION,
	EXECVE_FAIL
}	t_error;

typedef struct s_pipex
{
	int	fd[2];
	// int	fd_in;
	// int	fd_out;
	int	status;
	int	exit_code;
	char	*cmd;
	pid_t	pid1;
	pid_t	pid2;
}	t_pipex;

#endif
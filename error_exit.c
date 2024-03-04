/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:15:25 by jtu               #+#    #+#             */
/*   Updated: 2024/03/04 15:16:58 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_exit(t_error error, char *s)
{
	ft_putstr_fd("pipex: ", STDERR_FILENO);
	if (error == CMD_NOT_FOUND)
	{
		ft_putstr_fd("command not found: ", STDERR_FILENO);
		if (!s)
			s = "\n";
		ft_putendl_fd(s, STDERR_FILENO);
		exit(127);
	}
	if (error == NO_PATH)
	{
		ft_putstr_fd("No such file or directory: ", STDERR_FILENO);
		ft_putendl_fd(s, STDERR_FILENO);
		exit(127);
	}
	if (error == EXECVE_FAIL)
	{
		ft_putstr_fd("permission denied: ", STDERR_FILENO);
		if (!s)
			s = "\n";
		ft_putendl_fd(s, STDERR_FILENO);
		exit(126);
	}
	perror(s);
	exit(EXIT_FAILURE);
}

void	get_exit_code(t_pipex *pipex)
{
	if (WIFEXITED(pipex->status))
		pipex->exit_code = WEXITSTATUS(pipex->status);
	else if (WIFSIGNALED(pipex->status))
		pipex->exit_code = WTERMSIG(pipex->status);
}

void	free_arr(char **arr)
{
	while (*arr)
		free(*arr++);
}

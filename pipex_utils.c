/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:15:25 by jtu               #+#    #+#             */
/*   Updated: 2024/03/05 15:27:27 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_pipex(t_pipex *pipex)
{
	pipex->fd[0] = 0;
	pipex->fd[1] = 0;
	pipex->status = 0;
	pipex->exit_code = 0;
	pipex->cmd = NULL;
	pipex->pid1 = 0;
	pipex->pid2 = 0;
}

void	error_exit(t_error error, char *s)
{
	ft_putstr_fd("pipex: ", STDERR_FILENO);
	if (error == CMD_NOT_FOUND)
	{
		ft_putendl_fd("command not found: ", STDERR_FILENO);
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

void	error_free_exit(char **cmd)
{
	ft_putstr_fd("pipex: ", STDERR_FILENO);
	ft_putstr_fd("command not found: ", STDERR_FILENO);
	ft_putendl_fd(*cmd, STDERR_FILENO);
	free_arr(cmd);
	exit(127);
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
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

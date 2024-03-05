/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:37:34 by jtu               #+#    #+#             */
/*   Updated: 2024/03/05 12:49:53 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;

	if (argc != 5)
		error_exit(WRONG_ARGC, "Please enter 4 arguments. \
Ex: ./pipex <infile> <cmd1> <cmd2> <outfile>\n");
	pipex = (t_pipex *)ft_calloc(0, sizeof(t_pipex));
	if (!pipex)
		error_exit(NO_INFILE, NULL);
	if (pipe(pipex->fd) == -1)
		error_exit(PIPE_FAIL, NULL);
	pipex->pid1 = fork();
	if (pipex->pid1 < 0)
		error_exit(FORK_FAIL, NULL);
	if (pipex->pid1 == 0)
		child1_process(argv, envp, pipex);
	close(pipex->fd[1]);
	pipex->pid2 = fork();
	if (pipex->pid2 < 0)
		error_exit(FORK_FAIL, NULL);
	if (pipex->pid2 == 0)
		child2_process(argv, envp, pipex);
	close(pipex->fd[0]);
	waitpid(pipex->pid1, NULL, 0);
	waitpid(pipex->pid2, &(pipex->status), 0);
	get_exit_code(pipex);
	// system("leaks pipex");
	return (pipex->exit_code);
}

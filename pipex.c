/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:50:37 by jtu               #+#    #+#             */
/*   Updated: 2024/03/05 15:27:17 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*parse_path(char *cmd, char **envp)
{
	char	**path;
	char	*path_cmd;
	char	*temp;
	int		i;

	while (*envp && !ft_strnstr(*envp, "PATH=", 5))
		envp++;
	if (!*envp)
		error_exit(NO_PATH, cmd);
	path = ft_split(*envp + 5, ':');
	i = -1;
	temp = NULL;
	path_cmd = NULL;
	while (path[++i])
	{
		temp = ft_strjoin(path[i], "/");
		path_cmd = ft_strjoin(temp, cmd);
		free(temp);
		if (access(path_cmd, F_OK | X_OK) == 0)
			return (path_cmd);
		free(path_cmd);
	}
	free_arr(path);
	return (0);
}

void	execute_cmd(char *argv, char **envp)
{
	char	**cmd;
	char	*path;

	if (!argv)
		error_exit(EXECVE_FAIL, argv);
	cmd = ft_split(argv, ' ');
	if (!cmd[0])
		error_exit(CMD_NOT_FOUND, NULL);
	if (!ft_strrchr(cmd[0], '/'))
		path = parse_path(cmd[0], envp);
	else
	{
		if (access(cmd[0], F_OK) != 0)
			error_exit(NO_PATH, cmd[0]);
		if (access(cmd[0], X_OK) != 0)
			error_exit(EXECVE_FAIL, cmd[0]);
		path = cmd[0];
	}
	if (!path)
		error_free_exit(cmd);
	if (execve(path, cmd, envp) == -1)
		error_exit(EXECVE_FAIL, path);
}

void	child1_process(char **argv, char **envp, t_pipex *pipex)
{
	int	fd_in;

	if (access(argv[1], F_OK) != 0)
		error_exit(WRONG_FILE, argv[1]);
	if (access(argv[1], R_OK) != 0)
		error_exit(NO_PERMISSION, argv[1]);
	fd_in = open(argv[1], O_RDONLY);
	if (fd_in == -1)
		error_exit(OPEN_FAIL, argv[1]);
	dup2(pipex->fd[1], STDOUT_FILENO);
	dup2(fd_in, STDIN_FILENO);
	close(pipex->fd[1]);
	close(fd_in);
	execute_cmd(argv[2], envp);
}

void	child2_process(char **argv, char **envp, t_pipex *pipex)
{
	int	fd_out;

	fd_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out == -1)
		error_exit(OPEN_FAIL, argv[4]);
	dup2(pipex->fd[0], STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close(pipex->fd[0]);
	close(fd_out);
	execute_cmd(argv[3], envp);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc != 5)
		error_exit(WRONG_ARGC, "Please enter 4 arguments");
	init_pipex(&pipex);
	if (pipe(pipex.fd) == -1)
		error_exit(PIPE_FAIL, NULL);
	pipex.pid1 = fork();
	if (pipex.pid1 < 0)
		error_exit(FORK_FAIL, NULL);
	if (pipex.pid1 == 0)
		child1_process(argv, envp, &pipex);
	close(pipex.fd[1]);
	pipex.pid2 = fork();
	if (pipex.pid2 < 0)
		error_exit(FORK_FAIL, NULL);
	if (pipex.pid2 == 0)
		child2_process(argv, envp, &pipex);
	close(pipex.fd[0]);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, &(pipex.status), 0);
	get_exit_code(&pipex);
	return (pipex.exit_code);
}

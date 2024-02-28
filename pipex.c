/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:50:37 by jtu               #+#    #+#             */
/*   Updated: 2024/02/28 20:09:54 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_exit(void)
{
	perror("Error");
	exit(EXIT_FAILURE);
}

void	free_arr(char **arr)
{
	while (*arr)
		free(*arr++);
	// free(arr);
}

char	*parse_path(char *cmd, char **envp)
{
	char	**path;
	char	*path_cmd;
	char	*temp;
	int		i;

	while (!ft_strnstr(*envp, "PATH=", 5))
		envp++;
	path = ft_split(*envp + 5, ':');
	i = 0;
	temp = NULL;
	path_cmd = NULL;
	while (path[i])
	{
		temp = ft_strjoin(path[i], "/");
		path_cmd = ft_strjoin(temp, cmd);
		free(temp);
		if (access(path_cmd, F_OK | X_OK) == 0)
			return (path_cmd);
		free(path_cmd);
		i++;
	}
	free_arr(path);
	return (0);
}

void	execute_cmd(char *argv, char **envp)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(argv, ' ');
	// if (!cmd[0] || !cmd[1])
	// 	error_exit();
	path = parse_path(cmd[0], envp);
	if (!path)
	{
		free_arr(cmd);
		error_exit();
	}
	if (execve(path, cmd, envp) == -1)
		error_exit();
}

void	child_process(char **argv, char **envp, int *fd)
{
	int	fd_in;

	fd_in = open(argv[1], O_RDONLY);
	if (fd_in == -1)
		error_exit();
	dup2(fd[1], STDOUT_FILENO);
	dup2(fd_in, STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	execute_cmd(argv[2], envp);
}

void	parent_process(char **argv, char **envp, int *fd)
{
	int	fd_out;

	fd_out = open(argv[4],  O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd_out == -1)
		error_exit();
	dup2(fd[0], STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close(fd[1]);
	close(fd[0]);
	execute_cmd(argv[3], envp);
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid1;
	int	status;

	if (argc != 5)
		error_exit();
	if (pipe(fd) == -1)
		error_exit();
	pid1 = fork();
	if (pid1 < 0)
		error_exit();
	if (pid1 == 0)
		child_process(argv, envp, fd);
	waitpid(pid1, &status, 0);
	parent_process(argv, envp, fd);
	// sleep(100000000);
	system("leaks pipex "); //
	return (EXIT_SUCCESS);
}

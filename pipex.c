/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:50:37 by jtu               #+#    #+#             */
/*   Updated: 2024/02/29 18:07:37 by jtu              ###   ########.fr       */
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
	{
		envp++;
		// if (!*envp)
		// 	error_exit();    //????
	}
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

	if (!ft_strrchr(*cmd, '/'))
	{
		cmd = ft_split(argv, ' ');
		if (!cmd[0])
			error_exit();
		path = parse_path(cmd[0], envp);
	}
	else
		path = argv;
	if (!path)
	{
		free_arr(cmd);
		error_exit();
	}
	if (execve(path, cmd, envp) == -1)
		error_exit();
}

void	child1_process(char **argv, char **envp, int *fd)
{
	int	fd_in;

	// printf("%d\n", getpid());
	// printf("%d\n", getppid());
	fd_in = open(argv[1], O_RDONLY);
	if (fd_in == -1)
		error_exit();
	dup2(fd[1], STDOUT_FILENO);
	dup2(fd_in, STDIN_FILENO);
	close(fd[1]);
	close(fd_in);
	execute_cmd(argv[2], envp);
}

void	child2_process(char **argv, char **envp, int *fd)
{
	int	fd_out;

	fd_out = open(argv[4],  O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd_out == -1)
		error_exit();
	dup2(fd[0], STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close(fd[0]);
	close(fd_out);
	execute_cmd(argv[3], envp);
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;
	int	status1;
	int	status2;
	// int	statuscode;

	if (argc != 5)
		error_exit();
	if (pipe(fd) == -1)
		error_exit();
	pid1 = fork();
	if (pid1 < 0)
		error_exit();
	if (pid1 == 0)
		child1_process(argv, envp, fd);
	close(fd[1]);
	pid2 = fork();
	if (pid2 < 0)
		error_exit();
	if (pid2 == 0)
		child2_process(argv, envp, fd);
	close(fd[0]);
	waitpid(pid1, &status1, 0);
	waitpid(pid2, &status2, 0);
	// statuscode = 1;
	// if (WIFEXITED(status1))
	// 	statuscode = WEXITSTATUS(status1);
	// else if (WIFSIGNALED(status1))
	// 	statuscode = WTERMSIG(status1);
	// else
	// 	statuscode = 1;
	// printf("%d\n", getpid());
	// printf("%d\n", getppid());
	// printf("here");
	// while(1)
	// {
	// }
	// parent_process(argv, envp, fd);
	// sleep(100000000);
	// system("leaks pipex"); //
	return (EXIT_SUCCESS);
}
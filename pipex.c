/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:50:37 by jtu               #+#    #+#             */
/*   Updated: 2024/03/01 19:29:36 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_exit(t_error error, char *s)
{
	if (error == CMD_NOT_FOUND)
	{
		ft_printf("zsh: command not found: ");
		exit(127);
	}
	if (error == EXECVE_FAIL)
	{
		ft_printf("zsh: permission denied: %s\n", s);
		exit(126);
	}
	if (error == OPEN_FAIL)
	{
		ft_printf("Can't open infile");
		exit(0);
	}
	if (error == NO_INFILE)
	{
		ft_printf("zsh: no such file or directory: %s\n", s);
		exit(0);
	}
	if (error == NO_PERMISSION)
	{
		ft_printf("zsh: permission denied: %s\n", s);
		exit(126);
	}
	if (error == OUT_FILE)
	{
		ft_printf("zsh: permission denied: %s\n", s);
		exit(1);
	}
	perror("Error");
	exit(EXIT_FAILURE);
}

void	free_arr(char **arr)
{
	while (*arr)
		free(*arr++);
	// free(arr);
}

char	*parse_path(char *cmd, char **envp, t_pipex *pipex)
{
	char	**path;
	char	*path_cmd;
	char	*temp;
	int		i;

	while (!ft_strnstr(*envp, "PATH=", 5))
	{
		envp++;
		if (!*envp)
			error_exit(CMD_NOT_FOUND, "haha");
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

// void	check_access(char *path_cmd)
// {
// 	if (access(path_cmd, F_OK | X_OK) != 0)
// 		error_exit();
// }

void	execute_cmd(char *argv, char **envp, t_pipex *pipex)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(argv, ' ');
	if (!cmd[0])
		error_exit(CMD_NOT_FOUND, cmd[0]);
	if (!ft_strrchr(cmd[0], '/'))
		path = parse_path(cmd[0], envp, pipex);
	else
	{
		if (access(cmd[0], F_OK | X_OK) != 0)
			error_exit(NO_PERMISSION, cmd[0]);
		path = cmd[0];
	}
	if (!path)
	{
		free_arr(cmd);
		error_exit(CMD_NOT_FOUND, cmd[0]);
	}
	if (execve(path, cmd, envp) == -1)
		error_exit(EXECVE_FAIL, path);
}

void	child1_process(char **argv, char **envp, t_pipex *pipex)
{
	int	fd_in;

	if (access(argv[1], F_OK) != 0)
		error_exit(NO_INFILE, argv[1]);
	if (access(argv[1], R_OK) != 0)
		error_exit(NO_PERMISSION, argv[1]);
	fd_in = open(argv[1], O_RDONLY);
	if (fd_in == -1)
		error_exit(OPEN_FAIL, "haha");
	dup2(pipex->fd[1], STDOUT_FILENO);
	dup2(fd_in, STDIN_FILENO);
	close(pipex->fd[1]);
	close(fd_in);
	execute_cmd(argv[2], envp, pipex);
}

void	child2_process(char **argv, char **envp, t_pipex *pipex)
{
	int	fd_out;

	if (access(argv[4], W_OK) != 0)
		error_exit(OUT_FILE, argv[4]);
	fd_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd_out == -1)
		error_exit(OPEN_FAIL, "haha");
	dup2(pipex->fd[0], STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close(pipex->fd[0]);
	close(fd_out);
	execute_cmd(argv[3], envp, pipex);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;

	pipex = (t_pipex *)ft_calloc(0, sizeof(t_pipex));
	if (argc != 5)
		error_exit(WRONG_ARGC, "haha");
	if (pipe(pipex->fd) == -1)
		error_exit(PIPE_FAIL, "haha");
	pipex->pid1 = fork();
	if (pipex->pid1 < 0)
		error_exit(FORK_FAIL, "haha");
	if (pipex->pid1 == 0)
		child1_process(argv, envp, pipex);
	close(pipex->fd[1]);
	pipex->pid2 = fork();
	if (pipex->pid2 < 0)
		error_exit(FORK_FAIL, "haha");
	if (pipex->pid2 == 0)
		child2_process(argv, envp, pipex);
	close(pipex->fd[0]);
	waitpid(pipex->pid1, NULL, 0);
	waitpid(pipex->pid2, &(pipex->status), 0);
	pipex->exit_code = 0;
	if (WIFEXITED(pipex->status))
		pipex->exit_code = WEXITSTATUS(pipex->status);
	else if (WIFSIGNALED(pipex->status))
		pipex->exit_code = WTERMSIG(pipex->status);
	// else
	// 	statuscode = 1;
	// printf("%d\n", getpid());
	// printf("%d\n", getppid());
	while(1)
	{
	}
	// sleep(100000000);
	// system("leaks pipex"); //
	return (pipex->exit_code);
}

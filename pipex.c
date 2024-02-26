/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:50:37 by jtu               #+#    #+#             */
/*   Updated: 2024/02/26 18:14:43 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_exit(void)
{
	perror("Error");
	exit(EXIT_FAILURE);
}

int main(int argc, char **argv, char **envp)
{
	int	fd[2];

	if (argc != 5)
	{
		ft_putendl_fd("Error: Wrong Input", 2);
		ft_putendl_fd("Ex:./pipex <file1> <cmd1> <cmd2> <file2>", 2);
		exit(1);
	}
	if (pipe(fd) == -1)
		error_exit();
}

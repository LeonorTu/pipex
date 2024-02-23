/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:50:37 by jtu               #+#    #+#             */
/*   Updated: 2024/02/23 17:18:59 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char **argv, char **envp)
{
	if (argc != 5)
	{
		ft_putendl_fd("Error: Wrong Input", 2);
		ft_putendl_fd("Ex:./pipex <file1> <cmd1> <cmd2> <file2>", 2);
		exit(1);
	}

}

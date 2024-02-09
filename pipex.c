/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junesalaberria <junesalaberria@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 10:46:10 by junesalaber       #+#    #+#             */
/*   Updated: 2024/02/09 13:52:36 by junesalaber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv)
{
	int	fd[2];
	pid_t pid;

	pipe(fd);
	pid= fork();

	if (pid == -1)
		exit(-1);
	else if (pid == 0)
	{
		// estamos en el hijo
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close (fd[1]);
		execlp("ls", "ls", "-a", NULL);
	}
	else
	{
		// etsamos en el padre
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		execlp("cat", "cat", "-e", NULL);
	}
}
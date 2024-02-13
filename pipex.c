/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalaber <jsalaber@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 10:46:10 by junesalaber       #+#    #+#             */
/*   Updated: 2024/02/13 12:40:39 by jsalaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child(char **argv, int *mainfd) //char **env)
{
	int	fd;

	fd = open_file(argv[1], 0);
	dup2(fd, 0);
	dup2(mainfd[1], 1);
	close(mainfd[0]);
	execlp("ls", "ls", "-a", NULL);
}

void	parent(char **argv, int *mainfd) //char **env)
{
	int	fd;

	fd = open_file(argv[4], 1);
	dup2(fd, 1);
	dup2(mainfd[0], 0);
	close(mainfd[1]);
	execlp("cat", "cat", "-e", NULL);
}

int	main(int argc, char **argv)//char **env)
{
	int		mainfd[2];
	pid_t	pid;

	if (argc == 0)
		exit(1);
	else
	{
		pipe(mainfd);
		pid = fork();
		if (pid == -1)
			exit(-1);
		else if (pid == 0)
			child(argv, mainfd);
		else
			parent(argv, mainfd);
	}
}

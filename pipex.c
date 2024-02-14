/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalaber <jsalaber@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 10:46:10 by junesalaber       #+#    #+#             */
/*   Updated: 2024/02/14 12:50:20 by jsalaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child(char **argv, int *mainfd, char **env)
{
	int	fd;

	fd = open_file(argv[1], 0);
	dup2(fd, 0);
	dup2(mainfd[1], 1);
	close(mainfd[0]);
	exec(argv[2], env);
}

void	parent(char **argv, int *mainfd, char **env)
{
	int	fd;

	fd = open_file(argv[4], 1);
	dup2(fd, 1);
	dup2(mainfd[0], 0);
	close(mainfd[1]);
	exec(argv[3], env);
}

void	error(int n)
{
	if (n == 1)
		ft_putendl_fd("Incorrect argument format", 2);
	exit(0);
}

int	main(int argc, char **argv, char **env)
{
	int		mainfd[2];
	pid_t	pid;
	int		p_pipe;

	if (argc != 5)
		error(1);
	else
	{
		p_pipe = pipe(mainfd);
		if (p_pipe == -1)
			exit(-1);
		pid = fork();
		if (pid == -1)
			exit(-1);
		else if (pid == 0)
			child(argv, mainfd, env);
		else
			parent(argv, mainfd, env);
	}
}

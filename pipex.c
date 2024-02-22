/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalaber <jsalaber@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 10:46:10 by junesalaber       #+#    #+#             */
/*   Updated: 2024/02/22 12:37:52 by jsalaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_infile(char **argv)
{
	int	fd_in;

	fd_in = open(argv[1], O_RDONLY, 0777);
	if (fd_in < 0)
	{
		ft_putendl_fd("Incorrect infile", 2);
		exit(1);
	}
	return (fd_in);
}

void	access_outfile(char **argv)
{
	int	fd_out;
	int	acc;

	acc = access(argv[4], F_OK | W_OK);
	if (acc < 0)
	{
		fd_out = open(argv[4], O_WRONLY | O_CREAT, 0777);
		if (fd_out == -1)
		{
			ft_putendl_fd("Incorrect outfile", 2);
			exit(1);
		}
		close(fd_out);
	}
}

void	child(char **argv, int infile_fd, int *mainfd, char **env)
{
	if (infile_fd < 0)
	{
		exit(-1);
	}
	else
	{
		dup2(infile_fd, 0);
		dup2(mainfd[1], 1);
		close(mainfd[0]);
		exec(argv[2], env);
	}
}

void	parent(char **argv, int *mainfd, char **env)
{
	int	fd_out;

	fd_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd_out < 0)
	{
		ft_putendl_fd("Incorrect outfile", 2);
		exit(-1);
	}
	else
	{
		dup2(fd_out, 1);
		dup2(mainfd[0], 0);
		close(mainfd[1]);
		exec(argv[3], env);
	}
}

int	main(int argc, char **argv, char **env)
{
	int		mainfd[2];
	pid_t	pid;
	int		p_pipe;
	int		fd_infile;

	if (manage_error(argc) == 0)
	{
		access_outfile(&argv[4]);
		fd_infile = open_infile(argv);
		p_pipe = pipe(mainfd);
		if (p_pipe == -1)
		{
			ft_putendl_fd("Error in pipe", 2);
			exit(-1);
		}
		pid = fork();
		if (pid == -1)
			exit(-1);
		else if (pid == 0)
			child(argv, fd_infile, mainfd, env);
		wait(NULL);
		parent(argv, mainfd, env);
	}
	return (0);
}

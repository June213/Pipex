/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalaber <jsalaber@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 10:46:10 by junesalaber       #+#    #+#             */
/*   Updated: 2024/02/19 13:41:38 by jsalaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_infile(char **argv)
{
	int	fd_in;
	int	error;

	fd_in = open(argv[1], O_RDONLY, 0777);
	if (fd_in < 0)
	{
		ft_putendl_fd("Incorrect infile", 2);
		error = 1;
		exit(-1);
		return (error);
	}
	else
		return (fd_in);
}

int	open_outfile(char **argv)
{
	int	error;
	int	fd_out;

	fd_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd_out < 0)
	{
		ft_putendl_fd("Incorrect outfile", 2);
		error = 1;
		exit(-1);
		return (error);
	}
	else
		return (fd_out);
}

void	child(char **argv, int infile_fd, int *mainfd, char **env)
{
	dup2(infile_fd, 0);
	dup2(mainfd[1], 1);
	close(mainfd[0]);
	exec(argv[2], env);
}

void	parent(char **argv, int outfile_fd, int *mainfd, char **env)
{
	dup2(outfile_fd, 1);
	dup2(mainfd[0], 0);
	close(mainfd[1]);
	exec(argv[3], env);
}

int	main(int argc, char **argv, char **env)
{
	int		mainfd[2];
	pid_t	pid;
	int		p_pipe;
	int		fd_infile;
	int		fd_outfile;

	fd_infile = open_infile(argv);
	fd_outfile = open_outfile(argv);
	if (manage_error(argc, argv) == 0)
	{
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
		parent(argv, fd_outfile, mainfd, env);
	}
}

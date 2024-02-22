/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalaber <jsalaber@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 13:26:55 by junesalaber       #+#    #+#             */
/*   Updated: 2024/02/22 12:33:31 by jsalaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <sys/wait.h>

int		open_file(char **argv);
char	*ft_getenv(char **env);
void	ft_free(char **arr);
char	*ft_getpath(char *cmd, char **env);
void	exec(char *cmd, char **env);
void	child(char **argv, int infile_fd, int *mainfd, char **env);
void	parent(char **argv, int *mainfd, char **env);
int		manage_error(int argc);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalaber <jsalaber@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:39:52 by jsalaber          #+#    #+#             */
/*   Updated: 2024/02/22 13:06:47 by jsalaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	manage_error(int argc)
{
	int	error;

	error = 0;
	if (argc != 5)
	{
		ft_putendl_fd("Incorrect argument format", 2);
		error = 1;
	}
	return (error);
}

char	*ft_getenv(char **env)
{
	while (*env)
	{
		if (ft_strncmp(*env, "PATH=", 5) == 0)
			return (*env + 5);
		env++;
	}
	return (NULL);
}

void	ft_free(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	*ft_getpath(char *cmd, char **env)
{
	int		i;
	char	**split_path;
	char	**split_cmd;
	char	*part_path;
	char	*exec_path;

	split_path = ft_split(ft_getenv(env), ':');
	split_cmd = ft_split(cmd, ' ');
	if (!split_cmd)
	{
		ft_putendl_fd("incorrect command format", 2);
		ft_free(split_path);
		exit(1);
	}
	i = -1;
	while (split_path[++i])
	{
		part_path = ft_strjoin(split_path[i], "/");
		exec_path = ft_strjoin(part_path, split_cmd[0]);
		free(part_path);
		if (access(exec_path, X_OK) == 0)
			return (ft_free(split_cmd), exec_path);
		free (exec_path);
	}
	return (ft_free(split_path), ft_free(split_cmd), cmd);
}

void	exec(char *cmd, char **env)
{
	char	**split_cmd;
	char	*path;
	int		exec;

	split_cmd = ft_split(cmd, ' ');
	path = ft_getpath(split_cmd[0], env);
	exec = execve(path, split_cmd, env);
	if (exec == -1)
	{
		ft_putstr_fd("command not found", 2);
		ft_free(split_cmd);
		exit(0);
	}
}

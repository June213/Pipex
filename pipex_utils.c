/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalaber <jsalaber@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:39:52 by jsalaber          #+#    #+#             */
/*   Updated: 2024/02/13 12:09:52 by jsalaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// O_CREAT: por si el archivo no esta creado
// O_TRUNC por si esta creado para vaciarlo

int	open_file(char *file, int type)
{
	int	result;

	if (type == 0)
		result = open(file, O_RDONLY);
	if (type == 1)
		result = open(file, O_WRONLY | O_CREAT | O_TRUNC);
	if (result == -1)
		exit(1);
	return (result);
}

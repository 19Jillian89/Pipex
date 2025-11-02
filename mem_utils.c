/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilnassi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 11:51:34 by ilnassi           #+#    #+#             */
/*   Updated: 2025/03/11 14:56:19 by ilnassi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_paths(char *str, char **arr)
{
	int	i;

	if (str != NULL)
		free(str);
	if (arr != NULL)
	{
		i = 0;
		while (arr[i])
		{
			free(arr[i]);
			i++;
		}
		free(arr);
	}
}

void	verify_cmd_path(char *cmd_path, t_pipex *pipex)
{
	if (!cmd_path)
		error_close("Not found!", EXIT_FAILURE, pipex);
}

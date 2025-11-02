/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilnassi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 12:09:32 by ilnassi           #+#    #+#             */
/*   Updated: 2025/03/11 14:56:05 by ilnassi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*Handles writing an error message and closing allocated resources
before exiting with a given error code*/
void	error_close(char *error_message, int exit_code, t_pipex *pipex)
{
	if (error_message)
	{
		write(STDERR_FILENO, error_message, ft_strlen(error_message));
		write(STDERR_FILENO, "\n", 1);
		perror("Error!");
	}
	if (pipex)
	{
		if (pipex->cmd_path1)
			free(pipex->cmd_path1);
		if (pipex->cmd_path2)
			free(pipex->cmd_path2);
		if (pipex->argv_cmd1)
			free_parse_args(pipex->argv_cmd1);
		if (pipex->argv_cmd2)
			free_parse_args(pipex->argv_cmd2);
		if (pipex->paths)
			free_path_list(pipex);
		if (pipex->input_fd != -1)
			close(pipex->input_fd);
		if (pipex->output_fd != -1)
			close(pipex->output_fd);
	}
	exit(exit_code);
}

/*checks the validity of a command and in case of error, invokes
error_close function*/
char	*cmd_and_error(char *cmd, t_pipex *pipex)
{
	if (!cmd || cmd[0] == '\0')
	{
		error_close("Error: Not found!", EXIT_FAILURE, pipex);
		return (NULL);
	}
	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		else
			return (NULL);
	}
	return (NULL);
}

/*Function that frees the list of paths associated with pipex*/
void	free_path_list(t_pipex *pipex)
{
	if (pipex->paths != NULL)
	{
		free_parse_args(pipex->paths);
		pipex->paths = NULL;
	}
}

/*free memory for a list of arguments*/
void	free_parse_args(char **argv_cmd)
{
	int	i;

	i = 0;
	if (argv_cmd == NULL)
		return ;
	while (argv_cmd[i])
	{
		free(argv_cmd[i]);
		i++;
	}
	free(argv_cmd);
}

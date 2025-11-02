/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilnassi <ilnassi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:54:13 by ilnassi           #+#    #+#             */
/*   Updated: 2025/03/16 18:46:43 by ilnassi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex.h"

/*Create full path for a command, combine prefix + cmd name,
check if it exists and can be executed*/
char	*create_path(char *cmd, char *prefix)
{
	char	*temp_dir_path;
	char	*comand_path;

	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	temp_dir_path = ft_strjoin(prefix, "/");
	if (!temp_dir_path)
		return (NULL);
	comand_path = ft_strjoin(temp_dir_path, cmd);
	free(temp_dir_path);
	if (!comand_path)
		return (NULL);
	if (access(comand_path, X_OK) == 0)
		return (comand_path);
	free(comand_path);
	return (NULL);
}

/*Extracts paths from environment variables, extracts PATH value,
which contains directories where the system searches for executable cmds*/
char	**extract_dir_paths(char **env)
{
	char	**path;

	if (!env)
		return (NULL);
	while (*env && !ft_strnstr((*env), "PATH=", 5))
		env++;
	if (!*env)
		return (NULL);
	path = ft_split(*env + 5, ':');
	return (path);
}

void	free_array(char **arr)
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

/*Searches for a command in the directories specified 
by the PATH environment variable and returns 
the full path to the cmd*/
char	*find_command(char *cmd, char **env)
{
	char	**dir_paths;
	char	*cmd_path;
	int		i;

	dir_paths = extract_dir_paths(env);
	if (!dir_paths)
		return (NULL);
	i = 0;
	while (dir_paths[i])
	{
		cmd_path = create_path(cmd, dir_paths[i]);
		if (cmd_path)
		{
			free_array(dir_paths);
			return (cmd_path);
		}
		i++;
	}
	free_array(dir_paths);
	return (NULL);
}

/*Manages closing of fds associated with a pipe and waits for
child processes to terminate*/
void	closefd_wait(int *pipefd, t_pipex *pipex)
{
	int	status;

	close(pipefd[0]);
	close(pipefd[1]);
	if (pipex->pid1 > 0)
		waitpid(pipex->pid1, &status, 0);
	if (pipex->pid2 > 0)
		waitpid(pipex->pid2, &status, 0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilnassi <ilnassi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:21:40 by ilnassi           #+#    #+#             */
/*   Updated: 2025/03/27 17:52:27 by ilnassi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex.h"

//Create a pipe, if it fails error
int	pipe_creation(int *pipefd)
{
	if (pipe(pipefd) == 1)
	{
		perror("Pipe creation failed");
		return (-1);
	}
	return (0);
}

//Start child process execute one of the two commands
void	start_child(t_pipex *pipex, char **argv, char **envp, int is_first)
{
	pid_t			pid;
	t_child_args	args;

	pid = fork();
	if (pid < 0)
		error_close("Fork Error!!", EXIT_FAILURE, pipex);
	if (pid == 0)
	{
		if (is_first)
			args.cmd = argv[2];
		else
			args.cmd = argv[3];
		args.envp = envp;
		args.is_first = is_first;
		args.pipex = pipex;
		if (args.is_first)
			dup2(pipex->input_fd, STDIN_FILENO);
		else
			dup2(pipex->pipefd[0], STDIN_FILENO);
		first_child(&args, pipex);
	}
}

//Executes the command in the child process
int	first_child(t_child_args *args, t_pipex *pipex)
{
	char	**cmd_args;
	char	*cmd_path;

	cmd_args = ft_split(args->cmd, ' ');
	if (!cmd_args)
		error_close("Allocation failed", EXIT_FAILURE, args->pipex);
	cmd_path = find_command(cmd_args[0], args->envp);
	if (!cmd_path)
	{
		free_array(cmd_args);
		error_close("Not found", EXIT_FAILURE, args->pipex);
	}
	handle_pipes(args, pipex);
	execve(cmd_path, cmd_args, args->envp);
	free(cmd_path);
	free_array(cmd_args);
	error_close("execve failed", EXIT_FAILURE, args->pipex);
	return (-1);
}

/*Handles output redirection for the two commands,
the first writes to the pipe and the second to the output file*/
void	handle_pipes(t_child_args *args, t_pipex *pipex)
{
	if (args->is_first)
	{
		dup2(pipex->pipefd[1], STDOUT_FILENO);
		close(pipex->input_fd);
		close(pipex->pipefd[0]);
	}
	else
	{
		dup2(pipex->output_fd, STDOUT_FILENO);
		close(pipex->output_fd);
		close(pipex->pipefd[1]);
	}
}

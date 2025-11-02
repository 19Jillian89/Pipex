/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilnassi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 12:45:47 by ilnassi           #+#    #+#             */
/*   Updated: 2025/03/11 14:56:35 by ilnassi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//Handles creation of a pipe, two child processes, sync between processes
void	pipex_execute(t_pipex *pipex, char **argv, char **envp)
{
	if (pipe(pipex->pipefd) == -1)
		error_close("Pipe error", EXIT_FAILURE, pipex);
	start_child(pipex, argv, envp, 1);
	start_child(pipex, argv, envp, 0);
	close(pipex->pipefd[0]);
	close(pipex->pipefd[1]);
	waitpid(-1, NULL, 0);
	waitpid(-1, NULL, 0);
}

//File I/O and start main process
int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	pipex = (t_pipex){0};
	if (argc != 5)
	{
		ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 outfile\n", 2);
		return (EXIT_FAILURE);
	}
	pipex.input_fd = open(argv[1], O_RDONLY);
	if (pipex.input_fd < 0)
		error_close("Input file error", EXIT_FAILURE, &pipex);
	pipex.output_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex.output_fd < 0)
	{
		close(pipex.input_fd);
		error_close("Output file error", EXIT_FAILURE, &pipex);
	}
	pipex_execute(&pipex, argv, envp);
	close(pipex.input_fd);
	close(pipex.output_fd);
	return (EXIT_SUCCESS);
}

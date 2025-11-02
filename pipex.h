/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilnassi <ilnassi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 16:38:08 by ilnassi           #+#    #+#             */
/*   Updated: 2025/03/11 14:56:51 by ilnassi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>
# include <string.h>
# include <sys/wait.h>

//Struct for managing file descriptors and commands
typedef struct s_pipex
{
	char	**argv_cmd1;
	char	**argv_cmd2;
	char	**paths;
	char	*cmd_path1;
	char	*cmd_path2;
	int		input_fd;
	int		output_fd;
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;
}	t_pipex;

//Structure that contains info about commands executed in child processes
typedef struct s_child_args
{
	char	**envp;
	char	*cmd;
	int		is_first;
	int		*pipefd;
	t_pipex	*pipex;
}	t_child_args;

//Path management and command execution functions
char	*find_command(char *cmd, char **env);
char	*create_path(char *cmd, char *prefix);
char	**extract_dir_paths(char **env);
char	*cmd_and_error(char *cmd, t_pipex *pipex);
int		pipe_creation(int *pipefd);
int		first_child(t_child_args *args, t_pipex *pipex);
void	start_child(t_pipex *pipex, char **argv, char **envp, int is_first);
void	closefd_wait(int *pipefd, t_pipex *pipex);
void	error_close(char *error_message, int exit_code, t_pipex *pipex);
void	free_parse_args(char **argv_cmd);
void	free_path_list(t_pipex *pipex);
void	free_array(char **arr);
void	close_parent(int *pipefd, t_pipex *pipex);
void	verify_cmd_path(char *cmd_path, t_pipex *pipex);
void	pipex_execute(t_pipex *pipex, char **argv, char **envp);
void	handle_pipes(t_child_args *args, t_pipex *pipex);

#endif

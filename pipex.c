/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bizcru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 11:15:12 by bizcru            #+#    #+#             */
/*   Updated: 2024/12/13 11:57:29 by bcanals-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


void	sender(char **argv, int *pipefd, char **env)
{
	char	*path;
	char	**args;
	int		file_fd;
	int		exec_r;

	file_fd = open(argv[1], O_RDONLY);
	if (file_fd == -1)
		handle_err(errno, "sender open");
	args = ft_split(argv[2], ' ');
	if (!args)
		handle_err(errno, "sender split");
	path = get_path(args[0], env);
	if (!path)
	{
		ft_free_array(args);
		handle_err(0, "sender get_path");
	}
	close(pipefd[0]);
	dup2(pipefd[1], STDOUT_FILENO);
	dup2(file_fd, STDIN_FILENO);
	exec_r = 0;
	exec_r = execve(path, args, env);
	free(path);
	ft_free_array(args);
	close(file_fd);
	close(pipefd[1]);
	if (exec_r == -1)
		handle_err(errno, "execve sender");
	exit(EXIT_SUCCESS);
}

void	receiver(char **argv, int *pipefd, char **env)
{
	char	*path;
	char	**args;
	int		file_fd;

	file_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file_fd == -1)
		handle_err(errno, "receiver open");
	args = ft_split(argv[3], ' ');
	if (!args)
		handle_err(errno, "receiver split");
	path = get_path(args[0], env);
	if (!path)
	{
		ft_free_array(args);
		handle_err(0, "receiver get_path");
	}
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	dup2(file_fd, STDOUT_FILENO);
	if (my_execve(path, args, env) == -1);
	

	exit(EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **env)
{
	int		pipefd[2];
	pid_t	d_1;
	pid_t	pid_2;

	if (argc != 5)
		handle_err(0, "Please write 4 arguments");
	if (pipe(pipefd) == -1)
		handle_err(errno, "pipe error");
	pid_1 = fork();
	if (pid_1 == -1)
		handle_err(errno, "fork pid_1");
	if (pid_1 == 0)
		sender(argv, pipefd, env);
	pid_2 = fork();
	if (pid_2 == -1)
		handle_err(errno, "fork pid_2");
	if (pid_2 == 0)
		receiver(argv, pipefd, env);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid_1, NULL, 0);
	waitpid(pid_2, NULL, 0);
}

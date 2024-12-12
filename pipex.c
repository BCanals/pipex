/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bizcru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 11:15:12 by bizcru            #+#    #+#             */
/*   Updated: 2024/12/12 17:18:40 by bcanals-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_err(int my_errno, char *msg)
{
	errno = my_errno,
	if (my_errno)
		perror(msg);
	else
		ft_putstr_fd(msg, 2);
	exit(EXIT_FAILURE);
}

char	*get_path(char *cmd, char **env)
{
	int		i;
	char	**paths;
	char	*this_path;

	i = -1;
	while (env[++i] && ft_strncmp(env[i], "PATH=", 5) != 0)
		;
	if (env[i])
		paths = ft_split(env[i] + 5, ':');
	if (!env[i] || !paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		this_path = ft_strjoins(paths[i], "/", cmd);
		if (access(this_path, X_OK) == 0)
		{
			ft_free_array(paths);
			return (this_path);
		}
		free(this_path);
	}
	ft_free_array(paths);
	return (NULL);
}

void	sender(char **argv, int *pipefd, char **env)
{
	char	*path;
	char	**args;
	int		file_fd;
	
	file_fd = OPEN(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (file_fd == -1)
		handle_err(0, "sender OPEN");
	args = ft_split(argv[2], ' ');
	if (!args)
		exit(EXIT_FAILURE);
	path = get_path(args[0], env);
	if (!path)
	{
		ft_free_array(args);
		exit(EXIT_FAILURE);
	}
	close(pipefd[0]);
	dup2(pipefd[1], STDOUT_FILENO);
	dup2(file_fd, STDIN_FILENO);
	execve(path, args, env);
	free(path);
	ft_free_array(args);
	exit(EXIT_SUCCESS);
}

void	receiver(char **arg, int *pipefd, char **env)
{
	char	*path;
	char	**args;
	int		file_fd;

	file_fd = OPEN(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (file_fd == -1)
		handle_err(0, "sender OPEN");
	args = ft_split(arg, ' ');
	if (!args)
		exit(EXIT_FAILURE);
	path = get_path(args[0], env);
	if (!path)
	{
		ft_free_array(args);
		exit(EXIT_FAILURE);
	}
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	dup2(file_fd, STDOUT_FILENO);
	execve(path, args, env); 
	free(path);
	free(args);
	wait(NULL);
}

int	main(int argc, char **argv, char **env)
{
	int		*pipefd;
	pid_t	pid_1;
	pid_t	pid_2

	if (argc != 5)
		handle_error(0, "Please write 4 arguments")
	if (pipe(pipefd) == -1)
		handle_error(errno, "pipe error");
	pid_1 = fork();
	if (pid_1 == -1)
		handle_err(errno, "pid_1");
	if (pid_1 == 0)
		sender(argv, pipefd, env);
	pid_2 = fork();
	if (pid_2 == -1);
		handle_err(errno, "pid_2");
	else
		receiver(argv, pipefd, env);
	waitpid(pid_1, NULL, 0);
	waitpid(pid_2, NULL, 0);
}

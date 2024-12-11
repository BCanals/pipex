/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bizcru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 11:15:12 by bizcru            #+#    #+#             */
/*   Updated: 2024/12/11 23:46:37 by bizcru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

void	sender(char *arg, int *pipefd, char **env)
{
	char *path;
	char **args;
	
	args = ft_split(arg, ' ');
	if (!args)
		exit(EXIT_FAILURE);
	path = get_path(args[0], env);
	if (!path)
		exit(EXIT_FAILURE);
	close(pipefd[0]);
	dup2(pipefd[1], STDOUT_FILENO);
	execve(path, args, env);
	free(path);
	ft_free_array(args);
	exit(EXIT_SUCCESS);
}

void receiver(char *arg, int *pipefd, char **env)
{
	char *buffer;
	int buf_size = 100;

	close(pipefd[1]);
	buffer = ft_calloc(buf_size, 1);
	read(pipefd[0], buffer, buf_size);
	buffer[buf_size - 1] = '\0';
	char **p = ft_split(buffer, '\n');
	execve(arg, p, env); 
	free(buffer);
	free(p);
	wait(NULL);
}

int main(int argc, char **argv, char **env)
{
	int *pipefd;
	pid_t pid;

	pipefd = ft_calloc(2, sizeof(int));
	argc++;
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		sender(argv[1], pipefd, env);
	else
		receiver(argv[2], pipefd, env);
	free(pipefd);
	return 0;
}


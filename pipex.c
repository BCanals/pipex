/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bizcru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 11:15:12 by bizcru            #+#    #+#             */
/*   Updated: 2024/12/09 11:34:52 by bizcru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_path(char *cmd, char **env)
{
	int		i;
	char	**paths;
	
	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	if (!env[i])
		return ('\0');
	paths = ft_split(env[i] + 5, ':');
	if (!paths)
		return ('\0');
	i = -1;
	while (paths[++i])
}

void sender(char *arg, int *pipefd, char **env)
{
	close(pipefd[0]);
	dup2(pipefd[1], STDOUT_FILENO);
	char *p[] = {NULL};
	execve(arg, p, env);
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


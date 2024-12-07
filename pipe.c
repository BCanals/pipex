/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bizcru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 11:15:12 by bizcru            #+#    #+#             */
/*   Updated: 2024/12/07 11:49:57 by bizcru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

void sender(int write_fd);
void receiver(int read_fd);

int main()
{
	int pipefd[2];
	pid_t pid;

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
	{
		close(pipefd[0]);
		sender(pipefd[1]);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(pipefd[1]);
		receiver(pipefd[0]);
		wait(NULL);
	}
	return 0;
}

void sender(int write_fd)
{
	const char* msg = "Hello world!";

	write(write_fd, msg, strlen(msg) + 1);
	close(write_fd);
}

void receiver(int read_fd)
{
	char buffer[100];
	read(read_fd, buffer, sizeof(buffer));
	printf("received: %s\n", buffer);
	close(read_fd);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bizcru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 23:59:06 by bizcru            #+#    #+#             */
/*   Updated: 2024/12/07 11:14:32 by bizcru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main()
{
	const char *msg = "Hello world!";
	int pipefds[2];
	pid_t pid;
	char buf[30];


	pipe(pipefds);
	pid = fork();
	if (pid == -1){
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (pid == 0) {
		close(pipefds[0]);
		write(pipefds[1], msg, strlen(msg));
		write(pipefds[1], "\0", 1);
		close(pipefds[1]);
		exit(EXIT_SUCCESS);
	} else {
		close(pipefds[1]);
		read(pipefds[0], buf, sizeof(buf));
		printf("Received: %s\n", buf);
		close(pipefds[0]);
		wait(NULL);
	}

	return 0;
}

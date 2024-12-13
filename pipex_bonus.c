/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bizcru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 11:15:12 by bizcru            #+#    #+#             */
/*   Updated: 2024/12/13 18:02:07 by bcanals-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

pid_t	my_fork(char *cmd, char **env, int *fds_in, int *fds_out)
{
	pid_t	my_id;
	t_data	*data;

	my_id = fork();
	if (my_id == -1)
		handle_err(errno, "fork");
	else if (my_id == 0)
	{
		my_close(fds_in[1], fds_out[0]);
		data = load_data(cmd, env, fds_in[0], fds_out[1]);
		redirect(data);
		if (execve(data->path, data->args, env) == -1)
			clean_exit(data, errno, "execve");
		my_close(data->fd_in, data->fd_out);
		exit(EXIT_SUCCESS);
	}
	return (my_id);
}

int	main(int argc, char **argv, char **env)
{
	int		pipefds[2];
	int		filefds[2];
	pid_t	pid_1;
	pid_t	pid_2;

	if (argc != 5)
		handle_err(0, "Please write 4 arguments");
	if (pipe(pipefds) == -1)
		handle_err(errno, "pipe error");
	open_files(argv[1], argv[4], filefds);
	pid_1 = my_fork(argv[2], env, filefds, pipefds);
	pid_2 = my_fork(argv[3], env, pipefds, filefds);
	my_close(filefds[0], filefds[1]);
	my_close(pipefds[0], pipefds[1]);
	waitpid(pid_1, NULL, 0);
	waitpid(pid_2, NULL, 0);
}

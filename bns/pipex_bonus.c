/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bizcru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 11:15:12 by bizcru            #+#    #+#             */
/*   Updated: 2024/12/14 14:52:56 by bcanals-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

// Handles the forking process and manages errors

pid_t	my_fork(char *cmd, char **env, int **fds, pid_t *childs)
{
	pid_t	my_id;
	t_data	*data;

	my_id = fork();
	if (my_id == -1)
		return (my_id);
	else if (my_id == 0)
	{
		free(childs);
		my_close(fds[0][1], fds[1][0]);
		data = load_data(cmd, env, fds[0][0], fds[1][1]);
		redirect(data);
		if (execve(data->path, data->args, env) == -1)
			clean_exit(data, errno, "execve");
		my_close(data->fd_in, data->fd_out);
		exit(EXIT_SUCCESS);
	}
	return (my_id);
}

// Handles the iteration of creating a child process for each cmd

pid_t	*do_childs(int **fds, int argc, char **argv, char **env)
{
	int		i;
	pid_t 	*childs;
	int		newfds[2];
	int		oldfds[2];

	fds[0] = newfds;
	fds[1] = oldfds;
	childs = ft_calloc(argc - 2, sizeof(pid_t));
	if (!childs)
		close_exit(oldfds, errno, "ft_calloc");
	i = 0;
	while (i < argc - 4)
	{
		if (pipe(newfds) == -1)
			free_close_exit(oldfds, NULL, childs, "pipe");
		childs[i] = my_fork(argv[i + 2], env, fds, childs);
		if (childs[i++] == -1)
			free_close_exit(oldfds, newfds, childs, "fork");
		my_close(oldfds[0], oldfds[1]);
		oldfds[0] =  newfds[0];
		oldfds[1] =  newfds[1];
	}
	return (childs);
}

int	main(int argc, char **argv, char **env)
{
	int		oldfds[2];
	int		newfds[2];
	int		*fds[2];
	pid_t	*childs;

	fds[0] = newfds;
	fds[1] = oldfds;
	if (argc < 5)
		handle_err(0, "Please write at least 4 arguments");
	open_files(argv[1], argv[argc - 1], oldfds);
	childs = do_childs(fds, argc, argv, env);
	open_files(argv[1], argv[argc - 1], newfds);
	childs[argc - 4] = my_fork(argv[argc - 2], env, fds, childs);
	if (childs[argc - 4] == -1)
		free_close_exit(oldfds, newfds, childs, "fork");
	my_close(oldfds[0], oldfds[1]);
	my_close(newfds[0], newfds[1]);
	wait_childs(childs);
	free(childs);
}

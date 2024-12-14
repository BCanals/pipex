/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_2_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcanals- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 11:32:22 by bcanals-          #+#    #+#             */
/*   Updated: 2024/12/14 14:31:35 by bcanals-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

// Helper function for get_path to manage the error handling.

static char	*set_error(int *my_errno, char *msg, char **msg_add)
{
	*my_errno = errno;
	*msg_add = msg;
	return (NULL);
}

// Gets the path (if valid one) of the cmd of the child.
// Manages errors to allow load_data print the correct error info.

static char	*get_path(char *cmd, char **env, int *my_errno, char **msg_add)
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
		return (set_error(my_errno, "PATH not found\n", msg_add));
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
	return (set_error(my_errno, "no valid path\n", msg_add));
}

// Loads the necessary data for the child process, also handles errors.

t_data	*load_data(char *cmd, char **env, int fd_in, int fd_out)
{
	t_data	*new;
	int		my_errno;
	char	*msg;

	new = malloc(sizeof(t_data));
	if (!new)
	{
		perror("malloc");
		my_close(fd_in, fd_out);
		exit(EXIT_FAILURE);
	}
	new->fd_in = fd_in;
	new->fd_out = fd_out;
	new->args = NULL;
	new->path = NULL;
	new->args = ft_split(cmd, ' ');
	if (!new->args)
		clean_exit(new, 0, "ft_split in load data");
	new->path = get_path(new->args[0], env, &my_errno, &msg);
	if (!new->path)
		clean_exit(new, my_errno, msg);
	return (new);
}

// Opens files and fills the array

void	open_files(char *file_in, char *file_out, int *filefds)
{
	int	temp_fd;

	temp_fd = open(file_in, O_RDONLY);
	if (temp_fd == -1)
		handle_err(errno, "open infile");
	filefds[0] = temp_fd;
	temp_fd = open(file_out, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (temp_fd == -1)
	{
		perror("open outfile");
		if (close(filefds[1]) == -1)
			perror("close infile");
		exit(EXIT_FAILURE);
	}
	filefds[1] = temp_fd;
}

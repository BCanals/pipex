/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_data_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcanals- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:48:52 by bcanals-          #+#    #+#             */
/*   Updated: 2024/12/13 15:00:44 by bcanals-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	my_close(int fd1, int fd2)
{
	if (close(fd1) == -1)
		perror("close");
	if (close(fd2) == -1)
		perror("close");
}

// Close and frees the data of a t_data
// Checks which one is available to avoid double free in load_data

void	clean(t_data *data)
{	
	my_close(data->fd1, data->fd2);
	if (data->path)
		free(data->path);
	if (data->args)
		ft_free_array(data->args);
	free(data);	
}

void	clean_exit(t_data *data, int my_errno, char *msg)
{
	clean(data);
	handl_err(my_errno, msg);
}

// Creates a new t_data struct provided the cmd is a valid one.

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
	args = ft_split(cmd, ' ');
	if (!args)
		clean_exit(new, 0, "ft_split in load data");
	new->path = get_path(args[0], env, &my_errno, &msg);
	if (!new->path)
		clean_exit(new, 0, my_errno, msg);
	return (new);
}



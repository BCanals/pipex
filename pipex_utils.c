/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcanals- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 11:32:22 by bcanals-          #+#    #+#             */
/*   Updated: 2024/12/13 14:52:37 by bcanals-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_err(int my_errno, char *msg)
{
	errno = my_errno;
	if (my_errno)
		perror(msg);
	else
		ft_putstr_fd(msg, 2);
	exit(EXIT_FAILURE);
}

static char *set_error(int *my_errno, char *msg, char **msg_add)
{
	*my_errno = errno;
	*msg_add = msg;
	return (NULL);
}

char	*get_path(char *cmd, char **env, int *my_errno, char **msg_add)
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
		return (set_error(my_errno, "ft_split in get_path", msg_add));
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
	return (set_error(my_errno, "get_path", msg_add));
}

void	my_execve(char *path, char **args, char **env)
{
	int execve_r;

	execve_r = execve(path, args, env);
	free(path);
	ft_free_array(args);
}



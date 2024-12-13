/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bizcru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 16:18:40 by bizcru            #+#    #+#             */
/*   Updated: 2024/12/13 12:57:22 by bcanals-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include "libft/libft.h"

typedef struct s_data
{
	char	*path;
	int		*fds_in[2];
	int		*fds_out[2];
}			t_data;

void	handle_err(int my_errno, char *msg);
char	*get_path(char *cmd, char **env);
void	my_execve(char *path, char **args, char **env);
#endif

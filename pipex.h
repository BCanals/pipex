/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bizcru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 16:18:40 by bizcru            #+#    #+#             */
/*   Updated: 2024/12/13 16:18:09 by bcanals-         ###   ########.fr       */
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
	char	**args;
	int		fd_in;
	int		fd_out;
}			t_data;

int		my_close(int fd1, int fd2);
void	clean(t_data *data);
void	clean_exit(t_data *data, int my_errno, char *msg);
void	handle_err(int my_errno, char *msg);
void	redirect(t_data *data);
t_data	*load_data(char *cmd, char **env, int fd_in, int fd_out);
#endif

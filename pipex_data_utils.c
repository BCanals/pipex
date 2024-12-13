/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_data_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcanals- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:48:52 by bcanals-          #+#    #+#             */
/*   Updated: 2024/12/13 13:05:46 by bcanals-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_data	*load_data(char *cmd, char **env, int *fds_in, int *fds_out)
{
	t_data	*new;

	new = malloc(sizeof(t_data));
	if (!new)
		handle_err(errno, "malloc error");
	new->path = get_path(cmd, env);
	new->fds_in = fds_in;
	new->fds_out
}

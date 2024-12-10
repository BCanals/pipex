/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bizcru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 21:42:29 by bizcru            #+#    #+#             */
/*   Updated: 2024/12/07 17:55:18 by bizcru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
	char *path = "/bin/ls";
	char *args[] = {"ls", NULL};
	char *envp[] = {NULL};

	execve(path, args, envp);
}

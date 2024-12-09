/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bizcru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 12:28:17 by bizcru            #+#    #+#             */
/*   Updated: 2024/12/09 11:18:43 by bizcru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft/libft.h"

int main (int argc, char **argv, char **env)
{
	argc++;
	argv++;
	/*while (*env)
	{
		printf("%s\n", *env);
		env++;
	}*/
	int i;

	i = 0;
	while (ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	printf("%s\n", env[i]);

}

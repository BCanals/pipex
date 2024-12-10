/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcanals- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:49:18 by bcanals-          #+#    #+#             */
/*   Updated: 2024/12/10 14:40:55 by bcanals-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*this_strjoin(char *s1, char *s2)
{
	unsigned int	size;
	char			*rtrn;
	unsigned int	s1_len;
	unsigned int	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	size = s1_len + s2_len + 1;
	rtrn = malloc(size);
	if (rtrn == NULL)
		return (NULL);
	ft_memmove(rtrn, s1, s1_len);
	rtrn += s1_len;
	ft_memmove(rtrn, s2, s2_len);
	rtrn -= s1_len;
	rtrn[size - 1] = '\0';
	return (rtrn);
}

char	*ft_strjoins(char *s1, char *s2, char *s3)
{
	char	*temp;
	char	*rtrn;

	temp = this_strjoin(s1, s2);
	rtrn = this_strjoin(temp, s3);
	free(temp);
	return (rtrn);
}

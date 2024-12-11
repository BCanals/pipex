/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcanals- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:43:53 by bcanals-          #+#    #+#             */
/*   Updated: 2024/12/10 16:36:36 by bcanals-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	size_t	i;
	size_t len;

	i = 0;
	if (little[0] == 0)
		return ((char *)(big));
	len = ft_strlen(big) - ft_strlen(little);
	while (i <= len)
	{
		if (ft_strcmp(big, little) == 0)
			return ((char *)(big));
		big++;
		i++;
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bizcru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 20:47:43 by bizcru            #+#    #+#             */
/*   Updated: 2024/10/18 16:34:30 by bizcru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	*p;
	unsigned char	*s2;
	unsigned char	c2;

	s2 = (unsigned char *)s;
	p = (unsigned char *)s;
	c2 = (unsigned char)c;
	while (*s2)
		s2++;
	while (s2 >= p)
	{
		if (*s2 == c2)
			return ((char *)(s2));
		s2--;
	}
	return (NULL);
}

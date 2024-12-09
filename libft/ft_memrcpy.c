/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memrcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bizcru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 15:21:23 by bizcru            #+#    #+#             */
/*   Updated: 2024/10/18 16:26:56 by bizcru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memrcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*dest2;
	const unsigned char	*src2;

	if (!dest || !src)
		return (dest);
	dest2 = dest;
	src2 = src;
	while (n-- > 0)
	{
		dest2[n] = src2[n];
	}
	return (dest);
}

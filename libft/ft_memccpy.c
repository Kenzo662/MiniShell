/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evella <evella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 23:42:57 by evella            #+#    #+#             */
/*   Updated: 2023/10/03 12:17:00 by evella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t len)
{
	char		*tempd;
	const char	*temps;

	tempd = dest;
	temps = src;
	while (len-- > 0)
	{
		*tempd = *temps;
		if (*tempd == c)
			return (tempd + 1);
		tempd++;
		temps++;
	}
	return (0);
}

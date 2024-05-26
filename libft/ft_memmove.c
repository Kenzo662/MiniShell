/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evella <evella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 00:09:21 by evella            #+#    #+#             */
/*   Updated: 2023/10/02 00:09:24 by evella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	char	*destchar;
	char	*srcchar;
	size_t	i;

	destchar = (char *)dest;
	srcchar = (char *)src;
	if (!destchar && !srcchar)
		return (NULL);
	i = 0;
	if (destchar > srcchar)
	{
		while (len-- > 0)
		{
			destchar[len] = srcchar[len];
		}
	}
	else
	{
		while (i < len)
		{
			destchar[i] = srcchar[i];
			i++;
		}
	}
	return (dest);
}

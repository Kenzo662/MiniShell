/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evella <evella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 22:01:59 by evella            #+#    #+#             */
/*   Updated: 2023/10/01 22:03:03 by evella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memset(void *str, int c, size_t count)
{
	char	*temp;

	temp = str;
	while (count-- > 0)
	{
		*temp++ = c;
	}
	return (str);
}

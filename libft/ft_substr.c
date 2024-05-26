/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evella <evella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 23:51:25 by evella            #+#    #+#             */
/*   Updated: 2023/10/03 13:04:32 by evella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	int		i;
	int		l;
	char	*substr;

	if (start > (unsigned int)ft_strlen((char *)s))
	{
		substr = (char *)malloc(sizeof(char));
		if (!substr)
			return (NULL);
		substr[0] = '\0';
		return (substr);
	}
	if ((ft_strlen((char *)s) - start) > len)
		l = len;
	else
		l = ft_strlen((char *)s) - start;
	i = 0;
	substr = (char *)malloc(sizeof(char) * (l + 1));
	if (!substr)
		return (NULL);
	while (len-- > 0 && s[start])
		substr[i++] = s[start++];
	substr[i] = '\0';
	return (substr);
}
